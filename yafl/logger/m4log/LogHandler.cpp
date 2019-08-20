

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
        l.timestamp( true );
    }
    else
    {
        l.timestamp( false );
   
        ++ _timeSampleCounter;
        
        if ( TIMESTAMP_DELTA_MESSAGES == _timeSampleCounter )
        {
            _timeSampleCounter = 0;
        }
    }

    _bulk.push( l );
}

}}

