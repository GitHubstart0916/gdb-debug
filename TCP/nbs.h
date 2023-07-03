#ifndef NBS_H
#define NBS_H

namespace nbs {
    typedef ip_addr IP_ADDR;
    typedef tcp_client TCP_Client;
    typedef int TCP_Read;
    typedef tcp_write TCP_Write;
    typedef int ERROR;
}

namespace gvlSetting {
    const int gc_wMaxTelegram = 100;
    const int gc_stIpAddr = 100;
    const int gc_uiPort = 100;
}

class tcp_client
{
private:
    /* data */ 
public:
    tcp_client(int xEnable, int ipAddr, int uiPort, int udiTimeOut);
    int xActive;
    int xDone;
    int xBusy;
    int eError;
    int hConnection;
    ~tcp_client();
};

class ip_addr
{
private:
    /* data */
public:
    ip_addr(/* args */);
    int sAddr;
    ~ip_addr();
};

class tcp_write
{
private:
    /* data */
public:
    tcp_write(BOOL, int, int, int, int, nbs::ERROR);
    void set_xExecute(BOOL);
    ~tcp_write();
};







#endif