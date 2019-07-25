
#ifndef OPERATION_EXAMPLE_H
#define OPERATION_EXAMPLE_H


#include "operation.h"

// The example operation incraement-decrement the value of
// a counter between 'min' and 'max' and sleeps.
// it demonstrate an 'atomic' operation that ends
// within a resonable time
class OperationExample : public rf::Operation
{
public:
    OperationExample( unsigned int min, unsigned int max, unsigned char sleepTime  );
    virtual ~OperationExample();

public:
    virtual bool Operate();
    unsigned char GetCounter();
    
private:
    unsigned char _counter;
    unsigned int  _min;
    unsigned int  _max;
    unsigned char _sleepTime;

    // true == increment; false == decrement
    bool          _direction;
};


#endif 


