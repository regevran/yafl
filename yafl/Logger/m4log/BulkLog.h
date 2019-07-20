
#pragma once

#include "Logger/inc/log.h"
#include <fstream>

namespace yafl{
namespace log{


// assumption - single thread
class BulkLog
{
    public:
        BulkLog( 
                const std::string& logFileName,
                const unsigned long bulkSize 
        );
        ~BulkLog();

    public:
        void push_back( const Log& );

    private:
        void flush();

    private:
        const unsigned long     _bulkSize;
        std::vector<Log>        _bulk;
        std::fstream            _logFile;
};


}}

