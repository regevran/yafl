
#include <chrono>

#pragma once

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

    public:
        unsigned long getCallCount() const;

        void getTimes( 
            std::chrono::high_resolution_clock::time_point& start,
            std::chrono::high_resolution_clock::time_point& end
        );

    private:
        unsigned long   _callCount;
        unsigned long   _startCountAt;
        unsigned long   _stopCountAt;

    private:
        std::chrono::high_resolution_clock::time_point _start;
        std::chrono::high_resolution_clock::time_point _end;

    private:
};


