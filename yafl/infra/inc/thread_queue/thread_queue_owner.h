
#ifndef __THREAD__QUEUE_OWNER__
#define __THREAD__QUEUE_OWNER__


namespace infra{
namespace thread_queue{

template <class T> class ThreadQueue;
template <class T,unsigned long SIZE> class ThreadQueueT1;

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

template <class T,unsigned long SIZE>
class ThreadQueueOwnerT1
{
    public:
        ThreadQueueOwnerT1(){}
        virtual ~ThreadQueueOwnerT1(){}
        
    public:
        virtual void started( ThreadQueueT1<T,SIZE>* ){}
        virtual void stopped( ThreadQueueT1<T,SIZE>* ){}
        virtual void done( ThreadQueueT1<T,SIZE>* ){}
};
}}

#endif


