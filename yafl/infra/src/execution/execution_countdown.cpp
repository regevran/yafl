
#include "execution_countdown.h"
#include <iostream>
#include "operation.h"
#include "msg.h"

 namespace infra{

ExecutionCountdown::ExecutionCountdown(
        std::unique_ptr<Operation> op,
        std::chrono::milliseconds countDown, 
        std::chrono::milliseconds stopLatency )
    : 
    _operation( std::move(op) ),
    _countDown( countDown ),
    _stopLatency( stopLatency )
{ 
    // set to 1 second if the user supplied zero
    if ( std::chrono::milliseconds(0) == _stopLatency )
    {
        _stopLatency = std::chrono::milliseconds(100);
    }
}

ExecutionCountdown::~ExecutionCountdown()
{
}

bool ExecutionCountdown::mainExecution()
{
    // escape, nothing to do
    if ( ! _operation )
    {
        return false;
    }

    // number of rounds to complete the countdown
    auto rounds = _countDown / _stopLatency;

    for ( decltype(rounds) i = 0; i < rounds; ++i )
    {
        // each round of _stopLatency length
        std::this_thread::sleep_for( _stopLatency );

        // when stopped, exit
        if ( isStopped() )
        {
            return true;
        } 
    }

    // the time has passed, now we need to operate
    bool ret = _operation->Operate();

    return ret;
}

}

