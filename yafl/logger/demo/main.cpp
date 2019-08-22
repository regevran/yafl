
#include <iostream>
#include <thread>
#include "logger/inc/m4log_defs.h"
#include "logger/inc/log.h"
#include "series.h"



int main()
{
    // start the log queue
    yafl::log::g_logQ.start();

    //const unsigned long ITERATIONS = 100;
    const unsigned long ITERATIONS = 10000000;

    // for time calculation we use the messages in the range [+10%,MAX-10%]  
    const unsigned long START_COUNT = 0.1 * ITERATIONS;
    const unsigned long END_COUNT = ITERATIONS - START_COUNT;

    ///  fast log  ///

    Series s1( START_COUNT, END_COUNT );
    for ( unsigned long i = 0; i < ITERATIONS; ++ i )
    {
        s1.fast();
    } 

    // let the writing process finish its work
    std::this_thread::sleep_for( std::chrono::seconds( 3 ) );

    // get the times
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    s1.getTimes( start, end ); 

    // calculate the speed
    auto fastCount = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    double messegesPerSecond = ((double)s1.getCallCount() / (double)fastCount) * 1000000;

    // add some demo messages
    unsigned long v1=100,v2=200,v3=300;

    LOG_DEMO_INFO( "messages per second: ", messegesPerSecond, "; calculation time (us):", fastCount, "; total messages:", s1.getCallCount() );
    LOG_DEMO_DEBUG( "this text is mapped to unsigned long" );
    LOG_DEMO_WARNING( "variables must be converted to long too:", v1, v2, v3 );


    // stdout print
    std::cout << "messages per second: " << std::fixed << messegesPerSecond << "; calculation time (us):" << fastCount << "; total messages:" << s1.getCallCount() << std::endl;

    // empty these last few messages
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

    // print the log queue counter
    std::cout << yafl::log::g_logQ.getCounter();

    yafl::log::g_logQ.stop();
    yafl::log::g_logQ.join(); 


    return 0;
}



