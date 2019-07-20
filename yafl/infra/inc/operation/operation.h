//==============================================================================
//  File name	        :	operation.h
//  Author:		:	Ran Regev
//  date		: 	28/08/2013
//==============================================================================
// Notes: Operation to execute must end with a reasonable time,
// letting the execution manager a chance to stop the execution.
// do not write code that blocks forever!.
//==============================================================================

#ifndef OPERATION_H
#define OPERATION_H

namespace rf{

class Operation
{
    public:
        Operation() {}
        virtual ~Operation() {};

    public:
        // operate is called by the execution
        // at the correct time
        virtual bool Operate() = 0;

    public:
        // the execution can update the operation
        // that there is a new data to grab.
        // the operation is reponsible to get it
        virtual void Update(){} 
};

}

#endif 


