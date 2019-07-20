

#ifndef __OWNER_EXECUTION__
#define __OWNER_EXECUTION__


namespace rf {

class ExecutionBase;

template <class EXECUTION>
class OwnerExecution
{
    public:
        OwnerExecution() {}
        virtual ~OwnerExecution(){}

    public:
        virtual void done( EXECUTION* ) = 0; 
};

}

#endif

