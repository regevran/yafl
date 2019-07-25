
#ifndef __EXECUTION_COUNT_H__
#define __EXECUTION_COUNT_H__

#include "execution_base.h"

 namespace infra {

class Operation;

class ExecutionCount : public ExecutionBase
{
public:
    ExecutionCount( Operation&, unsigned long count );
    virtual ~ExecutionCount(); 

    virtual bool mainExecution();

private:
    Operation&      _theOperation;
    unsigned long   _count;
};

}

#endif 


