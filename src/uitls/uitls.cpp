#include"uitls/uitls.h"
#include <arpa/inet.h>  
void   chatserver_uitls::asyncOutput(const char* msg, int len){
       asyncLog.append(msg, len);
}

uint64_t chatserver_uitls::htonll(uint64_t host64) {
    uint32_t high_part = htonl(static_cast<uint32_t>(host64 >> 32));
    uint32_t low_part = htonl(static_cast<uint32_t>(host64 & 0xFFFFFFFF));
    return (static_cast<uint64_t>(low_part) << 32) | high_part;
}