
//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include "infra/inc/execution/execution_count.h"
#include "infra/inc/operation/operation.h"

 namespace infra {

ExecutionCount::ExecutionCount( Operation& op, unsigned long count )
    : 
    _theOperation( op ),
    _count( count )
{
}

ExecutionCount::~ExecutionCount()
{
}

bool ExecutionCount::mainExecution()
{
    bool bContinue( true );

    while ( ( _count > 0 ) && ( bContinue ) && ( ! isStopped() ) ) 
    {
        bContinue = _theOperation.Operate();
        -- _count; 
    }

    return true;
}

}

