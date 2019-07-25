
#ifndef EXECUTION_FOREVER_H
#define EXECUTION_FOREVER_H

#include "execution_base.h"
#include <mutex>

namespace infra {

class Operation; 

class ExecutionForever : public ExecutionBase
{
    public:
        ExecutionForever( 
                Operation& loopOp, 
                Operation* preOp = nullptr,
                Operation* postOp = nullptr,
                std::chrono::microseconds sleepTimeM = std::chrono::microseconds(0)
        );
        virtual ~ExecutionForever();

    public:
        virtual void stop();
        virtual void update();

        // pause returns only after the execution is paused
        // i.e. no call to operate is done after pause returned
        void pause();
        void resume();

        virtual void done();

    public:
        // return old operation
        Operation* setPreOperation( Operation* preOp );
        Operation* setPostOperation( Operation* postOp ); 
        void setSleepTime( std::chrono::milliseconds sleepTimeM );

    public:
        void owner( OwnerExecution<ExecutionForever>* );
        OwnerExecution<ExecutionForever>* owner(); 

    private:
        virtual bool mainExecution();

    private:
        Operation&                              _loopOp;
        Operation*                              _pPreOp;
        Operation*                              _pPostOp;
        std::chrono::microseconds               _sleepTimeM;
        bool                                    _shouldSleep;
        OwnerExecution<ExecutionForever>*       _owner;
        std::mutex                              _pause;
};

}

#endif 


