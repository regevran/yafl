

#pragma once

class Power
{
    public:
        Power( unsigned long x, unsigned long y);
        ~Power();

    public:
        unsigned long XtimeY() const; 
        double long XdivY() const; 

    private:
        unsigned long _x;
        unsigned long _y; 
};

