

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
    _bulk.push( l );
}

}}

