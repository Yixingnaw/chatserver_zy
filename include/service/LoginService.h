#ifndef LOGIN_SERVICE_
#define LOGIN_SERVICE_
#include"gloab/gloabal.h"
#include "json/json.h"
using namespace muduo;
using namespace muduo::net;
class LoginService
{
private:
    /* data */
public:
    LoginService(/* args */);
    ~LoginService();
    void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time);
};


#endif