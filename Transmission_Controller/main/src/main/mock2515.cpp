#include "mock2515.h"

#ifdef TEST
void MCP2515::sendMessage(struct can_frame *frame)
{
    // Implementation code here
}

// Definitions for other static methods
void MCP2515::reset()
{
    // Implementation code here
}

void MCP2515::setBitrate(int bps, int mhz)
{
    // Implementation code here
}

void MCP2515::setNormalMode()
{
    // Implementation code here
}

int MCP2515::readMessage(struct can_frame *frame)
{
    // Implementation code here
    return ERROR_OK; // Example return value
}

void MockSerial::println(double num)
{
    // Initialize serial communication with the given baud rate
}
void MockSerial::println(String s)
{
    // Initialize serial communication with the given baud rate
}
void MockSerial::print(uint32_t u){

}

void MockSerial::print(String u){
    
}

void MockSerial::begin(int i){
    
}

int MockSerial::read(){
    return 0;
}

MockSerial::MockSerial(){

}

MCP2515::MCP2515(int i){

}
#endif