
#include "Logger/inc/log.h"
#include "series.h"
#include <thread>
#include <log4cpp/PropertyConfigurator.hh>
#include "Logger/inc/a.h"

Series::Series( 
            unsigned long startCountAt,
            unsigned long stopCountAt )
    : 
    _callCount( 0 ),
    _startCountAt( startCountAt ),
    _stopCountAt( stopCountAt ) //,
//    _logger( log4cpp::Category::getInstance( "serieslog" ) )
{
    //log4cpp::PropertyConfigurator::configure("../log4cpp.ini");

    A a;
    a.f();
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
        _start = std::chrono::steady_clock::now();
    } 

    // the work
    YAFL_LOG( YAFL_INFO, "dana", "fast was called: ", _callCount, " times" ); 
    std::this_thread::sleep_for( std::chrono::milliseconds( 3 ) );
    // end the work

    if ( _stopCountAt == _callCount )
    {
        _end = std::chrono::steady_clock::now();
    }
}

void Series::log4cpp()
{

    /*
    ++ _callCount;

    if ( _startCountAt == _callCount )
    {
        _start = std::chrono::steady_clock::now();
    } 

    // the work
    _logger << log4cpp::Priority::DEBUG << "slow-check" << "log4cpp was called: " << _callCount << " times"; 
    // end the work

    if ( _stopCountAt == _callCount )
    {
        _end = std::chrono::steady_clock::now();
    }
    */
}

void Series::getTimes( 
        std::chrono::steady_clock::time_point& start,
        std::chrono::steady_clock::time_point& end
)
{
    start = _start;
    end = _end;
}

