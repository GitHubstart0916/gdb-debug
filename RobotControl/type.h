#ifndef TYPE_H
#define TYPE_H

#include<string>
typedef unsigned char BYTE;
typedef unsigned int UDINT;
typedef short INT;
typedef bool BOOL;
typedef int STRUCT_TO_JSON;
typedef int GetSystemTimeHigh;
typedef std::string STRING;
//typedef int SenMessage;

class STRUCT_TO_JSON
{
private:
    /* data */
public:
    STRUCT_TO_JSON(bool, int, int, int, int);
    STRUCT_TO_JSON();
    ~STRUCT_TO_JSON();
};

#define AxisA 10
#define AxisB 10
#define AxisC 10
#define SMC_ControlAxisByPos int
#define SMC_Interpolator int
#define VisuStruct3DPathPoint int
#define SMC_PositionTracker int 

namespace SM3_CNC {
    typedef int SMC_TRAFO_Gantry3;
    typedef int SMC_TRAFOF_Gantry3;

}


#endif
