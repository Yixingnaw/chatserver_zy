#ifndef REGISTSERVICE__H
#define REGISTSERVICE__H
#include"gloab/gloabal.h"
#include"model/UserModel.h"
using namespace muduo;
using namespace muduo::net;
//还没有测试
class RegistService
{
private:
    /* data */
public:
    RegistService(/* args */);
    ~RegistService();
void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time);
};




#endif