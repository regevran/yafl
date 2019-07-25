

#include "LogHandler.h"
#include <iostream>

namespace yafl{
namespace log{


LogHandler::LogHandler( 
    const std::string& logFileName,
    unsigned long bulkSize 
)
    : _bulk( logFileName, bulkSize )
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

