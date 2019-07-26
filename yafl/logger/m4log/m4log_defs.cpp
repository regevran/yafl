

#include "logger/inc/m4log_defs.h"
#include "logger/inc/log.h"
#include "LogHandler.h"
#include <string>



namespace yafl{
namespace log{

std::string     g_logFile( "fast.log" );

/*
LogHandler g_logHandler( g_logFile, 10000 );
infra::thread_queue::ThreadQueue<Log> g_logQ( "logQ", 10000000, &g_logHandler );
*/

yafl::log::BulkLog<LOG_BULK_SIZE> g_logQ( g_logFile );


}}

