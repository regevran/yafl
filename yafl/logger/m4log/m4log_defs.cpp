

#include "logger/inc/m4log_defs.h"
#include "logger/inc/log.h"
#include "LogHandler.h"
#include <string>



namespace yafl{
namespace log{

std::string     g_logFile( "fast.log" );

LogHandler g_logHandler( g_logFile );
infra::thread_queue::ThreadQueue<Log> g_logQ( "logQ", 100000000, &g_logHandler );



}}

