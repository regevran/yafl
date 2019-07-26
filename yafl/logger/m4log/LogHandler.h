
#pragma once

#include "BulkLog.h"
#include "logger/inc/m4log_defs.h"
#include "logger/inc/log.h"
#include "infra/inc/thread_queue/thread_queue_handler.h"

namespace yafl{
namespace log{


class LogHandler : public infra::thread_queue::ThreadQueueHandler< Log >
{
    public:
        LogHandler( const std::string& logFileName );
        ~LogHandler();

    public:
        virtual void handleQueueElement( Log& );

    private:
        BulkLog<LOG_BULK_SIZE>     _bulk;
};


}}

