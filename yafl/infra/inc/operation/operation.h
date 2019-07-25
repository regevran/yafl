
#ifndef OPERATION_H
#define OPERATION_H

namespace infra{

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


