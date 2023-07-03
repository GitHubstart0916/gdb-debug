#ifndef BLINK_H
#define BLINK_H

#include<time.h>
class blink
{
private:
    /* data */
    time_t TIMELOW;
    time_t TIMEHIGH;
public:
    blink(time_t timelow, time_t timehigh);
    void ENABLE(bool);
    ~blink();
    int OUT;
};


#endif