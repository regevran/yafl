

#include "LogHandler.h"
#include <iostream>

namespace yafl{
namespace log{


LogHandler::LogHandler( const std::string& logFileName )
    : _bulk( logFileName )
{
}

LogHandler::~LogHandler()
{
}

void LogHandler::handleQueueElement( Log& l )
{
    // system call not every message
    // but rather, every TIMESTAMP_DELTA_MESSAGES messages
    if ( 0 == _timeSampleCounter )
    {
        _ticksSinceEpoch = 
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count();

        l.timestamp( _ticksSinceEpoch );

        ++ _timeSampleCounter;
    }
    else
    {
        l.timestamp( _ticksSinceEpoch );
   
        ++ _timeSampleCounter;

        if ( TIMESTAMP_DELTA_MESSAGES == _timeSampleCounter )
        {
            _timeSampleCounter = 0;
        }
    }

    _bulk.push( l );
}

}}

