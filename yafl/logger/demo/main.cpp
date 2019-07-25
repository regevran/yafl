
#include <iostream>
#include <thread>
#include "logger/inc/m4log_defs.h"
#include "logger/inc/log.h"
#include "series.h"



int main()
{
//    yafl::log::g_logQ.start();

    const unsigned long ITERATIONS = 1000000;


    ///  fast log  ///

    Series s1( 1, ITERATIONS );

    for ( unsigned long i = 0; i < ITERATIONS; ++ i )
    {
        s1.fast();
    } 

    //std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;

    s1.getTimes( start, end ); 
    auto fastCount = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    double messegesPerSecond = (double)s1.getCallCount() / (double)fastCount * 1000000;

    LOG_DEMO_INFO( "messages per second: ", messegesPerSecond, "; calculation time (us):", fastCount, "; total messages:", s1.getCallCount() );
    std::cout << "messages per second: " << messegesPerSecond << "; calculation time (us):" << fastCount << "; total messages:" << s1.getCallCount() << std::endl;

//    yafl::log::g_logQ.stop();
//    yafl::log::g_logQ.join(); 


    return 0;
}



