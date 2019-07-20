
#include "BulkLog.h"

namespace yafl{
namespace log{


BulkLog::BulkLog( 
    const std::string& logFileName,
    const unsigned long bulkSize 
)
    : 
    _bulkSize( bulkSize ),
    _logFile( logFileName, _logFile.binary | _logFile.trunc | _logFile.out )
{
}

BulkLog::~BulkLog()
{
    flush();
} 

void BulkLog::push_back( const Log& l )
{
    _bulk.push_back( l );

    if ( _bulk.size() == _bulkSize )
    {
        flush();
    }
}

void BulkLog::flush()
{
    _logFile.write( reinterpret_cast<const char*>(_bulk.data()), sizeof(Log) * _bulk.size() );
    _bulk.clear();
}


}}

