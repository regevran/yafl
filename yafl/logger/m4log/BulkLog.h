
#pragma once

#include "logger/inc/log.h"
#include <fstream>
#include <array>

namespace yafl{
namespace log{


// assumption - single thread

template< unsigned long BULK_SIZE>
class BulkLog
{
    public:
        BulkLog( const std::string& logFileName );
        ~BulkLog();

    public:
        void push( const Log& );

    private:
        void flush();

    private:
        std::array<Log,BULK_SIZE>   _bulk;
        unsigned long               _pos = 0;
        std::fstream                _logFile;
};

template<unsigned long BS>
BulkLog<BS>::BulkLog( const std::string& logFileName )
    : _logFile( logFileName, _logFile.binary | _logFile.trunc | _logFile.out )
{
}

template<unsigned long BS>
BulkLog<BS>::~BulkLog()
{
    flush();
} 

template<unsigned long BS>
void BulkLog<BS>::push( const Log& l )
{
    _bulk[ _pos ] = l;
    ++_pos;

    if ( _bulk.size() == BS )
    {
        flush();
    }
}

template<unsigned long BS>
void BulkLog<BS>::flush()
{
    _logFile.write( reinterpret_cast<const char*>(_bulk.data()), sizeof(Log) * _pos );
    _pos = 0;
}

}}

