#include"service/FriendchatService.h"
#include"model/FriendshipModel.h"
#include"model/UserMessageModel.h"
#include"model/UnreadUserMessageModel.h"
#include"model/UserModel.h"
#include"algorithm"
FriendchatService::FriendchatService(/* args */)
{
}

FriendchatService::~FriendchatService()
{
}
/*
   {
    "Content":
    "SendTime":
    "SenderID":
    "ReceiverID":
   }
*/

void   FriendchatService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
        Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::ONE_CHAT_MSG_ACK);
    //查询是否在线
    if(user_connection_map.contains(js["ReceiverID"].asInt())){
        //找到好友socket转发消息
      auto friend_socket_ptr=user_connection_map.get(js["ReceiverID"].asInt());
           ack["msg_value"]=js;
        Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack);   
         friend_socket_ptr->second->send(muduo::StringPiece(jsonString));   
    }else
    //不在线写入数据库表
    {
        std::string Content=js["Content"].asString();
        std::string SendTime=js["SendTime"].asString();
        int SenderID=js["SenderID"].asInt();
        int ReceiverID=js["ReceiverID"].asInt();
      UserMessage friend_message(Content,SendTime,SenderID,ReceiverID);
      UserMessageModel().insert(friend_message);
      UnreadUserMessage friend_unreadusemessage(ReceiverID,friend_message.getMessageID());
      UnreadUserMessageModel().insert(friend_unreadusemessage);
    }
    
}