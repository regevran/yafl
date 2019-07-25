
//==============================================================================
// Notes: executes the operation upon each call to notify()
//==============================================================================

#ifndef __EXECUTION_NOTIFICATION__
#define __EXECUTION_NOTIFICATION__

#include "execution_base.h"
#include <condition_variable>
#include <mutex>

 namespace infra{

class Operation;

class ExecutionNotification : public ExecutionBase
{
    public:
        ExecutionNotification( Operation& ); 
        ~ExecutionNotification(); 

    private:
        virtual bool mainExecution();

    public:
        virtual void stop();
        void notify();

    private:
        Operation&                  _op;
        std::mutex                  _condLock;
        std::condition_variable     _workToDo; 
};

}

#endif
