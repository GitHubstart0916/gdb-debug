#ifndef TYPE_H
#define TYPE_H

#include<string>
typedef unsigned char BYTE;
typedef unsigned int UDINT;
typedef short INT;
typedef bool BOOL;
typedef float REAL;
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
#define LIN 10
#define SMC_ControlAxisByPos int
#define SMC_Interpolator int
#define VisuStruct3DPathPoint int
#define SMC_PositionTracker int 
//#define SMC_CheckVelocities int
//#define SMC_OUTQUEUE int
//#define SMC_PathCopierCompleteQueue int
//#define VisuStruct3DControl int

namespace SM3_CNC {
    typedef int SMC_TRAFO_Gantry3;
    typedef int SMC_TRAFOF_Gantry3;
    void SMC_SetQueueCapacity(int, int);

}

class SMC_GEOINFO
{
private:
    /* data */
public:
    SMC_GEOINFO(int,int,int,int,int,int,int,int,bool);
    SMC_GEOINFO();
    ~SMC_GEOINFO();
    int iSourceLine_No, iMoveType, iObjNo; 
    PiPos piStartPos, piDestPos;
};

class PiPos
{
private:
    /* data */
public:
    PiPos(/* args */);
    ~PiPos();
    int dX, dY, dZ;
};




class VisuStruct3DControl
{
private:
    /* data */
public:
    VisuStruct3DControl(/* args */);
    int iTurnX, iTurnY, iTurnZ, iZ;
    ~VisuStruct3DControl();
};


class SMC_OUTQUEUE
{
private:
    /* data */
public:
    SMC_OUTQUEUE(/* args */);
    int pbyBuffer;
    int bFull;
    bool bEndOfList;
    ~SMC_OUTQUEUE();
};

class SMC_PathCopierCompleteQueue
{
private:
    /* data */
public:
    SMC_PathCopierCompleteQueue(bool, int, int, int);
    SMC_PathCopierCompleteQueue();
    ~SMC_PathCopierCompleteQueue();
    void Set_bExecute(BOOL);
};



class SMC_CheckVelocities
{
private:
    /* data */
public:
    SMC_CheckVelocities(/* args */);
    void Set_bExecute(BOOL);
    void Set(bool, int);
    ~SMC_CheckVelocities();
};

class robotCtr
{
private:
    /* data */
public:
    robotCtr(/* args */);
    bool bDone;
    ~robotCtr();
};





template<typename T> void SMC_CalcLengthGeo(T);

template<typename T> void SMC_AppendObj(T, T);

template<typename T> void SMC_OutQueueInit(T);


const robotCtr RobotControl = robotCtr();




#endif
