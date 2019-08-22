
#include "logger/inc/log.h"
#include "logger/inc/m4log_defs.h"
#include "series.h"
#include <thread>

Series::Series( 
            unsigned long startCountAt,
            unsigned long stopCountAt )
    : 
    _callCount( 0 ),
    _startCountAt( startCountAt ),
    _stopCountAt( stopCountAt )
{
}

Series::~Series()
{
}

void Series::reset()
{
    _callCount = 0;
}

void Series::fast()
{
    ++ _callCount;

    if ( _startCountAt == _callCount )
    {
        _start = std::chrono::high_resolution_clock::now();
    } 

    // the work
    switch ( _callCount % 4 )
    {
        case 0: 
        {
            LOG_DEMO_DEBUG( "fast was called: ", _callCount, " times" ); 
        }
        break;

        case 1: 
        {
            LOG_DEMO_ERROR( "call count can't be ", _callCount, " but it is!" ); 
        }
        break;

        case 2: 
        {
            LOG_DEMO_WARNING( _callCount, " is odd" ); 
        }
        break;

        case 3: 
        {
            LOG_DEMO_INFO( "start count at:", _startCountAt, "; stop count at: ", _stopCountAt, "; current count: ", _callCount ); 
        }
        break;
    }
    // end the work

    if ( _stopCountAt == _callCount )
    {
        _end = std::chrono::high_resolution_clock::now();
    }
}

unsigned long Series::getCallCount() const
{
    if ( _callCount > _stopCountAt - _startCountAt )
    {
        return _stopCountAt - _startCountAt;
    }
    else
    {
        return _callCount;
    }
}

void Series::getTimes( 
        std::chrono::high_resolution_clock::time_point& start,
        std::chrono::high_resolution_clock::time_point& end
)
{
    start = _start;
    end = _end;
}

