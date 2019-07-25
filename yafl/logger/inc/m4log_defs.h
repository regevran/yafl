
#pragma once

#include "infra/inc/thread_queue/thread_queue.h"
#include "logger/m4log/BulkLog.h"

namespace yafl{
namespace log{

class Log;
class LogHandler;

// THE log-q for Log messages
//extern infra::thread_queue::ThreadQueue<Log>    g_logQ;
extern BulkLog g_logQ;


}}

