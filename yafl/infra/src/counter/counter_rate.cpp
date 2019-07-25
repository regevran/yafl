
#include "infra/inc/counter/counter_rate.h"
#include <cmath>
#include <iomanip>
#include <sys/timeb.h>

namespace infra{
namespace counter{

CounterRate::CounterRate( const std::string& name )
    :
    _bstarted( false ),
    _name( name )
{
}

CounterRate::CounterRate( const CounterRate& rhs )
{
    *this = rhs;
}

CounterRate::~CounterRate()
{
}

CounterRate& CounterRate::operator=( const CounterRate& rhs )
{
    _start = rhs._start;
    _end = rhs._end;
    _count = rhs._count;
    _bstarted = rhs._bstarted;
    _name = rhs._name;

    return *this;
}

void CounterRate::startCount()
{
    struct timeb timer_msec;
    if ( ! ftime( &timer_msec ) )
    {
        _start = 
            ((unsigned long long) timer_msec.time) * 1000ll +
            (unsigned long long) timer_msec.millitm;

        _bstarted = true;
    }
    else
    {
        _bstarted = false;
    }
}

void CounterRate::endCount()
{
    struct timeb timer_msec;
    if ( ! ftime( &timer_msec ) )
    {
        _end = 
            ((unsigned long long) timer_msec.time) * 1000ll +
            (unsigned long long) timer_msec.millitm;
    }
    else
    {
        _bstarted = false;
    }
}

void CounterRate::add( double amount )
{
    if ( ! _bstarted )
    {
        startCount();
    }
    _count += amount;
}

double CounterRate::getCount() const
{
    return _count;
}

double CounterRate::getRate() const
{
    double diffCount = _end - _start;

    if ( 0 != diffCount )
    {
        return _count / ( diffCount / 1000 );
    }
    else
    {
        return 0;
    }
}

std::ostream& operator << ( std::ostream& o, const CounterRate cr )
{
    double rate = cr.getRate();
    unsigned long rateFloored = std::floor(rate);
    unsigned long printRate = rateFloored - ( rateFloored % 100000 );


    o.imbue( std::locale("en_US.UTF8") );
    o << "[" << cr._name << "] rate (floored): " << printRate;
    return o;
}


}}

