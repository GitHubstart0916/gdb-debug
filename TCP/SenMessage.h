
#define AxisXPoint 100
#define AxisYPoint 100
#define AxisZPoint 100
#define JSONVAR 100
#include<string>
class SenMessage
{
private:
    /* data */
public:
    SenMessage(/* args */);
    Axis AxisXP;
    Axis AxisYP;
    Axis AxisZP;
    TimeStamp TimeStamp;
    ~SenMessage();
};

class Axis
{
private:
    /* data */
public:
    Axis(/* args */);
    int Number;
    ~Axis();
};

class TimeStamp
{
private:
    /* data */
public:
    TimeStamp(/* args */);
    std::string CharString;
    ~TimeStamp();
};

TimeStamp::TimeStamp(/* args */)
{
}

TimeStamp::~TimeStamp()
{
}


