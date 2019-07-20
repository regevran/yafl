

#include "execution_notification.h"
#include "operation/operation.h"

namespace rf{


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

