//==============================================================================
//  File name	        :	execution_forever.cpp
//  Author:		:	Ran Regev
//  date		: 	28/08/2013
//==============================================================================
// Notes:  Implementation of execution forever
//==============================================================================
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

#include "execution/execution_forever.h"
#include "operation/operation.h"

namespace rf {

ExecutionForever::ExecutionForever( 
    Operation& loopOp, 
    Operation* pPreOp,
    Operation* pPostOp,
    unsigned long sleepTimeS
)
    :
    _loopOp( loopOp ),
    _pPreOp( pPreOp ),
    _pPostOp( pPostOp ),
    _sleepTimeS( sleepTimeS )
{
}

ExecutionForever::~ExecutionForever()
{
} 

void ExecutionForever::stop()
{
    ExecutionBase::stop();

    // this does not work. It does not stops the sleep_until function
    _absoluteSleep = std::chrono::system_clock::now(); 
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

bool ExecutionForever::mainExecution()
{
    bool isOK( true );

    if ( _pPreOp )
    {
        isOK = _pPreOp->Operate();
    }

    while ( ( ! isStopped() ) && ( isOK ) )
    {
        isOK = _loopOp.Operate();

        if ( isOK && _sleepTimeS )
        {
            _absoluteSleep = std::chrono::system_clock::now();
            _absoluteSleep += std::chrono::seconds( _sleepTimeS );
            std::this_thread::sleep_until( _absoluteSleep ); 
        }
    }

    // post operations are done even if !isOk
    if ( _pPostOp )
    {
        isOK = _pPostOp->Operate();
    } 

    return isOK;
}

}

