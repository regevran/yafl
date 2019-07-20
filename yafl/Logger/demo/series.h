
#pragma once

#include <log4cpp/Category.hh>

class Series
{
    public:
        Series( 
            unsigned long startCountAt,
            unsigned long stopCountAt
        );
        ~Series();

    public:
        void reset();

    public:
        void fast();
        void log4cpp();

        void getTimes( 
            std::chrono::steady_clock::time_point& start,
            std::chrono::steady_clock::time_point& end
        );

    private:
        int             _callCount;
        unsigned long   _startCountAt;
        unsigned long   _stopCountAt;

    private:
        std::chrono::steady_clock::time_point _start;
        std::chrono::steady_clock::time_point _end;

    private:
//        log4cpp::Category&   _logger;
};




