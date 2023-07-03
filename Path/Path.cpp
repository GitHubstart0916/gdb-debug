#include "mc_power.h"
#include "type.h"
#include "lib.h"
int main() {
    Path();
}

void Path() {
    CONST_VAR:

    NON_CONST_VAR:
        bool xStart;
        bool xStartIpo;
        INT iState;
        SMC_CheckVelocities CheckVel;
        SMC_OUTQUEUE QUEUE;

        SMC_GEOINFO BUF[50];
        SMC_GEOINFO GEO = SMC_GEOINFO(0, 1, 0, 10, 5, 5, 5, 0, true);
        INT n = 0;
        float xp[7] = {0,100,100,100,0,0,0};
        float yp[7] = {0,100,100,100,0,0,0};
        float Zp[7] = {0,0,20,0,0,20,0};
        VisuStruct3DPathPoint pointbuffer[1001];
        SMC_PathCopierCompleteQueue pcc;
        VisuStruct3DControl vc;
        BOOL iX,iY,iZ,iZA,iZD;
        BOOL bLoopRun;
    MAIN:
    if (iX) {
        vc.iTurnX = 3600;   
    } else {
        vc.iTurnX = 0;
    }
    if (iY) {
        vc.iTurnY = 3600;   
    } else {
        vc.iTurnY = 0;
    }
    if (iZ) {
        vc.iTurnZ = 3600;   
    } else {
        vc.iTurnZ = 0;
    }
    if (iZA) {
        vc.iZ = 360;
    } else if (iZD) {
        vc.iZ = -360;
    } else {
        vc.iZ = 0;
    }

    switch (iState)
    {
    case 0:
        if (xStart) {
            QUEUE.pbyBuffer = ADR(BUF[0]);
            SM3_CNC::SMC_SetQueueCapacity(ADR(QUEUE), SIZEOF(BUF));
            xStart = false;
            xStartIpo = false;
            CheckVel.Set_bExecute(false);
            iState = 1;
        }
        break;
    case 1:
        while (!QUEUE.bFull) {
            n = n + 1;
            GEO.iSourceLine_No = n;
            GEO.piStartPos = GEO.piDestPos;
            GEO.iMoveType = LIN;
            GEO.iObjNo = GEO.iObjNo + 1;
            GEO.piDestPos.dX = xp[n];
            GEO.piDestPos.dY = yp[n];
            GEO.piDestPos.dZ = Zp[n];
            SMC_CalcLengthGeo(ADR(GEO));
            SMC_AppendObj(ADR(QUEUE), ADR(GEO));
            if (n == SIZEOF(xp) / sizeof(xp[1])) {
                QUEUE.bEndOfList = true;
                n = 0;
                iState = 2;
                exit(0);
            }
        }
        pcc = SMC_PathCopierCompleteQueue(false, 
                                    SIZEOF(pointbuffer)/SIZEOF(pointbuffer[0]), 
                                    ADR(pointbuffer), 
                                    ADR(QUEUE));
        break;
    case 2:
        pcc.Set_bExecute(true);
        xStartIpo = true;
        if (RobotControl.bDone) {
            SMC_OutQueueInit(ADR(QUEUE));
            if (bLoopRun) {
                iState = 3;
            } else {
                iState = 0;
            }
        }
        break;
    case 3:
        QUEUE.pbyBuffer = ADR(BUF[0]);
        SM3_CNC::SMC_SetQueueCapacity(ADR(QUEUE), SIZEOF(BUF));
        xStart = false;
	    xStartIpo = false;
	    CheckVel.Set_bExecute(false);
	    iState = 1;
        break;	
    default:
        break;
    }

    CheckVel.Set(true, ADR(QUEUE));
}