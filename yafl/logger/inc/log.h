
#pragma once

#include <ostream>
#include <chrono>

namespace yafl{
namespace log{


// changing the sizeof(Log) may results in writing
// the wrong number of bytes to the log file because
// BulkLog uses sizeof(Log)

// max fields in a Log record
constexpr unsigned long MAX_LOG_FIELDS( 25 );

// the end of mark value - should be sync with the m4's script (yaflpp.m4)
// though the m4 adds the end of mark just for safty. The Log class 
// adds this field by default to ALL fields
constexpr unsigned long END_RECORD_MARK( 0xcdcdcdcdcdcdcdcd );

class Log
{
    // sizeof( unsigned long ) == 8 
    public:
        constexpr Log(
             unsigned long f1 = END_RECORD_MARK,
             unsigned long f2 = END_RECORD_MARK,
             unsigned long f3 = END_RECORD_MARK,
             unsigned long f4 = END_RECORD_MARK,
             unsigned long f5 = END_RECORD_MARK,
             unsigned long f6 = END_RECORD_MARK,
             unsigned long f7 = END_RECORD_MARK,
             unsigned long f8 = END_RECORD_MARK,
             unsigned long f9 = END_RECORD_MARK,
             unsigned long f10 = END_RECORD_MARK,
             unsigned long f11 = END_RECORD_MARK,
             unsigned long f12 = END_RECORD_MARK,
             unsigned long f13 = END_RECORD_MARK,
             unsigned long f14 = END_RECORD_MARK,
             unsigned long f15 = END_RECORD_MARK,
             unsigned long f16 = END_RECORD_MARK,
             unsigned long f17 = END_RECORD_MARK,
             unsigned long f18 = END_RECORD_MARK,
             unsigned long f19 = END_RECORD_MARK,            
             unsigned long f20 = END_RECORD_MARK,
             unsigned long f21 = END_RECORD_MARK,
             unsigned long f22 = END_RECORD_MARK,
             unsigned long f23 = END_RECORD_MARK,
             unsigned long f24 = END_RECORD_MARK,
             unsigned long f25 = END_RECORD_MARK
         ) noexcept; 
    
    public:
        constexpr Log( const Log& rhs );
        constexpr Log& operator=( const Log& rhs );        
        ~Log();

    public:
        void timestamp( bool sysCall );

    private:
        unsigned long _fields[ MAX_LOG_FIELDS ];
        std::chrono::high_resolution_clock::time_point _now;

        friend std::ostream& operator<<( std::ostream&, const Log& );
};

std::ostream& operator<<( std::ostream&, const Log& );

constexpr Log::Log(
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
) noexcept 
    :
    _fields{ 
        END_RECORD_MARK, // reserved for timestamp
        f1, f2, f3, f4, f5, f6, f7, f8, f9, f10,
        f11, f12, f13, f14, f15, f16, f17, f18, f19, f20,
        f21, f22, f23,
        // last element is hardcoded end of record mark
        END_RECORD_MARK
    } 
{
}

constexpr Log::Log( const Log& rhs )
    :
    _fields{ 
        rhs._fields[0], 
        rhs._fields[1], rhs._fields[2], rhs._fields[3], rhs._fields[4], rhs._fields[5], 
        rhs._fields[6], rhs._fields[7], rhs._fields[8], rhs._fields[9], rhs._fields[10],
        rhs._fields[11], rhs._fields[12], rhs._fields[13], rhs._fields[14], rhs._fields[15],
        rhs._fields[16], rhs._fields[17], rhs._fields[18], rhs._fields[19], rhs._fields[20],
        rhs._fields[21], rhs._fields[22], rhs._fields[23], rhs._fields[24]
    } 
{
}

constexpr Log& Log::operator=( const Log& rhs )
{
    _fields[0] = rhs._fields[0];
    _fields[1] = rhs._fields[1]; 
    _fields[2] = rhs._fields[2]; 
    _fields[3] = rhs._fields[3]; 
    _fields[4] = rhs._fields[4]; 
    _fields[5] = rhs._fields[5]; 
    _fields[6] = rhs._fields[6]; 
    _fields[7] = rhs._fields[7]; 
    _fields[8] = rhs._fields[8]; 
    _fields[9] = rhs._fields[9]; 
    _fields[10] = rhs._fields[10];
    _fields[11] = rhs._fields[11]; 
    _fields[12] = rhs._fields[12]; 
    _fields[13] = rhs._fields[13]; 
    _fields[14] = rhs._fields[14]; 
    _fields[15] = rhs._fields[15];
    _fields[16] = rhs._fields[16]; 
    _fields[17] = rhs._fields[17]; 
    _fields[18] = rhs._fields[18]; 
    _fields[19] = rhs._fields[19]; 
    _fields[20] = rhs._fields[20];
    _fields[21] = rhs._fields[21]; 
    _fields[22] = rhs._fields[22]; 
    _fields[23] = rhs._fields[23];
    _fields[24] = rhs._fields[24];
    return *this;
} 

}}

