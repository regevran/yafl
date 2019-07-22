
#include <iomanip>
#include "thread_queue/thread_queue_counter.h"

namespace rf{
namespace thread_queue{

ThreadQueueCounter::ThreadQueueCounter(  const std::string& qName, unsigned long capacity )
    : 
    _qName( qName ),
    _capacity( capacity )
{
    reset();
}

ThreadQueueCounter::ThreadQueueCounter( const ThreadQueueCounter& rhs )
    :
    _qName( rhs._qName ),
    _capacity( rhs._capacity )
{
    *this = rhs;
}

ThreadQueueCounter& ThreadQueueCounter::operator =( const ThreadQueueCounter& rhs )
{
    _pushed = rhs._pushed;
    _pushRequest = rhs._pushRequest;
    _popped = rhs._popped;
    _dropped = rhs._dropped; 
    _qSize = rhs._qSize;
    _highestSize = rhs._highestSize;

    return *this;
}

ThreadQueueCounter::~ThreadQueueCounter()
{
}

void ThreadQueueCounter::reset()
{
    _pushed = 0;
    _pushRequest = 0;
    _popped = 0;
    _dropped = 0; 
    _highestSize = 0;
    _qSize = 0;
}

void ThreadQueueCounter::pushed( unsigned long counter )
{
    _pushed += counter;
}

void ThreadQueueCounter::pushRequested( unsigned long count )
{
    _pushRequest += count;
}

void ThreadQueueCounter::popped( unsigned long counter )
{
    _popped += counter;
}

void ThreadQueueCounter::dropped( unsigned long counter ) 
{
    _dropped += counter;
}

void ThreadQueueCounter::size( unsigned long qSize ) 
{
    _qSize = qSize;

    if ( _qSize > _highestSize )
    {
        _highestSize = _qSize;
    }
}

std::ostream& operator << ( std::ostream& o, const ThreadQueueCounter tqc )
{
    o.imbue(std::locale(""));
    o << std::endl <<
        tqc._qName << std::endl <<
        "capacity: " << std::setw(20) << std::right << tqc._capacity << std::endl <<
        "current: " << std::setw(20) << std::right << tqc._qSize << std::endl << 
        "highest: " << std::setw(20) << std::right << tqc._highestSize << std::endl <<
        "pushed: " << std::setw(20) << std::right << tqc._pushed << std::endl <<
        "push requests: " << std::setw(20) << std::right << tqc._pushRequest << std::endl <<
        "popped: " << std::setw(20) << std::right << tqc._popped << std::endl <<
        "dropped: " << std::setw(20) << std::right << tqc._dropped << std::endl;

   if ( tqc._pushRequest )
   { 
       double dropped = tqc._dropped;
       double pushRequest = tqc._pushRequest;
       o << std::fixed << "dropped(%): " <<  std::setprecision(2) << ( dropped / pushRequest ) * 100 << std::endl;
   }

   return o;
}

}}

