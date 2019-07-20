//==============================================================================
//  File name	:	execution_at.cpp
//  Author:		:	Ran Regev
//  date		: 	11/10/2015
//==============================================================================
// Notes:  
//==============================================================================

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
#include "execution_at.h"
#include "operation.h"
#include "owner_execution.h"
#include "msg.h"

namespace rf {

ExecutionAt::ExecutionAt( 
        unsigned long t1,
        unsigned long t2, 
        Operation* op
) : 
    _t1( t1 ),
    _t2( t2 ),
    _op( op )
{
}

ExecutionAt::~ExecutionAt()
{
}

void ExecutionAt::stop()
{
    ExecutionBase::stop(); 

    // it would be an error if we have more than one
    // thread waiting on this condition
    _stopCond.notify_one();
} 


void ExecutionAt::setNewTimes( unsigned long t1, unsigned long t2 )
{
    RF_LOG_DEBUG( "old t1: ", _t1 );
    RF_LOG_DEBUG( "old t2: ", _t2 );
    RF_LOG_DEBUG( "new t1: ", t1 );
    RF_LOG_DEBUG( "new t2: ", t2 );

    _t1 = t1;
    _t2 = t2;

    if ( _op )
    {
        _op->Update();
    }

    _stopCond.notify_one();
}
 
bool ExecutionAt::mainExecution()
{
    RF_LOG_ENTRY();

    std::cv_status waitResult;
    bool retVal = false; 

    while ( !isStopped() )
    { 
        // sleep t1
        {
            RF_LOG_DEBUG( "now going to sleep till (t1) ", _t1 );
            std::unique_lock< std::mutex > lk( _mutex ); 
            waitResult = _stopCond.wait_until( lk, std::chrono::system_clock::from_time_t( _t1 ) );
        }

        // timeout means that it is the time to work 
        if ( waitResult == std::cv_status::timeout )
        { 
            if ( _op )
            {
                retVal = _op->Operate();
            }
            else
            {
                retVal = false;
            }

            if ( retVal )
            {            
                while ( ! isStopped() )
                {
                    // sleep t2 
                    if ( 0 != _t2 )
                    {
                        {
                            RF_LOG_DEBUG( "now going to sleep till (t2) ", _t2 );
                            std::unique_lock< std::mutex > lk( _mutex ); 
                            waitResult = _stopCond.wait_until( lk, std::chrono::system_clock::from_time_t( _t2 ) );
                        }

                        // timeout means that it is the time to work 
                        if ( waitResult == std::cv_status::timeout )
                        {     
                            if ( _op )
                            {
                                retVal = _op->Operate();
                                stop();
                            }
                        }
                    }
                    else
                    {
                        retVal = true;
                        stop();
                    }
                }
            }
            else
            {
                stop();
            }
        }
    }

    RF_LOG_EXIT( std::boolalpha, retVal ); 
    return retVal;
}

void ExecutionAt::owner( OwnerExecution<ExecutionAt>* o )
{
    _owner = o;
}

OwnerExecution<ExecutionAt>* ExecutionAt::owner()
{
    return _owner;
}

}

