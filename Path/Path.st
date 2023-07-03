PROGRAM Path
VAR
	xStart:BOOL;
	xStartIpo: BOOL;
	iState: INT;
	CheckVel: SMC_CheckVelocities;	

	QUEUE: SMC_OUTQUEUE;
	BUF: ARRAY[0..49] OF SMC_GEOINFO;
	GEO: SMC_GEOINFO:=(dT1:=0, dT2:=1, dToolRadius:=0, dVel:=10, dVelEnd:=5, dAccel:=5, dDecel:=5, iObjNo:=0,b3DMode:=TRUE);
	n: INT:=0;
	xp:ARRAY[1..7] OF REAL:= [0,100,100,100,0,0,0];
	yp:ARRAY[1..7] OF REAL:= [0,100,100,100,0,0,0];
	Zp:ARRAY[1..7] OF REAL:= [0,0,20,0,0,20,0];
	pointbuffer: ARRAY [0..1000] OF VisuStruct3DPathPoint;
	pcc:SMC_PathCopierCompleteQueue;
	vc: VisuStruct3DControl;
	iX,iY,iZ,iZA,iZD:BOOL;
	bLoopRun: BOOL;
END_VAR

IF iX THEN
	vc.iTurnX:=3600;
ELSE
	vc.iTurnX:=0;
END_IF
IF iY THEN
	vc.iTurnY:=3600;
ELSE
	vc.iTurnY:=0;
END_IF
IF iZ THEN
	vc.iTurnZ:=3600;
ELSE
	vc.iTurnZ:=0;
END_IF

IF iZA THEN
	vc.iZ:=360;
ELSIF iZD THEN
	vc.iZ:=-360;
ELSE
	vc.iZ:=0;
END_IF

CASE iState OF 
0:
	//initialize Queue
	IF xStart THEN
	QUEUE.pbyBuffer := ADR(BUF[0]);
	SM3_CNC.SMC_SetQueueCapacity(ADR(QUEUE), SIZEOF(BUF));
	xStart:=FALSE;
	xStartIpo:=FALSE;
	CheckVel(bExecute:=FALSE);
	iState :=1;	
	END_IF
	
1: 	//fill queue

	WHILE NOT QUEUE.bFull DO					// when the Queue is full, wait until it has been processed by the following FBs
		n := n + 1;
		GEO.iSourceLine_No := n;	
		GEO.piStartPos := GEO.piDestPos;		// copy last destination 
		GEO.iMoveType := LIN;					// generate linear movement 
		GEO.iObjNo := GEO.iObjNo + 1;			// calculate number 
		GEO.piDestPos.dX := xp[n];				// generate position 
		GEO.piDestPos.dY := yp[n];
		GEO.piDestPos.dZ := Zp[n];
		SMC_CalcLengthGeo(pg := ADR(GEO));		// calculate length of object with the help of the standard function
		SMC_AppendObj(poq:=ADR(QUEUE), pgi:=ADR(GEO));	//append object to queue 
		IF n = SIZEOF(xp)/SIZEOF(xp[1]) THEN	// all target positions processed
			QUEUE.bEndOfList := TRUE;
			n := 0;
			iState := 2;
			EXIT;
		END_IF
	END_WHILE
	pcc(bExecute:=FALSE , 
			udiNumberOfPointsInArray:=SIZEOF(pointbuffer)/SIZEOF(pointbuffer[0]) , 
			pBuffer:=ADR(pointbuffer) , 
			poqCNCPath:=ADR(QUEUE)); 
2:	//done
	pcc(bExecute:=TRUE);
	xStartIpo:=TRUE;
	IF RobotControl.bDone THEN
	SMC_OutQueueInit(poq:=ADR(QUEUE));
		IF bLoopRun THEN
			iState:=3;
		ELSE
			iState:=0;
		END_IF
	END_IF	
3:
	QUEUE.pbyBuffer := ADR(BUF[0]);
	SM3_CNC.SMC_SetQueueCapacity(ADR(QUEUE), SIZEOF(BUF));
	xStart:=FALSE;
	xStartIpo:=FALSE;
	CheckVel(bExecute:=FALSE);
	iState :=1;	
END_CASE

CheckVel(bExecute:=TRUE , poqDataIn:=ADR(queue));
