
///==============================================================================
// TODO:  Setting preOp and postOp is not safe in case of two or more
// threads that try to set them at the same time.
// A protection must be added to support this.
// However, if your application tries to set for a forever loop a pre operation 
// or a post operation at the same time... from mroe than one thread... then... 
// well... you definitely have a serious problem in your design!
//==============================================================================
//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include "infra/inc/execution/execution_forever.h"
#include "infra/inc/execution/owner_execution.h"
#include "infra/inc/operation/operation.h"

namespace infra {

ExecutionForever::ExecutionForever( 
    Operation& loopOp, 
    Operation* pPreOp,
    Operation* pPostOp,
    std::chrono::microseconds sleepTimeM
)
    : 
    _loopOp( loopOp ),
    _pPreOp( pPreOp ),
    _pPostOp( pPostOp ),
    _sleepTimeM( sleepTimeM ),
    _owner( nullptr )
{
    _shouldSleep = _sleepTimeM != std::chrono::microseconds(0);
}

ExecutionForever::~ExecutionForever()
{
} 

void ExecutionForever::stop()
{
    resume(); 
    ExecutionBase::stop();
}

void ExecutionForever::update()
{
    _loopOp.Update();
}

void ExecutionForever::pause()
{
//        _pause.lock();
}

void ExecutionForever::resume()
{
//        _pause.unlock();
}

Operation* ExecutionForever::setPreOperation( Operation* preOp )
{
    // replacing preOp to nullptr is illegal.
    // though it might be already nullptr, which is fine
    if ( ! preOp )
    {
        return nullptr;
    }

    Operation* ret = _pPreOp;
    _pPreOp = preOp;
    return ret;
}

Operation* ExecutionForever::setPostOperation( Operation* postOp ) 
{
    Operation* ret = _pPostOp;
    _pPostOp = postOp;
    return ret;
}

void ExecutionForever::owner( OwnerExecution<ExecutionForever>* owner )
{
    _owner = owner;
}

OwnerExecution<ExecutionForever>* ExecutionForever::owner()
{
    return _owner;
}

bool ExecutionForever::mainExecution()
{
    bool isOK( true );

    if ( _pPreOp )
    {
        isOK = _pPreOp->Operate();
    }

    while ( ( ! isStopped() ) && ( isOK ) )
    {
//        _pause.lock();

        if ( ! isStopped() )
        {
            isOK = _loopOp.Operate();
        }

//        _pause.unlock();

        if ( _shouldSleep && isOK )
        {
            // removed beccause of older g++: std::this_thread::sleep_for( _sleepTimeM ); 
        }
    }

    // post operations are done even if !isOk
    if ( _pPostOp )
    {
        isOK = _pPostOp->Operate();
    } 

    return isOK;
}

void ExecutionForever::done()
{
    if ( _owner )
    {
        _owner->done( this );
    }
}


}
