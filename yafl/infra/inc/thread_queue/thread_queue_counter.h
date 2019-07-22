
#ifndef __THREAD_QUEUE_COUNTER__
#define __THREAD_QUEUE_COUNTER__

#include <ostream>
#include <string>

namespace rf{
namespace thread_queue{

class ThreadQueueCounter
{
    public:
        ThreadQueueCounter( const std::string& qName, unsigned long capacity );
        ThreadQueueCounter( const ThreadQueueCounter& );
        ~ThreadQueueCounter();

        ThreadQueueCounter& operator =( const ThreadQueueCounter& rhs );

    public:
        void pushed( unsigned long count = 1 );
        void pushRequested( unsigned long count = 1 );
        void popped( unsigned long count = 1 );
        void dropped( unsigned long count = 1 ); 
        void size( unsigned long qSize ); 

    public:
        void reset();

    private:
        const std::string   _qName;
        unsigned long       _pushed;
        unsigned long       _pushRequest;
        unsigned long       _popped;
        unsigned long       _dropped; 
        unsigned long       _qSize;
        const unsigned long _capacity;
        unsigned long       _highestSize;

    friend std::ostream& operator << ( std::ostream&, const ThreadQueueCounter );
};

}}


#endif

