
#pragma once

namespace infra{

class Joinable
{
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void join() = 0;
};

}


