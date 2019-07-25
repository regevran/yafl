
#ifndef MSG_H
#define MSG_H

#include <iostream>
#include <sstream>
#include <syslog.h>
#include <pthread.h>
#include <thread>

namespace Logging {

class MSG
{
public:
    MSG()
    {
    } 

    template <typename HEAD, typename... TAIL>
    MSG( HEAD head, TAIL... tail )
    {
        _ss << head;
        MSG( _ss, tail... ); 
    }

    MSG( const MSG&& rhs )
    {
        *this = rhs;
    }

    MSG& operator=( const MSG&& rhs )
    {
        _ss.swap( rhs._ss );
        return *this;
    }

    MSG( const MSG& rhs )
    {
        *this = rhs;
    }

    MSG& operator=( const MSG& rhs )
    {
        _ss.swap( rhs._ss );
        return *this;
    }

    ~MSG()
    {
    }

    friend std::ostream& operator <<( std::ostream& o, const MSG& msg )
    {
        o << msg._ss.str();
        return o;
    }

private:

    template <typename HEAD, typename... TAIL>
    MSG( std::stringstream& os, HEAD head, TAIL...tail )
    {
        os << head;
        MSG( os, tail... );
    }

    MSG( std::stringstream& os )
    {
        os << std::endl;
    }

private:
    mutable std::stringstream _ss;
};


}

// few helpfull definitions
#ifdef SERVER_ENTRY_EXIT
#define INFRA_LOG_ENTRY( x... )\
    Logging::MSG { "P|", LOG_DEBUG, "T|", std::hex, pthread_self(), std::dec, "|", __FILE__, "|", __LINE__, "|", __FUNCTION__, "() { ", ##x };\
    unsigned char must_be_used;
    
#define INFRA_LOG_EXIT( x... )\
    Logging::MSG { "P|", LOG_DEBUG, "T|", std::hex, pthread_self(), std::dec, "|", __FILE__, "|", __LINE__, "|", __FUNCTION__, "() } ", ##x };\
    must_be_used = 9; must_be_used ++;

#else
#define INFRA_LOG_ENTRY( x... )
#define INFRA_LOG_EXIT( x... ) 
#endif

#ifdef SERVER_INFO
#define INFRA_LOG_INFO( x... ) Logging::MSG { "P|", LOG_INFO, "I|", std::hex, pthread_self(), std::dec, "|", __FILE__, "|", __LINE__, "|", __FUNCTION__, "() ", ##x }; 
#else
#define INFRA_LOG_INFO( x... )
#endif 

#ifdef SERVER_WARNING
#define INFRA_LOG_WARNING( x... ) Logging::MSG { "P|", LOG_WARNING, "W|", std::hex, pthread_self(), std::dec, "|", __FILE__, "|", __LINE__, "|", __FUNCTION__, "() ", ##x }; 
#else
#define INFRA_LOG_WARNING( x... )
#endif

#ifdef SERVER_ERROR
#define INFRA_LOG_ERROR( x... ) Logging::MSG { "P|", LOG_ERR, "E|", std::hex, pthread_self(), std::dec, "|", __FILE__, "|", __LINE__, "|", __FUNCTION__, "() ", ##x }; 
#else
#define INFRA_LOG_ERROR( x... )
#endif

#ifdef SERVER_ALERT
#define INFRA_LOG_ALERT( x... ) Logging::MSG { "P|", LOG_ALERT, "A|", std::hex, pthread_self(), std::dec, "|", __FILE__, "|", __LINE__, "|", __FUNCTION__, "() ", ##x }; 
#else
#define INFRA_LOG_ALERT( x... )
#endif


#ifdef SERVER_DEBUG
#define INFRA_LOG_DEBUG( x... ) Logging::MSG { "P|", LOG_DEBUG, "D|", std::hex, pthread_self(), std::dec, "|", __FILE__, "|", __LINE__, "|", __FUNCTION__, "() ", ##x }; 
#else
#define INFRA_LOG_DEBUG( x... )
#endif

#endif 


