
#include"service/GroupchatService.h"
#include"model/GroupModel.h"
GroupchatService::GroupchatService(/* args */)
{
}

GroupchatService::~GroupchatService()
{
}
/*
  {
    “”：
  }
*/
 void GroupchatService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{//暂时不保存群未读消息
     Group group_;
     
 }