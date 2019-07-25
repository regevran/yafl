

#include "infra/inc/execution/execution_notification.h"
#include "infra/inc/operation/operation.h"

 namespace infra{


ExecutionNotification::ExecutionNotification( Operation& op )
    : _op( op )
{
}
 
ExecutionNotification::~ExecutionNotification()
{
}
 
void ExecutionNotification::stop()
{
    ExecutionBase::stop();
    notify();
}

void ExecutionNotification::notify()
{
    _workToDo.notify_one();
}

bool ExecutionNotification::mainExecution()
{
    bool isOK( true );

    while ( ! isStopped() && isOK )
    {
        // wait till someone wake us
        //LOG_INFRA_INFO( "going to sleep until my prince will come" );
        std::unique_lock< std::mutex > lg( _condLock );
        _workToDo.wait( lg );
        
        if ( ! isStopped() )
        {
            isOK = _op.Operate(); 
        }
    }

    return isOK;
}

}

