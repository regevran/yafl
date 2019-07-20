
#pragma once

#include <fstream>
#include <ostream>

namespace yafl{
namespace log{

/*
Msg{ 10, 20, 30 }

Msg<3>{
    long 10;            <-- _head
    Msg<2>{             <-- _msg
        long 20;        <-- _head
        Msg<1>{         <-- _msg
            long 30;    <-- _val
        }
    }
}
*/


template<unsigned long SIZE>
class Msg
{
    public:
        template<typename HEAD, class... TAIL>
        Msg( HEAD head, TAIL... tail )
            :
            _head( head ),
            _msg( tail... )
        {
        }

    private:
        unsigned long          _head;
        Msg<SIZE-1>            _msg;

    public:
        template<unsigned long S>
        friend std::ostream& operator<<( std::ostream&, const Msg<S>& );

        template<unsigned long S>
        friend std::fstream& operator<<( std::fstream&, const Msg<S>& );
};

template<unsigned long S>
std::ostream& operator<<( std::ostream& o, const Msg<S>& msg )
{
    o << msg._head << "|" << msg._msg;
    return o;
} 

template<unsigned long S>
std::fstream& operator<<( std::fstream& f, const Msg<S>& msg )
{
    f.write( reinterpret_cast<const char*>(&msg._head), sizeof msg._head );
    f << msg._msg;
    return f;
} 

////////////////      specialization for 1    ///////////////////////

template<>
class Msg<1>
{
    public:
        Msg( unsigned long val )
            : _val( val )
        {
        }

    private:
        unsigned long          _val;

    public:
        friend std::ostream& operator<<( std::ostream&, const Msg<1>& );
        friend std::fstream& operator<<( std::fstream&, const Msg<1>& );
};

////////////////    construct_msg    ///////////////////////

template<typename HEAD, class... TAIL>
auto construct_msg( HEAD head, TAIL... tail )
{
    return Msg<sizeof...(TAIL)+1>( head, tail... );
}


extern std::fstream g_log;

}}

