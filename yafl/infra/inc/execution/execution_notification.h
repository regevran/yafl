//==============================================================================
//  File name	:	execution_at.h
//  Author:		:	Ran Regev
//  date		: 	21/10/2015
//==============================================================================
// Notes: executes the operation upon each call to Notify()
//==============================================================================

#ifndef __EXECUTION_NOTIFICATION__
#define __EXECUTION_NOTIFICATION__

#include "execution_base.h"
#include <condition_variable>
#include <mutex>

namespace rf{

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
