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

/*
   1：插入群消息，保留历史数据（防止数据库压力过大，采用消息队列异步处理，尚未完成）
   2：找到群里面在线用户转发消息。
*/

#endif