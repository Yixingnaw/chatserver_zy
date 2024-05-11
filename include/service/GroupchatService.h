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
     
     void history_handle(const TcpConnectionPtr &conn,Json::Value &js)const;//客户端加载历史群消息请求
     void groupchat_handle(const TcpConnectionPtr &conn,Json::Value &js)const;//客户端群聊信息请求；
};



#endif