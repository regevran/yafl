//==============================================================================
//  File name	        :	execution_once.h
//  Author:		:	Ran Regev
//  date		: 	29/08/2013
//==============================================================================
// Notes: Execution of a single operation 	
//==============================================================================

#ifndef EXECUTION_ONCE_H
#define EXECUTION_ONCE_H

#include "execution_base.h"

namespace rf {

class Operation;

class ExecutionOnce : public ExecutionBase
{
public:
    ExecutionOnce( Operation& );
    virtual ~ExecutionOnce(); 

    virtual bool MainExecution();

private:
    Operation& _theOperation;
};


}







#endif 


