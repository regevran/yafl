//==============================================================================
//  File name	        :	execution_suspend.cpp
//  Author:		:	Ran Regev
//  date		: 	21/11/2013
//==============================================================================
// Notes:  Implement the exection-then-suspend exeution thread
//==============================================================================

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
#include "execution/execution_suspend.h"
#include "operation/operation.h"

namespace rf {

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






