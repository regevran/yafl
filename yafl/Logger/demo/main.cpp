
#include <iostream>
#include <thread>
#include "Logger/inc/msg_t.h"


int main()
{
    STDERR( " kabala ", " shemesh ", "40 miles ", 345 );
    return 0;
}



# if 0
int main()
{
    yafl::log::g_logQ.start();

    const unsigned long ITERATIONS = 10;


    ///  fast log  ///

    Series s1( 1, ITERATIONS );

    for ( unsigned long i = 0; i < ITERATIONS; ++ i )
    {
        s1.fast();
    } 

    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    s1.getTimes( start, end ); 
    auto fastCount = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    LOG_DEMO_INFO( "calculation time (us):", fastCount );
    std::cout << "fast log calculation time (us):" << fastCount << std::endl; 

    yafl::log::g_logQ.stop();
    yafl::log::g_logQ.join(); 

    ///  log 4 cpp  ///
    /*

    Series s2( 1, ITERATIONS );

    for ( unsigned long i = 0; i < ITERATIONS; ++ i )
    {
        s3.log4cpp();
    } 
    s2.getTimes( start, end ); 
    auto log4cppCount = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

    std::cout << "log4cpp calculation time (us):" << log4cppCount << std::endl; 


    std::cout << "fast is : " << log4cppCount / fastCount << " times faster" << std::endl;
    */

    return 0;
}
#endif


