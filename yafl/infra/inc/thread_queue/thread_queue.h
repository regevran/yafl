
#ifndef __THREAD_QUEUE__
#define __THREAD_QUEUE__

#include "execution/execution_forever.h"
#include "execution/owner_execution.h"
#include "joinable.h"
#include "msg.h"
#include "operation/operation.h"
#include "thread_queue_counter.h"
#include "thread_queue_handler.h"
#include "thread_queue_owner.h"
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace rf{
namespace thread_queue{

template< class T>
class ThreadQueue : 
    public rf::Operation,
    public rf::Joinable,
    public rf::OwnerExecution< rf::ExecutionForever > 
{
    public:
        ThreadQueue( 
                const std::string& qName,
                unsigned long maxQueueSize,
                ThreadQueueHandler<T>* handler,
                std::chrono::milliseconds stopLatency = std::chrono::milliseconds(1000),
                ThreadQueueOwner<T>* owner = nullptr
       );

       ThreadQueue( const ThreadQueue& ) = delete;
       ThreadQueue( const ThreadQueue&& ) = delete;

       virtual ~ThreadQueue();

    public:
       ThreadQueueHandler<T>* getHandler() const;

       // sets new handler, returns the old handler
       ThreadQueueHandler<T>* replaceHandler( ThreadQueueHandler<T>* newHandler );

    public:
        virtual void start();
        virtual void stop();
        virtual void join();
        virtual void detach();

    public:
        void pause();
        void resume();

    public:
        // get notification when the internal thread is done
        virtual void done( ExecutionForever* );

    public:
        bool push( const T& t );

    public:
        bool empty();
        const std::string& name() const;

    public:
        virtual bool Operate(); 

    public:
        const ThreadQueueCounter& getCounter() const;
        ThreadQueueCounter& getCounter(); 

    private:
        const unsigned long         _maxQueueSize;
        std::mutex                  _mutexHandler;
        ThreadQueueHandler<T>*      _handler;
        std::queue<T>               _queue;
        std::mutex                  _queueLock;
    private:
        // for operate
        std::mutex                  _operationLock;
        std::condition_variable     _elementInQueue;
        std::chrono::milliseconds   _stopLatency;

    private:
        rf::ExecutionForever        _readerExecution; 

    private:
        ThreadQueueOwner<T>*        _owner;

    private:
        const std::string           _qName;
        ThreadQueueCounter          _theCounter;
        bool                        _bPaused;
};


template< class T>
ThreadQueue<T>::ThreadQueue( 
        const std::string& qName,
        unsigned long maxQueueSize,
        ThreadQueueHandler<T>* handler,
        std::chrono::milliseconds stopLatency,
        ThreadQueueOwner<T>* owner
) : _maxQueueSize( maxQueueSize ), 
    _handler( handler ),
    _stopLatency( stopLatency ),
    _readerExecution( *this, nullptr, nullptr, std::chrono::microseconds(0) ),
    _owner( owner ),
    _qName( qName ),
    _theCounter( _qName, _maxQueueSize ),
    _bPaused( false )
{
    _readerExecution.owner( this );
}

template< class T>
ThreadQueue<T>::~ThreadQueue()
{
}

template< class T>
ThreadQueueHandler<T>* ThreadQueue<T>::getHandler() const
{
    return _handler;
}

template< class T>
ThreadQueueHandler<T>* ThreadQueue<T>::replaceHandler( ThreadQueueHandler<T>* newHandler )
{
    std::lock_guard<std::mutex> lock( _mutexHandler );
    ThreadQueueHandler<T>* ret = _handler;
    _handler = newHandler;

    return ret;
}

template< class T>
void ThreadQueue<T>::start()
{
    _readerExecution.start();

    if ( _owner )
    {
        _owner->started( this );
    }
}

template< class T>
void ThreadQueue<T>::stop()
{
    _readerExecution.stop();

    if ( _owner )
    {
        _owner->stopped( this );
    }
}

template< class T>
void ThreadQueue<T>::join()
{
    _readerExecution.join();
}

template< class T>
void ThreadQueue<T>::detach()
{
    _readerExecution.detach();
}

template< class T>
void ThreadQueue<T>::pause()
{
    _bPaused = true;
}

template< class T>
void ThreadQueue<T>::resume()
{
    _bPaused = false;
}

template< class T>
void ThreadQueue<T>::done( ExecutionForever* )
{
    if ( _owner )
    {
        _owner->done( this );
    }
}

template< class T>
bool ThreadQueue<T>::push( const T& t )
{
    bool ret;

    std::lock_guard< std::mutex > lg( _queueLock );

    _theCounter.pushRequested();

    if ( _bPaused )
    {
        _theCounter.dropped();
        ret = false;
        return ret;
    } 

    int queueSize = _queue.size();

    if ( 0 == queueSize )
    {
        _elementInQueue.notify_one();
    }

    if ( queueSize < _maxQueueSize )
    {
        _queue.push( t );

        _theCounter.pushed();
        _theCounter.size( queueSize );

        ret = true;
    }
    else
    {
        _theCounter.dropped();
        ret = false;
    }

    return ret;
}

template< class T>
bool ThreadQueue<T>::empty()
{
    std::lock_guard< std::mutex > lg( _queueLock ); 

    return _queue.empty();
}

template< class T>
const std::string& ThreadQueue<T>::name() const
{
    return _qName;
} 

template< class T>
bool ThreadQueue<T>::Operate()
{
    _queueLock.lock();

    if ( ! _queue.empty() )
    {
        // creates a copy of the element in the queue.
        // this allows unlocking the queue before handeling
        // the element. handleQueueElement gets a reference to this
        // local t. the queue may be moved.
        T t = _queue.front();
        _queue.pop();

        _theCounter.popped();
        _theCounter.size( _queue.size() );

        _queueLock.unlock();

        {
            std::lock_guard<std::mutex> lock( _mutexHandler );
            if ( _handler )
            {
                _handler->handleQueueElement( t );
            }
        }
    }
    else
    {
        _queueLock.unlock();

        // we will be notified when an element is inserted
        std::unique_lock< std::mutex > waitLock( _operationLock );
        _elementInQueue.wait_for( waitLock, _stopLatency );
    }

    return true;
}

template< class T>
const ThreadQueueCounter& ThreadQueue<T>::getCounter() const
{
    return _theCounter;
}

template< class T>
ThreadQueueCounter& ThreadQueue<T>::getCounter()
{
    return _theCounter;
}

}}

#endif

