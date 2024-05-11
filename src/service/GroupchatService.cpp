
#include"service/GroupchatService.h"
#include"model/GroupModel.h"
#include"model/UnreadGroupMessageModel.h"
GroupchatService::GroupchatService(/* args */)
{
}

GroupchatService::~GroupchatService()
{
}

 void GroupchatService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
   
      int handle_=js["handle_value"].asInt();
      switch (handle_)
      {
      case 1:
         history_handle(conn,js);
        break;
      case 2:
          groupchat_handle(conn,js);
      break;
      }
       return;
 }
/*
  {
    ”handle_value“：1
     "GroupID":
    "history_number":     //用来返回数据库的哪些历史数据
  }
*/
void GroupchatService::history_handle(const TcpConnectionPtr &conn,Json::Value &js)const{
      Json::Value ack;
      ack["msg_id"]=static_cast<int>(ServerMessage::GROUP_CHAT_MSG_ACK);
         Json::Value msg_value;
         msg_value["handle_value"]=1;
         msg_value["GroupID"]=js["GroupID"].asInt();
         auto  vec_UnreadGroupMessage=UnreadGroupMessageModel{}.query(js["GroupID"].asInt(),js["history_number"].asInt());
         Json::Value UnreadGroupMessage;
         for(const auto&x:vec_UnreadGroupMessage){
             Json::Value data;
             data["Content"]=x.getContent();
             data["SendTime"]=x.getSendTime();
            data["SenderID"]=x.getSenderID();
             UnreadGroupMessage.append(data);
         }
         msg_value["UnreadGroupMessage"]=UnreadGroupMessage;
         ack["msg_value"]=msg_value;
          Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack);

         conn->send(muduo::StringPiece(jsonString));

         LOG_DEBUG<<"群历史消息查询成功";
         return;
}
/*
{
    "msg_id":GROUP_CHAT_MSG_ACK
     "msg_vlaue":{
        ”handle_value“：1
         "GroupID":
        “UnreadGroupMessage”:[{
           "Content":
           "SendTime":
           "SenderID":
           }
        ]
      
     }
}
*/

/*
   {
    ”handle_value“:2
    "Content":
    "SendTime":
    "SenderID":
    "GroupID":
   }
*/
void GroupchatService::groupchat_handle(const TcpConnectionPtr &conn,Json::Value &js)const{

 //  1：插入群消息，保留历史数据（防止数据库压力过大，采用消息队列异步处理，尚未完成）
         
  // 2：找到群里面在线用户转发消息,线程安全。
      Json::Value ack;
      ack["msg_id"]=static_cast<int>(ServerMessage::GROUP_CHAT_MSG_ACK);
      ack["msg_value"]=js;
      Json::FastWriter fastWriter;
      std::string jsonString = fastWriter.write(ack);   
      auto vec_groupmembers_=GroupModel{}.query_gropumembers(js["GroupID"].asInt());//群表所有用户
      for(auto &x:vec_groupmembers_){
          if(user_connection_map.contains(x)){  //n1 * logn2复杂度，加n1个读锁开销
                    (user_connection_map.get(x))->second->send(jsonString);
          }
      }
      LOG_DEBUG<<"群消息转发测试成功";
      return;
}
/*
{
    "msg_id":GROUP_CHAT_MSG_ACK
     "msg_vlaue":{
      "handle_value“：2
      "Content":
      "SendTime":
      "SenderID":
      "GroupID":
     }
}
*/