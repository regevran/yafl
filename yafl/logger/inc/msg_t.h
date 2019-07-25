
#pragma once

#include <fstream>
#include <ostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <thread>

namespace yafl{
namespace log{

////////////////    MsgT   ///////////////////////

/*
   MsgT<int, std::string, double, char> m( 4, "hello", 6.78, 'e' );

   MsgT<int, std::string, double, char>
   {
       int                              _val = 4;
       MsgT<std::string, double, char>  // _inner
       {
            std::string                 _val = "hello";
            MsgT<double, char>          // inner
            {
                double                  _val = 6.78;
                MsgT<char>              // inner (specialized version)
                {
                    A                   _val = 'e';
                } 
            }
        }
    }
*/

template<typename V, typename... T>
class MsgT
{
    public:
        template<typename W, class... REST>
        MsgT( const W& val, REST... rest )
            :
            _val( val ),
            _inner( rest... )
        {
        }

    private:
        const V       _val;
        MsgT<T...>    _inner;

    public:
        template<class... TYPES>
        friend std::ostream& operator<<( std::ostream&, const MsgT<TYPES...>& );
};

template<class... TYPES>
std::ostream& operator<<( std::ostream& o, const MsgT<TYPES...>& msg )
{
    o << msg._val << msg._inner;

    return o;
} 


////////////////    specialization for one    ///////////////////////
template<typename V>
class MsgT<V>
{
    public:
        MsgT( const V& val )
            : _val( val )
        {
        }

    private:
        V   _val;

    public:
        template<typename W>
        friend std::ostream& operator<<( std::ostream&, const MsgT<W>& );
};

template<typename W>
std::ostream& operator<<( std::ostream& o, const MsgT<W>& msg )
{
    o << msg._val; 

    return o;
}

////////////////    construct_msg    ///////////////////////

// construct_msg is to prevent the need to write in the caller: MsgT<types...>
// instead the caller can use it for example as simple as:
// auto m = construct_msg( 34, "abc", 56.8 ); 
// std::cout << m << std::end;
template<typename... PARAMS>
auto construct_msg( PARAMS... params )
{
    // stamp the time including milliseconds
    auto now( std::chrono::high_resolution_clock::now() );
    auto epoch = now.time_since_epoch();
    auto epocOnlyhMilli = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count() % 1000;
    std::time_t tt = std::chrono::high_resolution_clock::to_time_t( now );
    std::tm tm = *std::localtime( &tt );

    std::stringstream ss; 
    ss << std::put_time( &tm, "%d/%m/%Y %H:%M:%S" ) << "." << epocOnlyhMilli; 

    return MsgT<std::string, PARAMS...>( ss.str() , params... );
}

////////////////    convinient macros   ///////////////////////

#define STDOUT( x... )  std::cout << yafl::log::construct_msg(  "|", __FILE__, "|", __LINE__, "|", std::this_thread::get_id(), "|", x ) << std::endl
#define STDERR( x... )  std::cerr << yafl::log::construct_msg(  "|", __FILE__, "|", __LINE__, "|", std::this_thread::get_id(), "|", x ) << std::endl

}}

