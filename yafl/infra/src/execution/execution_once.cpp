//==============================================================================
//  File name	        :	execution_once.cpp
//  Author:		:	Ran Regev
//  date		: 	29/08/2013
//==============================================================================
// Notes:  Implementation of execution once
//==============================================================================

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include "execution/execution_once.h"
#include "operation/operation.h"

namespace rf {

ExecutionOnce::ExecutionOnce( Operation& op )
    : _theOperation( op )
{
}

ExecutionOnce::~ExecutionOnce()
{
}

bool ExecutionOnce::MainExecution()
{
    return _theOperation.Operate();
}

}

