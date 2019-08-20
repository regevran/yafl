
#include "logger/inc/log.h"
#include <iostream>
#include <cstring>

namespace yafl{
namespace log{

Log::~Log()
{
}

void Log::timestamp()
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now(); 
    _fields[0] = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

std::ostream& operator<<( std::ostream& o, const Log& l )
{

    // 0xee7db699|0x12|0xcdcd0000|0x7f0d6d5f9740|0xbeef0000|0xbeef0001|0x1e|0xcdcdcdcd#

    o << 
        "0x" << std::hex << l._fields[0]    << "|" <<  // file
        std::dec << l._fields[1]            << "|" <<  // line
        "0x" << std::hex << l._fields[2]    << "|" <<  // debug level
        "0x" << std::hex << l._fields[3]    << "|" <<  // working thread
        "0x" << std::hex << l._fields[4]    << "|";    // module

    unsigned long index = 5;

    while ( index < MAX_LOG_FIELDS && l._fields[ index ] != END_RECORD_MARK )
    {
        o << std::dec << l._fields[ index ] << "|";
        ++ index;
    } 

    o << "0x" << std::hex << l._fields[ index ] << "#";

    return o;
}


}}

