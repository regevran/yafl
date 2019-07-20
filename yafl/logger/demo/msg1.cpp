
#include "msg.h"

namespace yafl{
namespace log{

////////////////    Msg<1>     ///////////////////////

std::ostream& operator<<( std::ostream& o, const Msg<1>& msg )
{
    o << msg._val << "#" << std::endl;
    return o;
} 

std::fstream& operator<<( std::fstream& f, const Msg<1>& msg )
{
    f.write( reinterpret_cast<const char*>(&msg._val), sizeof msg._val );
    return f;
} 

////////////////    construct_msg    ///////////////////////

auto construct_msg()
{ 
    return Msg<1>(0);
}

}}

