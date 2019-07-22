//==============================================================================
//  File name	        :	execution_forever.h
//  Author:		:	Ran Regev
//  date		: 	28/08/2013
//==============================================================================
// Notes: forever execution running context 	
//==============================================================================

#ifndef EXECUTION_FOREVER_H
#define EXECUTION_FOREVER_H

#include "execution_base.h"

namespace infra {

class Operation; 

class ExecutionForever : public ExecutionBase
{
public:
    ExecutionForever( 
            Operation& loopOp, 
            Operation* preOp = nullptr,
            Operation* postOp = nullptr,
            unsigned long sleepTimeS = 0
    );
    virtual ~ExecutionForever();

    virtual void stop();

public:
    // return old operation
    Operation* setPreOperation( Operation* preOp );
    Operation* setPostOperation( Operation* postOp ); 
    void setSleepTime( unsigned long sleepTimeS );


private:
    virtual bool mainExecution();

private:
    Operation&              _loopOp;
    Operation*              _pPreOp;
    Operation*              _pPostOp;
    unsigned long           _sleepTimeS;
    std::chrono::time_point<std::chrono::system_clock> _absoluteSleep;
};

}

#endif 


