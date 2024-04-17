#ifndef ADDFRIENDSERVICE_H_
#define ADDFRIENDSERVICE_H_
#include"gloab/gloabal.h"
#include"model/UserModel.h"
#include"service/service.h"
using namespace muduo;
using namespace muduo::net;
class AddFriendService:public service
{//还没测试
private:
    /* data */
public:
    AddFriendService(/* args */);
    ~AddFriendService();
    void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};


#endif