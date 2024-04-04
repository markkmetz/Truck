#ifndef _MOCK2515_H 
#define _MOCK2515_H 


struct can_frame {
    int can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    int    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    int    data[8];
};

int CAN_500KBPS;
int MCP_8MHZ;

class MCP2515
{
    public:
        enum ERROR {
            ERROR_OK        = 0,
            ERROR_FAIL      = 1,
            ERROR_ALLTXBUSY = 2,
            ERROR_FAILINIT  = 3,
            ERROR_FAILTX    = 4,
            ERROR_NOMSG     = 5
        };


    void sendMessage(struct can_frame &can_frame);
    MCP2515(int num);
    void reset();
    void setBitrate(int bps, int mhz);
    void setNormalMode();
    int readMessage(struct can_frame &frame);
};

#endif