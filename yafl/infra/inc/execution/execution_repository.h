
#ifndef __EXECTION_REPOSITORY__
#define __EXECTION_REPOSITORY__

#include "execution/owner_execution.h"
#include <mutex>
#include <list>

 namespace infra {

template <class EXECUTION>
class ExecutionRepository : 
    public OwnerExecution<ExecutionBase>,
    public Joinable
{
    public:
        ExecutionRepository( unsigned long maxExecutions = 1000 );
        virtual ~ExecutionRepository();

    public:
        void start();
        void stop();
        void join();

    public:
        bool add( EXECUTION* );
        virtual void done( ExecutionBase* ); 

    private:
        std::mutex              _executionListGuard;
        std::list<EXECUTION*>   _executionList;
        unsigned long           _maxExecutuions;
};

#endif


template <class EXECUTION>
ExecutionRepository<EXECUTION>::ExecutionRepository( unsigned long maxExecutions )
    : _maxExecutuions( maxExecutions )
{
}

template <class EXECUTION>
ExecutionRepository<EXECUTION>::~ExecutionRepository()
{
}


template <class EXECUTION>
void ExecutionRepository<EXECUTION>::start()
{
    std::lock_guard<std::mutex>   lg( _executionListGuard ); 
    for ( auto e : _executionList )
    {
        e->start();
    }
}

template <class EXECUTION>
void ExecutionRepository<EXECUTION>::stop()
{
    std::lock_guard<std::mutex>   lg( _executionListGuard ); 
    for ( auto e : _executionList )
    {
        e->stop();
    }

}

template <class EXECUTION>
void ExecutionRepository<EXECUTION>::join()
{
    std::lock_guard<std::mutex>   lg( _executionListGuard ); 
    for ( auto e : _executionList )
    {
        e->join();
    }

} 

template <class EXECUTION>
bool ExecutionRepository<EXECUTION>::add( EXECUTION* e )
{
    std::lock_guard<std::mutex>   lg( _executionListGuard ); 

    if ( _executionList.size() < _maxExecutuions )
    {
        e->owner( this );
        _executionList.push_back( e ); 
        return true;
    }
    else
    {
        RF_LOG_WARNING( "reached max executions (", _maxExecutuions, ") rejecting this one" );
        return false;
    } 
}

template <class EXECUTION>
void ExecutionRepository<EXECUTION>::done( ExecutionBase* e )
{
    std::lock_guard<std::mutex> lg( _executionListGuard ); 

    auto it = std::find( _executionList.begin(), _executionList.end(), e );

    if ( it != _executionList.end() )
    {
        // remove the execution from the list
        _executionList.erase( it );

        // allow the working thread to continue (and exit since it is 'done')
        e->detach();

        // delete the object
        delete e; 
    }
}

}




