

//==============================================================================
// Notes: Execution with two operations with suspention between them.
// To exit the suspention, and continue to the second operation, just call 
// Stop on this object.
// It is possible to achive 'wait till notification' by setting pre=null, post=op
// And 'execute then wait' by setting pre=op, post=null.
// WARNING: Calling Stop() before Start(), calling multiple times to Start()
// and/or Stop() has undefined behavior.
//==============================================================================

#ifndef EXECUTION_SUSPEND_H
#define EXECUTION_SUSPEND_H

#include <mutex>
#include "execution_base.h"

 namespace infra {

class Operation;

class ExecutionSuspend : public ExecutionBase
{
    public:
        ExecutionSuspend( Operation* pre, Operation* post );
        virtual ~ExecutionSuspend();

    public:
        virtual void start();
        virtual void stop(); 

    public:
        virtual bool mainExecution();
        
    private:
        std::mutex _mutex;
        Operation* _pre;
        Operation* _post;

}; 

}

#endif 


