#include"service/AddFriendService.h"
#include"model/FriendshipModel.h"

AddFriendService::AddFriendService(/* args */)
{
}

AddFriendService::~AddFriendService()
{
}
/*
{
     "msg_id":
     "msg_vlaue":{
         "FriendRemark":
         "UserID":
         "GroupID":
         "UserID":
     }   
     注意role和jointime格式
}
*/
void AddFriendService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
       Friendship friendship_;
      friendship_.setFriendRemark(js["FriendRemark"].asString());
      friendship_.setUserID(js["UserID"].asInt());
      friendship_.setFriendID(js["FriendID"].asInt());
      FriendshipModel().add_friendship()
      //需要根据返回值来判断是否添加成功
}
