//==============================================================================
//  File name	:	execution_at.h
//  Author:		:	Ran Regev
//  date		: 	11/10/2015
//==============================================================================
// Notes: calls operate at time1 and again on time2.
// The general case of this execution is to call operate on [t1,t2,...,tn]
// but currently we have only a use case where n=2.
// in the general case, it is probably best to implement the Operation as a state
// machine that each call to operatae() ends in a transition to another state.
// ExecutionAt is responsible to delete the operation supplied to it.
//==============================================================================

#ifndef EXECUTION_AT_H
#define EXECUTION_AT_H

#include "execution_base.h"
#include <memory>
#include <mutex>
#include <condition_variable>

namespace rf {


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


