PROGRAM RobotControl
VAR
	bDone:BOOL;
	iState: INT;
	pA, pB, pC: MC_Power;
	ipo: SMC_Interpolator;
	trafo: SM3_CNC.SMC_TRAFO_Gantry3;
	cabpa: SMC_ControlAxisByPos;
	cabpb: SMC_ControlAxisByPos;
	cabpc: SMC_ControlAxisByPos;
	pointbuffer_pt: ARRAY [0..1000] OF VisuStruct3DPathPoint;
	pt: SMC_PositionTracker;
	trafof: SM3_CNC.SMC_TRAFOF_Gantry3;
END_VAR

pA(
	Enable:=TRUE , 
	bRegulatorOn:=TRUE , 
	bDriveStart:=TRUE , 
	Axis:=AxisA);
pB(
	Enable:=TRUE , 
	bRegulatorOn:=TRUE , 
	bDriveStart:=TRUE , 
	Axis:=AxisB);
pC(
	Enable:=TRUE , 
	bRegulatorOn:=TRUE , 
	bDriveStart:=TRUE , 
	Axis:=AxisC);
	
CASE iState OF
	0:
	   IF pA.Status AND pB.Status AND pC.Status THEN
		   iState:=1;
	   END_IF
	1:
		Interpolation();
	;
END_CASE