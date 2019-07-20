
#ifndef __EXECUTION_COUNT_DOWM__
#define __EXECUTION_COUNT_DOWM__

#include "execution_base.h"
#include <chrono>

namespace rf
{

class Operation;

class ExecutionCountdown : public ExecutionBase
{
    public: 
        ExecutionCountdown(
                std::unique_ptr<Operation>  op,
                std::chrono::milliseconds   countDown, 
                std::chrono::milliseconds   stopLatency = std::chrono::milliseconds(100)
        );
        virtual ~ExecutionCountdown();

    // ExecutionBase
    public:
        virtual bool mainExecution();

    private: 
        std::unique_ptr<Operation>      _operation; 
        std::chrono::milliseconds       _countDown;
        std::chrono::milliseconds       _stopLatency;
};
    
}


#endif

