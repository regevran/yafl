
#include "operation_example.h"
#include <iostream>
#include <ostream>
#include <thread>
#include "msg.h"

OperationExample::OperationExample( unsigned int min, unsigned int max, unsigned char sleepTime )
{
    if ( max < min )
    {
        unsigned char temp( max );
        max = min;
        min = temp;
    }

    _min = min;
    _max = max;
    _sleepTime = 1000 * sleepTime;
    _counter = min;
    _direction = true;
}

OperationExample::~OperationExample()
{
}

bool OperationExample::Operate()
{
    RF_LOG_DEBUG( "min:", _min, " max:", _max );


    if ( _counter == _max ) 
    {
        _direction = false;
    }
    else if ( _counter == _min )
    {
        _direction = true;
    }

    if ( _direction )
    {
        ++ _counter;
    }
    else
    {
       -- _counter;
    }

    std::this_thread::sleep_for( std::chrono::milliseconds( _sleepTime ) ); 

    std::cout << (unsigned int)_counter << " " << std::endl;

    return true;
}

unsigned char OperationExample::GetCounter()
{
    return _counter;
}

