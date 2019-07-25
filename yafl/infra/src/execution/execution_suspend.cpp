
#include "infra/inc/execution/execution_suspend.h"
#include "infra/inc/operation/operation.h"

namespace infra {

ExecutionSuspend::ExecutionSuspend( Operation* pre, Operation* post )
    : 
    _pre( pre ),
    _post( post )
{
}

ExecutionSuspend::~ExecutionSuspend()
{
}

void ExecutionSuspend::start()
{
    _mutex.try_lock();

    ExecutionBase::start();
}

void ExecutionSuspend::stop()
{
    ExecutionBase::stop();

    _mutex.unlock();
} 
 
bool ExecutionSuspend::mainExecution()
{
    bool retVal( true );

    if ( _pre )
    {
        retVal = _pre->Operate();
    }

    // this will be released when Stop is called
    _mutex.lock();

    if ( _post )
    {
        retVal &= _post->Operate();
    }

    return retVal;
}


}






