
#include "execution_period.h"
#include "owner_execution.h"
#include <iostream>
#include "operation.h"
#include "msg.h"
#include <memory>

namespace rf{

ExecutionPeriod::ExecutionPeriod(
    Operation&  op,
    std::chrono::milliseconds period )
    : 
    _operation( op ),
    _period( new  std::atomic<std::chrono::milliseconds>( period ) ),
    _isPointer( true ),
    _owner( nullptr )
{ 
}

ExecutionPeriod::ExecutionPeriod(
        Operation&  op,
        std::atomic<std::chrono::milliseconds>&   period)
    :
    _operation( op ),
    _period( &period ),
    _isPointer( false ),
    _owner( nullptr )
{
}

ExecutionPeriod::~ExecutionPeriod()
{
    if ( _isPointer )
    {
        delete _period;
    }
}

void ExecutionPeriod::setPeriod( std::chrono::milliseconds newPeriod )
{
    _period->store( newPeriod );
}

bool ExecutionPeriod::mainExecution()
{
    bool continueOp = true;
    
    while ( ! isStopped() && continueOp )
    {
        // we will be notified when the execution is stopped or when period reached
        std::unique_lock< std::mutex > waitLock( _operationLock );
        _periodCondition.wait_for( waitLock, _period->load() );

        if ( ! isStopped() )
        {
            // the time has passed, now we need to operate
            continueOp = _operation.Operate();
        }
        else
        {
            continueOp = false;
        }
    }

    return continueOp;
}

void ExecutionPeriod::owner( OwnerExecution<ExecutionPeriod>* owner )
{
    _owner = owner;
}

OwnerExecution<ExecutionPeriod>* ExecutionPeriod::owner()
{
    return _owner;
}

void ExecutionPeriod::stop()
{
    ExecutionBase::stop();

    _periodCondition.notify_one();
}

void ExecutionPeriod::done()
{
    if ( _owner )
    {
        _owner->done( this );
    }
}

}

