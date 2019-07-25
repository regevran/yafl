
#include "operation_execution_destroyer.h"
#include "execution/execution_base.h"
#include "msg.h"

namespace rf{

OperationExecutionDestroyer::OperationExecutionDestroyer()
    : _toDestroy( nullptr )
{
}

OperationExecutionDestroyer::~OperationExecutionDestroyer()
{
}

bool OperationExecutionDestroyer::Operate()
{
    std::lock_guard<std::mutex> lg( _toDestroyGuard );

    if ( _toDestroy )
    {
        RF_LOG_DEBUG(  "waiting for the execution ", std::hex, _toDestroy, " to join..." );
        _toDestroy->join(); 
        RF_LOG_DEBUG( std::hex, _toDestroy, " joined" );

        delete _toDestroy; 
        RF_LOG_DEBUG( std::hex, _toDestroy, " deleted" );

        _toDestroy = nullptr;
        _tillDeleted.unlock();
    }
    else
    {
        RF_LOG_INFO( "nothing to destroy" );
        return false;
    }

    return true;
}

void OperationExecutionDestroyer::setExecutionToDestroy( rf::ExecutionBase* e )
{
    std::lock_guard<std::mutex> lg( _toDestroyGuard );
    _tillDeleted.lock(); 

    if ( _toDestroy != nullptr )
    {
        RF_LOG_ERROR( "Impossible situation: setting new execution to delete before deleting the last one!" );
    }
    
    _toDestroy = e; 
}

}

