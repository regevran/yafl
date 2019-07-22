
#ifndef __THREAD_QUEUE_HANDLER__
#define __THREAD_QUEUE_HANDLER__

namespace rf{
namespace thread_queue{

template <class T>
class ThreadQueueHandler
{
    public:
        ThreadQueueHandler(){}
        virtual ~ThreadQueueHandler(){}

    public:
        virtual void handleQueueElement( T& ) = 0;
}; 

}}

#endif

