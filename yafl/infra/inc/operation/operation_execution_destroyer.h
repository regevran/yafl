
#ifndef __OPERATION_EXECUTION_DESTROYER__
#define __OPERATION_EXECUTION_DESTROYER__


#include <mutex>
#include "operation.h"

namespace rf{ 

class ExecutionBase; 

class OperationExecutionDestroyer : public rf::Operation
{
    public:
        OperationExecutionDestroyer(); 
        virtual ~OperationExecutionDestroyer();

    public:
        virtual bool Operate();

    public:
        void setExecutionToDestroy( rf::ExecutionBase* );

    private:
        std::mutex                  _tillDeleted;
        std::mutex                  _toDestroyGuard;
        rf::ExecutionBase*          _toDestroy; 
};

}

#endif

