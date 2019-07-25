
#ifndef __INFRA_QUEUE__
#define __INFRA_QUEUE__

#include "msg.h"

namespace infra{
namespace container{

template <class T, unsigned long SIZE>
class Queue
{
    public:
        Queue();
        ~Queue();
        Queue( const Queue& ) = delete;
        Queue& operator=( const Queue& ) = delete; 

    public:
        bool empty() const;
        unsigned long size() const;

    public:
        // push T into the queue, makes a copy of T in the queue.
        // does nothing if the queue is full (size() == SIZE)
        bool push( const T& );

        // returns a reference to the top most element
        // returns a default constructed T in case of underflow (more pops than pushes)
        T& pop();

    private:
        void advance( unsigned long& );
        void jail( unsigned long& ); 
        bool jailed( const unsigned long& ) const;

    private:
        // the +1 handles overflow and underflow
        T                   _data[ SIZE + 1];

        // points to the next free address
        unsigned long       _head;

        // points to the read address
        unsigned long       _tail; 
};


template <class T, unsigned long SIZE>
Queue<T,SIZE>::Queue()
    : _head( 0 )
{
    jail( _tail );
}

template <class T, unsigned long SIZE>
Queue<T,SIZE>::~Queue()
{
}

template <class T, unsigned long SIZE>
bool Queue<T,SIZE>::empty() const
{
    return jailed( _tail );
}

template <class T, unsigned long SIZE>
unsigned long Queue<T,SIZE>::size() const
{
    if ( jailed( _head ) )
    {
        return SIZE;
    } 
    else if ( jailed( _tail ) )
    {
        return 0;
    } 
    else if ( _head > _tail )
    {
        return _head - _tail;
    }
    else
    {
        return SIZE - ( _tail - _head );
    } 
}

template <class T, unsigned long SIZE>
bool Queue<T,SIZE>::push( const T& t )
{
    bool overflow = jailed( _head );

    // check for overflow
    if ( ! overflow  )
    {
        _data[ _head ] = t;

        if ( jailed( _tail ) )
        {
            _tail = _head;
        }

        advance( _head );
        
        // overflow
        if ( _head == _tail )
        {
            jail( _head );
        }
    }

    return ! overflow;
}

template <class T, unsigned long SIZE>
T& Queue<T,SIZE>::pop()
{
    if ( _tail <= SIZE )
    {
        T& ret( _data[ _tail ] );

        if ( ! jailed( _tail ) )
        { 
            if ( jailed( _head ) )
            {
                _head = _tail;
            }

            advance( _tail );

            // underflow
            if ( _tail == _head )
            {
                jail( _tail );
            }
        }

        return ret;
    }
    else
    {
        return _data[0];
    }
}

template <class T, unsigned long SIZE>
void Queue<T,SIZE>::advance( unsigned long& p )
{ 
    if ( ! jailed( p ) )
    {
        ++ p;
        if ( p == SIZE )
        {
            p = 0;
        }
    }          
}

template <class T, unsigned long SIZE>
void Queue<T,SIZE>::jail( unsigned long& p )
{
    p = SIZE + 1;
} 

template <class T, unsigned long SIZE>
bool Queue<T,SIZE>::jailed( const unsigned long& p ) const
{
    return p == (SIZE + 1);
}

}}

#endif

