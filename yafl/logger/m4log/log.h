
#pragma once

#include <ostream>

namespace yafl{
namespace log{

class Log
{

    public:
        Log(
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
         );


        Log( const Log& rhs );
        ~Log(); 
        Log& operator =( const Log& rhs );

    private:
        unsigned long _fields[24];

    // debug
    friend std::ostream& operator<<( std::ostream&, const Log& );
};

std::ostream& operator<<( std::ostream& o, const Log& l );

}}

