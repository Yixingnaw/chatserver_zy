#ifndef GROUPCHATSERVICE_H_
#define GROUPCHATSERVICE_H_
#include"gloab/gloabal.h"
#include"service/service.h"
#include "json/json.h"
using namespace muduo;
using namespace muduo::net;
class GroupchatService:public service
{
private:
    /* data */
public:
    GroupchatService(/* args */);
    ~GroupchatService();
     void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};



#endif