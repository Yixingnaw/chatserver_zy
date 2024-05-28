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
         "FriendID":
     }   
     注意role和jointime格式
}
*/
void AddFriendService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
          Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::ADD_FRIEND_MSG_ACK);
       Friendship friendship_;
      friendship_.setFriendRemark(js["FriendRemark"].asString());
      friendship_.setUserID(js["UserID"].asInt());
      friendship_.setFriendID(js["FriendID"].asInt());
      
     if(FriendshipModel().add_friendship(friendship_)){
         Json::Value msg_value;
          msg_value["value"]=std::string("添加好友成功");
          ack["msg_value"]=msg_value;
          Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack);   
         message message_data(jsonString);
          conn->send(message_data.data(),message_data.size());
                                                                    LOG_DEBUG<<"添加好友成功";
         return;
     }else{
         Json::Value msg_value;
          msg_value["value"]=std::string("添加好友失败");
          ack["msg_value"]=msg_value;
          Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack);   
        message message_data(jsonString);
          conn->send(message_data.data(),message_data.size());
                                                                    LOG_DEBUG<<"添加好友失败";
         return;
     }
}
/*
{
     "msg_id":
     "msg_vlaue":
}
*/