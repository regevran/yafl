//==============================================================================
//  File name	:	execution_period.h
//  Author:		:	Ran Regev
//  date		: 	10/05/2017
//==============================================================================
// Notes: calls Operate() every period
// well suites for operations that should be done once in a while.
// e.g. cleanning missions.
//==============================================================================
//
#ifndef __EXECUTION_PERIOD__
#define __EXECUTION_PERIOD__

#include "execution_base.h"
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace rf
{

class Operation;

class ExecutionPeriod : public ExecutionBase
{
    public: 
        ExecutionPeriod(
                Operation&  op,
                std::chrono::milliseconds   period
        );

        ExecutionPeriod(
                Operation&  op,
                 std::atomic<std::chrono::milliseconds>& period
        );
         
        virtual ~ExecutionPeriod();

    public:
        void setPeriod( std::chrono::milliseconds newPeriod ); 

    public:
        virtual bool mainExecution();

    public:
        void owner( OwnerExecution<ExecutionPeriod>* );
        OwnerExecution<ExecutionPeriod>* owner(); 

    public:
        virtual void stop();
        virtual void done();

    private: 
        Operation&                                                    _operation; 
        std::atomic<std::chrono::milliseconds>*                       _period;
        bool                                                          _isPointer;

    private:
        std::mutex                          _operationLock;
        std::condition_variable             _periodCondition;
        OwnerExecution<ExecutionPeriod>*    _owner;
};
    
}


#endif

