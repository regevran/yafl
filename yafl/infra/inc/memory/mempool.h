
#ifndef __MEM_POOL__
#define __MEM_POOL__

#include <queue>
#include <mutex>

#define nullptr 0

namespace infra{
namespace memory{

template <class T, unsigned long SIZE>
class MemPool
{
    public:
        MemPool();
        ~MemPool();

        T* malloc();
        void free( T* );

    private:
        T               _pool[ SIZE ]; 
        T*              _stack[ SIZE + 1 ];
        unsigned long   _head;
        std::mutex      _memoryKeeper;
};

template <class T, unsigned long SIZE>
MemPool<T,SIZE>::MemPool()
{
    for ( unsigned long i = 0; i < SIZE; ++i )
    {
        _stack[ i ] = &_pool[ i ];
    }
    
    // one past the end
    _stack[ SIZE ] = nullptr;

    _head = 0;
}

template <class T, unsigned long SIZE>
MemPool<T,SIZE>::~MemPool()
{
}

template <class T, unsigned long SIZE>
T* MemPool<T,SIZE>::malloc()
{
    std::lock_guard<std::mutex> lg( _memoryKeeper );

    T* ret = _stack[ _head ];
    ++ _head;

    if ( _head > SIZE )
    {
        _head = SIZE;
    }

    return ret;
}

template <class T, unsigned long SIZE>
void MemPool<T,SIZE>::free( T* t )
{
    std::lock_guard<std::mutex> lg( _memoryKeeper );

    -- _head;
    _stack[ _head ] = t; 
}

}}

#endif

