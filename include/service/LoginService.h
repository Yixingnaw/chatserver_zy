#ifndef LOGIN_SERVICE_
#define LOGIN_SERVICE_
#include"gloab/gloabal.h"
#include"service/service.h"
#include "json/json.h"

#include"model/FriendshipModel.h"
#include"model/GroupModel.h"
#include"model/UnreadUserMessageModel.h"
#include"model/UserMessageModel.h"
#include"model/UserModel.h"
using namespace muduo;
using namespace muduo::net;
class LoginService:public service
{//还没测试
private:
    /* data */
public:
    LoginService(/* args */);
    ~LoginService();
    void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};


#endif