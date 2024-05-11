#ifndef LOGINOUTSERVICE_H_
#define LOGINOUTSERVICE_H_
#include"gloab/gloabal.h"
#include"model/UserModel.h"
#include"service/service.h"
using namespace muduo;
using namespace muduo::net;
class LoginOutService:public service//客户端退出登陆
{
private:
    /* data */
public:
    LoginOutService(/* args */);
    ~LoginOutService();
    void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};


#endif