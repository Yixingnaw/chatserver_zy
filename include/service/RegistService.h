#ifndef REGISTSERVICE__H
#define REGISTSERVICE__H
#include"gloab/gloabal.h"
#include"model/UserModel.h"
#include"service/service.h"
using namespace muduo;
using namespace muduo::net;

class RegistService:public service
{
private:
    /* data */
public:
    RegistService(/* args */);
    ~RegistService();
void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};




#endif