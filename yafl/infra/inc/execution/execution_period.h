
#ifndef __EXECUTION_PERIOD__
#define __EXECUTION_PERIOD__

#include "execution_base.h"
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace infra {

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

