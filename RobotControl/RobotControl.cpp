#include "type.h"
#include "mc_power.h"
int main() {
    RobotControl();
}

void RobotControl() {
    CONST_VAR:

    NON_CONST_VAR:
        BOOL bDone;
        int iState;
        MC_Power pA, pB, pC;
        SMC_Interpolator ipo;
        SM3_CNC::SMC_TRAFO_Gantry3 trafo;
        SMC_ControlAxisByPos cabpa;
        SMC_ControlAxisByPos cabpb;
        SMC_ControlAxisByPos cabpc;
        VisuStruct3DPathPoint pointbuffer_pt[1001];
        SMC_PositionTracker pt;
        SM3_CNC::SMC_TRAFOF_Gantry3 trafof;
    MAIN:
        pA = MC_Power(true, true, true, AxisA);
        pB = MC_Power(true, true, true, AxisB);
        pC = MC_Power(true, true, true, AxisC);
        switch (iState) {
            case 0:
                if (pA.Status && pB.Status && pC.Status) {
                    iState = 1;
                }
                break;
            case 1:
                Interpolation();
                break;
            
            default:
                break;
        }
        
}