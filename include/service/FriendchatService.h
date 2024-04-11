#ifndef FRIENDCHATSERVICE_H_
#define FRIENDCHATSERVICE_H_
#include"gloab/gloabal.h"
#include"service/service.h"
#include "json/json.h"
using namespace muduo;
using namespace muduo::net;
class FriendchatService:public service
{
    //未测试
private:
    /* data */
public:
    FriendchatService(/* args */);
    ~FriendchatService();
      void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};


#endif