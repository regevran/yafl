
#ifndef __THREAD_QUEUE_T1__
#define __THREAD_QUEUE_T1__

#include "container/cyclic_queue.h"
#include "execution/execution_forever.h"
#include "execution/owner_execution.h"
#include "joinable.h"
#include "msg.h"
#include "operation/operation.h"
#include "thread_queue_counter.h"
#include "thread_queue_handler.h"
#include "thread_queue_owner.h"
#include <condition_variable>
#include <mutex>

namespace infra{
namespace thread_queue{

template<class T,unsigned long SIZE>
class ThreadQueueT1 : 
    public infra::Operation,
    public infra::Joinable,
    public infra::OwnerExecution< infra::ExecutionForever > 
{
    public:
        ThreadQueueT1( 
                const std::string& qName,
                ThreadQueueHandler<T>* handler,
                std::chrono::milliseconds stopLatency = std::chrono::milliseconds(1000),
                ThreadQueueOwnerT1<T,SIZE>* owner = nullptr
       );

       virtual ~ThreadQueueT1();

    public:
       ThreadQueueHandler<T>* getHandler();

       // sets new handler, returns the old handler
       ThreadQueueHandler<T>* replaceHandler( ThreadQueueHandler<T>* newHandler );

    public:
        virtual void start();
        virtual void stop();
        virtual void join();
        virtual void detach();

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
        ThreadQueueHandler<T>*                    _handler;
        infra::container::CyclicQueue<T,SIZE>     _queue;

    private:
        // for operate
        std::mutex                  _operationLock;
        std::condition_variable     _elementInQueue;
        std::chrono::milliseconds   _stopLatency;

    private:
        infra::ExecutionForever        _readerExecution; 

    private:
        ThreadQueueOwnerT1<T,SIZE>*        _owner;

    private:
        const std::string           _qName;
        ThreadQueueCounter          _theCounter;
};


template<class T,unsigned long SIZE>
ThreadQueueT1<T,SIZE>::ThreadQueueT1( 
        const std::string& qName,
        ThreadQueueHandler<T>* handler,
        std::chrono::milliseconds stopLatency,
        ThreadQueueOwnerT1<T,SIZE>* owner
) : 
    _handler( handler ),
    _stopLatency( stopLatency ),
    _readerExecution( *this, nullptr, nullptr, std::chrono::microseconds(0) ),
    _owner( owner ),
    _qName( qName ),
    _theCounter( _qName, SIZE )
{
    _readerExecution.owner( this );
}

template<class T,unsigned long SIZE>
ThreadQueueT1<T,SIZE>::~ThreadQueueT1()
{
}

template<class T,unsigned long SIZE>
ThreadQueueHandler<T>* ThreadQueueT1<T,SIZE>::getHandler()
{
    return _handler;
}

template<class T,unsigned long SIZE>
ThreadQueueHandler<T>* ThreadQueueT1<T,SIZE>::replaceHandler( ThreadQueueHandler<T>* newHandler )
{
    _readerExecution.pause();

    ThreadQueueHandler<T>* ret = _handler;
    _handler = newHandler;

    _readerExecution.resume();

    return ret;
}

template<class T,unsigned long SIZE>
void ThreadQueueT1<T,SIZE>::start()
{
    _readerExecution.start();

    if ( _owner )
    {
        _owner->started( this );
    }
}

template<class T,unsigned long SIZE>
void ThreadQueueT1<T,SIZE>::stop()
{
    _readerExecution.stop();

    if ( _owner )
    {
        _owner->stopped( this );
    }
}

template<class T,unsigned long SIZE>
void ThreadQueueT1<T,SIZE>::join()
{
    _readerExecution.join();
}

template<class T,unsigned long SIZE>
void ThreadQueueT1<T,SIZE>::detach()
{
    _readerExecution.detach();
}

template<class T,unsigned long SIZE>
void ThreadQueueT1<T,SIZE>::done( ExecutionForever* )
{
    if ( _owner )
    {
        _owner->done( this );
    }
}

template<class T,unsigned long SIZE>
bool ThreadQueueT1<T,SIZE>::push( const T& t )
{
    bool ret;

    _theCounter.pushRequested();

    if ( _queue.empty() )
    {
        _elementInQueue.notify_one();
    }

    bool bPushed = _queue.push( t );

    if ( bPushed )
    {
        _theCounter.pushed();
        _theCounter.size( _queue.size() ); 
        ret = true;
    }
    else
    {
        _theCounter.dropped();
        ret = false;
    }

    return ret;
}

template<class T,unsigned long SIZE>
bool ThreadQueueT1<T,SIZE>::empty()
{
    return _queue.empty();
}

template<class T,unsigned long SIZE>
const std::string& ThreadQueueT1<T,SIZE>::name() const
{
    return _qName;
} 

template<class T,unsigned long SIZE>
bool ThreadQueueT1<T,SIZE>::Operate()
{
    if ( ! _queue.empty() )
    {
        T& t = _queue.pop();

        _theCounter.popped();
        _theCounter.size( _queue.size() );

        // note that future pushes may write on the referenced pooped element
        if ( _handler )
        {
            _handler->handleQueueElement( t );
        }
    }
    else
    {
        // we will be notified when an element is inserted
        std::unique_lock< std::mutex > waitLock( _operationLock );
        _elementInQueue.wait_for( waitLock, _stopLatency );
    }

    return true;
}

template<class T,unsigned long SIZE>
const ThreadQueueCounter& ThreadQueueT1<T,SIZE>::getCounter() const
{
    return _theCounter;
}

template<class T,unsigned long SIZE>
ThreadQueueCounter& ThreadQueueT1<T,SIZE>::getCounter()
{
    return _theCounter;
}

}}

#endif

