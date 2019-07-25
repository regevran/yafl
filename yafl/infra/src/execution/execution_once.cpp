
#include "infra/inc/execution/execution_once.h"
#include "infra/inc/operation/operation.h"

 namespace infra {

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

