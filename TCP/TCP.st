PROGRAM TCPClient
VAR CONSTANT
	c_tInterval		: TIME:=T#0.5S;;
END_VAR
VAR
	ipAddress	: NBS.IP_ADDR;
	fbTcpClient	: NBS.TCP_Client;
	fbTcpRead	: NBS.TCP_Read;
	fbTcpWrite	: NBS.TCP_Write;
	abyTx		: ARRAY[0..gvlSetting.gc_wMaxTelegram] OF  BYTE;
	abyRx		: ARRAY[0..gvlSetting.gc_wMaxTelegram] OF  BYTE;
	
	fbBlink		: BLINK:=(TIMELOW:=c_tInterval,TIMEHIGH:=c_tInterval);
	xBlink		: BOOL;
	
	udiVal		: UDINT;
	pudiVal		: POINTER TO BYTE;
	iIndex		: INT;
	xConnect	: BOOL;
	
	xRead		: BOOL;
	xMissingAck	: BOOL;
	udiResult	: UDINT;
	udiLastAck	: UDINT;
	udiNow		: UDINT;
	udiRead		: UDINT;
	eRErrorID	: NBS.ERROR;
	eWErrorID	: NBS.ERROR;
	
	ComposeJSON	:STRUCT_TO_JSON;
	sMessage	:SenMessage;
	SendString:STRING(1000);
	SendFlage	: BOOL:=FALSE;
	GetSysTimeMS : GetSystemTimeHigh;
	sTimeStamp	:STRING;
END_VAR

IF NOT fbTcpClient.xActive THEN
	ipAddress.sAddr:=gvlSetting.gc_stIpAddr;
END_IF

fbTcpClient(xEnable:=xConnect,ipAddr:=ipAddress,uiPort:=gvlSetting.gc_uiPort,udiTimeOut:=0);
GetSysTimeMS(GetTimeMs=>sTimeStamp);
fbBlink(ENABLE:=TRUE);
IF(fbBlink.OUT AND (xBlink <> fbBlink.OUT)) THEN
	SendFlage:=NOT SendFlage;
	IF SendFlage THEN
		
		sMessage.AxisXP.Number:=AxisXPoint;
		sMessage.AxisYP.Number:=AxisYPoint;
		sMessage.AxisZP.Number:=AxisZPoint;
		sMessage.TimeStamp.CharString:=sTimeStamp;
		ComposeJSON(
			Execute:=TRUE,
    		JSONString:= ADR(SendString), 
    		JSONStringSize:= SIZEOF(SendString),
    		JSONVars:= ADR(sMessage),
    		NumberOfVars:= SIZEOF(sMessage) / SIZEOF(JSONVAR)
		);
		IF fbTcpClient.eError=0 AND fbTcpClient.hConnection<>0 THEN
			fbTcpWrite(xExecute:=xConnect,hConnection:=fbTcpClient.hConnection,udiTimeOut:=5000,szSize:=len(SendString),pData:=ADR(SendString),eError=>eWErrorID);
		END_IF
	ELSE
		fbTcpWrite(xExecute:=FALSE);
		AxisXPoint:=AxisXPoint+0.1;
		ComposeJSON(
			Execute:=FALSE,
    		JSONString:= ADR(SendString), 
    		JSONStringSize:= SIZEOF(SendString),
    		JSONVars:= ADR(sMessage),
    		NumberOfVars:= SIZEOF(sMessage) / SIZEOF(JSONVAR)
		);
	END_IF
END_IF

xBlink:=fbBlink.OUT;

IF NOT fbTcpClient.xActive AND NOT  fbTcpClient.xBusy AND NOT fbTcpClient.xDone THEN
	xConnect:=TRUE;
ELSE
//	xConnect:=FALSE;
END_IF


