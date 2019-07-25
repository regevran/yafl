
//==============================================================================
// Notes:  Implementation of execution base
// we do NOT expect that execution objects will be called from multiple
// contexts. In other words, Execution is not thread safe by its own
//==============================================================================

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include "infra/inc/execution/execution_base.h"
#include "infra/inc/execution/owner_execution.h"

namespace infra {


ExecutionBase::ExecutionBase()
    :
     _isStopped( true ),
     _endStatus( true ), // no start, therefore no fail
     _owner( nullptr ) 
{
}

ExecutionBase::~ExecutionBase()
{
}

void ExecutionBase::start()
{
    if ( isStopped()  )
    {
        // setting _IsStopped lets the new created thread a chance
        // to run before this function (Start) finishes
        _isStopped = false;

        // create temporary thread and start its execution
        std::thread tmpThread( ExecutionBase::mainEntryPoint, std::ref( *this ) );

        // keep the running thread in this object
        tmpThread.swap( _thisExecutionThread );
    }
}

void ExecutionBase::stop()
{
    _isStopped = true;
}

void ExecutionBase::done()
{
    if ( _owner )
    {
        _owner->done( this );
    } 
}

void ExecutionBase::join()
{
    if ( _thisExecutionThread.joinable() )
    {
        _thisExecutionThread.join();
    }
}

void ExecutionBase::detach()
{
    _thisExecutionThread.detach();
}

void ExecutionBase::mainEntryPoint( ExecutionBase& execution )
{
    try
    {
        execution._endStatus = execution.mainExecution();
    }
    catch ( std::exception& e )
    {
        //STDERR( "caught exception from MainExecution: [[e.what()]]" );
    }
    catch ( ... )
    {
        //STDERR( "caught exception from MainExecution. exiting." );
        std::exit( -1 );
    } 

    execution.done();
}


bool ExecutionBase::isStopped()
{
    return _isStopped;
}

bool ExecutionBase::isSuccess()
{
    return _endStatus;
}

void ExecutionBase::owner( OwnerExecution<ExecutionBase>* o )
{
    _owner = o;
}

OwnerExecution<ExecutionBase>* ExecutionBase::owner()
{
    return _owner;
}

}


