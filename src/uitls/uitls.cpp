#include"uitls/uitls.h"
void   uitls::asyncOutput(const char* msg, int len){
       asyncLog.append(msg, len);
}
