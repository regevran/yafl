
#ifndef EXECUTION_ONCE_H
#define EXECUTION_ONCE_H

#include "execution_base.h"

namespace infra {

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


