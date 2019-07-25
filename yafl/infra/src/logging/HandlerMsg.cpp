

#include "logging/HandlerMsg.h"

namespace Logging {

HandlerMsg::HandlerMsg()
{
}

HandlerMsg::~HandlerMsg()
{
}

void HandlerMsg::handleQueueElement( MSG& msg )
{
    std::cout << "here" << std::endl;
    std::cout << msg;
}

}

