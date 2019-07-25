
#pragma once

//#include "m4log_defs.h"
//
#include <ostream>

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
        Log(
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
         ); 
    
        Log( const Log& rhs );
        ~Log();
        Log& operator =( const Log& rhs );        

    private:
         unsigned long _fields[ MAX_LOG_FIELDS ];

    public:
        friend std::ostream& operator<<( std::ostream&, const Log& );
};

std::ostream& operator<<( std::ostream&, const Log& );

}}

