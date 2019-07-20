//==============================================================================
//  File name	        :	execution_count.cpp
//  Author:		:	Ran Regev
//  date		: 	29/08/2013
//==============================================================================
// Notes:  Implementation of execution count
//==============================================================================

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include "execution/execution_count.h"
#include "operation/operation.h"

namespace rf {

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
    for (; _count > 0; -- _count )
    {
        _theOperation.Operate();
    }

    return true;
}

}

