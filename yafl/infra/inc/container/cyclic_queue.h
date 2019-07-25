
#ifndef __INFRA_CYCLIC_QUEUE__
#define __INFRA_CYCLIC_QUEUE__

namespace infra{
namespace container{

// assumption: never overflow or underflow
template <class T, unsigned long SIZE>
class CyclicQueue
{
    public:
        CyclicQueue();
        ~CyclicQueue();
        CyclicQueue( const CyclicQueue& ) = delete;
        CyclicQueue& operator=( const CyclicQueue& ) = delete; 

    public:
        bool empty() const;
        unsigned long size() const;

    public:
        // push T into the queue, makes a copy of T in the queue.
        // write on top of the first element if overflow
        bool push( const T& );

        // returns a reference to the top most element
        T& pop();

    private:
        void advance( unsigned long& );

    private:
        T                   _data[ SIZE ];

        // points to the next free address
        unsigned long       _head;

        // points to the read address
        unsigned long       _tail; 
};


template <class T, unsigned long SIZE>
CyclicQueue<T,SIZE>::CyclicQueue()
    : 
    _head( 0 ),
    _tail( 0 )
{
}

template <class T, unsigned long SIZE>
CyclicQueue<T,SIZE>::~CyclicQueue()
{
}

template <class T, unsigned long SIZE>
bool CyclicQueue<T,SIZE>::empty() const
{
    return (_head == _tail);
}

template <class T, unsigned long SIZE>
unsigned long CyclicQueue<T,SIZE>::size() const
{
    if ( _head >= _tail )
    {
        return _head - _tail;
    }
    else
    {
        return SIZE - ( _tail - _head );
    } 
}

template <class T, unsigned long SIZE>
bool CyclicQueue<T,SIZE>::push( const T& t )
{
    _data[ _head ] = t;

    advance( _head );
        
    return true;
}

template <class T, unsigned long SIZE>
T& CyclicQueue<T,SIZE>::pop()
{
    T& ret( _data[ _tail ] );

    advance( _tail );

    return ret;
}

template <class T, unsigned long SIZE>
void CyclicQueue<T,SIZE>::advance( unsigned long& p )
{ 
    ++ p;
    if ( p == SIZE )
    {
        p = 0;
    }
}

}}

#endif 

