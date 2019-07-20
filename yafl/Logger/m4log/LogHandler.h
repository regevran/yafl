
#pragma once

#include "BulkLog.h"
#include "Logger/inc/log.h"
#include "infra/inc/thread_queue/thread_queue_handler.h"

namespace yafl{
namespace log{


class LogHandler : public infra::thread_queue::ThreadQueueHandler< Log >
{
    public:
        LogHandler( 
                const std::string& logFileName,
                unsigned long bulkSize 
        );
        ~LogHandler();

    public:
        virtual void handleQueueElement( Log& );

    private:
        BulkLog     _bulk;
};


}}

