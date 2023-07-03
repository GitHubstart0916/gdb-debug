#include<time.h>
#include "nbs.h"
#include "type.h"
#include "blink.h"
#include "SenMessage.h"
#include "lib.h"
int main() {
    TCPClient();
}

void TCPClient() {
    CONST_VAR:
        time_t c_tInterval = 0.5;
    NON_CONST_VAR:
        nbs::IP_ADDR ipAddres;
        nbs::TCP_Client fbTcpClient;
        nbs::TCP_Read fbTcpRead;
        nbs::TCP_Write fbTcpWrite;
        //gvlSetting.gc_wMaxTelegram
        BYTE abyTx[gvlSetting::gc_wMaxTelegram + 1];
        BYTE abyRx[gvlSetting::gc_wMaxTelegram + 1];
        blink fbBlink = blink(c_tInterval, c_tInterval);
        BOOL xBlink;
        UDINT udiVal;
        BYTE* pudiVal;
        INT iIndex;
        BOOL xConnect;
        BOOL xRead;
        BOOL xMissingAck;
        UDINT udiResult;
        UDINT udiLastAck;
        UDINT udiNow;
        UDINT udiRead;
        nbs::ERROR erErrorID;
        nbs::ERROR eWErrorID;
        STRUCT_TO_JSON ComposeJSON;
        SenMessage sMessage;
        char SendString[1000];
        BOOL SendFLage = false;
        GetSystemTimeHigh GetSystemTimeMS;
        STRING sTimeStamp;
    MAIN:
        if (!fbTcpClient.xActive) {
            ipAddres.sAddr = gvlSetting::gc_stIpAddr;
        }
        fbTcpClient = nbs::TCP_Client(xConnect, ipAddres, 
                                        gvlSetting::gc_uiPort, 0);
        fbBlink.ENABLE(true);
        if (fbBlink.OUT && xBlink < fbBlink.OUT) {
            SendFLage = !SendFLage;
            if (SendFLage) {
                sMessage.AxisXP.Number = AxisXPoint;
                sMessage.AxisYP.Number = AxisYPoint;
                sMessage.AxisZP.Number = AxisZPoint;
                sMessage.TimeStamp.CharString = sTimeStamp;
                ComposeJSON = STRUCT_TO_JSON(true, 
                                            ADR(SendString), 
                                            SIZEOF(SendString), 
                                            ADR(sMessage), 
                                            SIZEOF(sMessage) / SIZEOF(JSONVAR));
                if (fbTcpClient.eError == 0 && fbTcpClient.hConnection != 0) {
                    fbTcpWrite = tcp_write(xConnect, 
                                            fbTcpClient.hConnection, 
                                            5000, 
                                            len(SendString), 
                                            ADR(SendString), 
                                            eWErrorID);
                }
            } else {
                fbTcpWrite.set_xExecute(false);
                int axisXPoint = AxisXPoint + 0.1;
                ComposeJSON = STRUCT_TO_JSON(false, 
                                            ADR(SendString), 
                                            SIZEOF(SendString), 
                                            ADR(sMessage), 
                                            SIZEOF(sMessage) / SIZEOF(JSONVAR));

            }
        }
        xBlink = fbBlink.OUT;
        if (!fbTcpClient.xActive && !fbTcpClient.xBusy && !fbTcpClient.xDone) {
            xConnect = true;
        } else {
            xConnect = false;
        }
}