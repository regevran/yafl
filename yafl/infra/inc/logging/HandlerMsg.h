
#pragma once

#include "thread_queue/thread_queue_handler.h"
#include "msg.h"

namespace Logging {

class HandlerMsg : public infra::thread_queue::ThreadQueueHandler<MSG>
{
    public:
        HandlerMsg();
        virtual ~HandlerMsg();

    public:
        virtual void handleQueueElement( MSG& );
};


}

