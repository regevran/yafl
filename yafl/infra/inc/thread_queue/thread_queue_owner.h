
#ifndef __THREAD__QUEUE_OWNER__
#define __THREAD__QUEUE_OWNER__


namespace rf{
namespace thread_queue{

template <class T> class ThreadQueue;

template <class T>
class ThreadQueueOwner
{
    public:
        ThreadQueueOwner(){}
        virtual ~ThreadQueueOwner(){}
        
    public:
        virtual void started( ThreadQueue<T>* ){}
        virtual void stopped( ThreadQueue<T>* ){}
        virtual void done( ThreadQueue<T>* ){}
};

}}

#endif


