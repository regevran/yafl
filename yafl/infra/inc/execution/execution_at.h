
#ifndef EXECUTION_AT_H
#define EXECUTION_AT_H

#include "execution_base.h"
#include <memory>
#include <mutex>
#include <condition_variable>

namespace infra {


class Operation;

class ExecutionAt : public ExecutionBase
{
    public:
        // t is the time in epoch
        ExecutionAt( 
                unsigned long t1,
                unsigned long t2, 
                Operation* op
        );

        virtual ~ExecutionAt();

    public:
        virtual void stop(); 

    public:
        void owner( OwnerExecution<ExecutionAt>* );
        OwnerExecution<ExecutionAt>* owner();

    public:
        void setNewTimes( unsigned long t1, unsigned long t2 );

    public:
        virtual bool mainExecution();
        
    private:
        unsigned long               _t1; 
        unsigned long               _t2; 
        std::unique_ptr<Operation>  _op;

    private:
        std::mutex               _mutex;
        std::condition_variable  _stopCond; 
    private: 
        OwnerExecution<ExecutionAt>*  _owner;
}; 

}

#endif 


