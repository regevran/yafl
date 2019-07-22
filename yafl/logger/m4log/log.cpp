
#include "logger/m4log/log.h"
#include <iostream>
#include <chrono>
#include <cstring>

namespace yafl{
namespace log{

Log::Log(
         unsigned long f1,
         unsigned long f2,
         unsigned long f3,
         unsigned long f4,
         unsigned long f5,
         unsigned long f6,
         unsigned long f7,
         unsigned long f8,
         unsigned long f9,
         unsigned long f10,
         unsigned long f11,
         unsigned long f12,
         unsigned long f13,
         unsigned long f14,
         unsigned long f15,
         unsigned long f16,
         unsigned long f17,
         unsigned long f18,
         unsigned long f19,
         unsigned long f20,
         unsigned long f21,
         unsigned long f22,
         unsigned long f23,
         unsigned long f24,
         unsigned long f25
)
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now(); 
    _fields[0] = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    _fields[1] = f1;
    _fields[2] = f2;
    _fields[3] = f3;
    _fields[4] = f4;
    _fields[5] = f5;
    _fields[6] = f6;
    _fields[7] = f7;
    _fields[8] = f8;
    _fields[9] = f9;
    _fields[10] = f10;
    _fields[11] = f11;
    _fields[12] = f12;
    _fields[13] = f13;
    _fields[14] = f14;
    _fields[15] = f15;
    _fields[16] = f16;
    _fields[17] = f17;
    _fields[18] = f18;
    _fields[19] = f19;
    _fields[20] = f20;
    _fields[21] = f21;
    _fields[22] = f22;
    _fields[23] = f23;
    _fields[24] = f24;

    // last element is hardcoded end of mark
    _fields[MAX_LOG_FIELDS -1 ] = END_RECORD_MARK; 
}

Log::Log( const Log& rhs )
{
    *this = rhs;
}

Log::~Log()
{
}

Log& Log::operator =( const Log& rhs )
{
    memcpy( _fields, rhs._fields, sizeof(_fields[0]) * MAX_LOG_FIELDS );

    return *this;
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

