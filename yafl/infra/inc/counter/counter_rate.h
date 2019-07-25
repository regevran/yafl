
#ifndef __COUNTER_RATE__
#define __COUNTER_RATE__

#include <chrono>
#include <ostream>

namespace infra{
namespace counter{

class CounterRate
{

    public:
        CounterRate( const std::string& name = "counter" );
        ~CounterRate();
        CounterRate( const CounterRate& );
        CounterRate& operator=( const CounterRate& rhs );

    public:
        void startCount();
        void endCount();

        // implicitly starts the counter if not yet started
        void add( double amount );
    
    public:
        double getCount() const;
        double getRate() const;

    private:
        double        _count;
        unsigned long _start;
        unsigned long _end;
        bool _bstarted;
        std::string _name;


        friend std::ostream& operator << ( std::ostream&, const CounterRate ); 
};


std::ostream& operator << ( std::ostream&, const CounterRate ); 

}}


#endif
