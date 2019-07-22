//==============================================================================
//  File name	:	execution_base.h
//  Author:		:	Ran Regev
//  date		: 	28/08/2013
//==============================================================================
// Notes: base class for all radifow executions 	
//==============================================================================

#ifndef EXECUTION_BASE_H
#define EXECUTION_BASE_H

#include <thread>
#include "infra/inc/joinable.h"

namespace infra {

template<class E> class OwnerExecution;

class ExecutionBase : public infra::Joinable
{
    public:
        ExecutionBase();
        virtual ~ExecutionBase();

        static void mainEntryPoint( ExecutionBase& );

    public:
        virtual void start();
        virtual void stop();
        virtual void join();

    public:
        virtual void detach();

    public:
        bool isStopped(); 
        virtual void done();

    public:
        bool isSuccess();

    public:
        void owner( OwnerExecution<ExecutionBase>* );
        OwnerExecution<ExecutionBase>* owner();

    private:
        virtual bool mainExecution() = 0;

    private:
        bool                            _isStopped;
        std::thread                     _thisExecutionThread;
        bool                            _endStatus;
        OwnerExecution<ExecutionBase>*  _owner;
}; 

}

#endif 


