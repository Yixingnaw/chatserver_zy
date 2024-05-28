#include"service/LoginService.h"
#include<vector>
LoginService::LoginService(/* args */)
{
    
}

LoginService::~LoginService()
{

}
//待测试
void LoginService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
          Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::LOGIN_MSG_ACK);
        //检测账号密码是否正确
        User user;

        user.setPassword(js["Password"].asString());
          user.setId(js["UserID"].asInt());
        if(!UserModel().is_hava_user(user)){
            Json::Value msg_value;
          msg_value["value"]=std::string("密码错误");
              ack["msg_value"]=msg_value;
         Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
           message message_data(jsonString);
          conn->send(message_data.data(),message_data.size());
                                                                        LOG_DEBUG<<jsonString;
              return;
        }
        user= UserModel().query(user.getId());
        //检测是否在线
      if(user_connection_map.contains(user.getId())){
       //在线（这个有问题，正常逻辑应该是挤出另一个在线的客户端）
        Json::Value msg_value;
          msg_value["value"]=std::string("用户在线");
          ack["msg_value"]=msg_value;
            Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
         message message_data(jsonString);
          conn->send(message_data.data(),message_data.size());
        
              return;
      }
      
       //不在线，插入在线列表，更新数据库状态,登陆成功
       Json::Value msg_value;
        user_connection_map.insert(user.getId(),conn);
  //      gloabal_users.push_back(user.getId());
       UserModel().update_state(user);
                                                                               LOG_DEBUG<<"登陆成功";
       //返回用户好友列表
       Json::Value Friendships;
        std::vector<User> vec_user=FriendshipModel().query_friendship(user);
         for(const auto& x:vec_user){
            Json::Value user_;
            user_["UserID"]=x.getId();
            user_["Username"]=x.getUsername();
            user_["PersonalSignature"]=x.getPersonalSignature();
            user_["State"]=x.getState();
           Friendships.append(user_);
         }
         msg_value["Friendship"]=Friendships;
                                                                                 LOG_DEBUG<<"用户所有好友信息获取完毕"; 
       //返回用户群组列表以及对应的群用户
       Json::Value group;
       auto map_group=GroupModel().query_group(user);
       for(const auto&x:map_group){
          Json::Value groupdate;
          Json::Value groupmember;//
          groupdate["GroupID"]=x.first.getGroupID();
          groupdate["GroupName"]=x.first.getGroupName();
          groupdate["Description"]=x.first.getDescription();        
          for(const auto&xx: x.second){
              Json::Value groupmembers;
          groupmembers["Role"]=xx.getRole();
          groupmembers["JoinTime"]=xx.getJoinTime();
          groupmembers["UserID"]=xx.getUserID();
          groupmember.append(groupmembers);
          }
          groupdate["GroupMember"]=groupmember;
          group.append(groupdate);
       }
       msg_value["Group"]=group;                                        
                                                                                LOG_DEBUG<<"用户所有群信息获取完毕";
       //返回用户未读好友消息,记得删除数据库
       Json::Value UnreadUserMessage;
       auto vec_UnreadUserMessageid=UnreadUserMessageModel().query(user.getId());
       UnreadUserMessageModel().delete_UnreadUserMessage(user.getId());
       auto vec_UnreadUserMessage=UserMessageModel().query(vec_UnreadUserMessageid);
       UserMessageModel().delete_UserMessage(user.getId());
       for(const auto &x:vec_UnreadUserMessage){
             Json::Value UnreadUserMessageData;
             UnreadUserMessageData["UserMessageID"]=x.getMessageID();
             UnreadUserMessageData["Content"]=x.getContent();
             UnreadUserMessageData["SendTime"]=x.getDate();
             UnreadUserMessageData["SenderID"]=x.getSenderID();
             UnreadUserMessageData["ReceiverID"]=x.getReceiverID();
             UnreadUserMessage.append(UnreadUserMessageData);
       }
       msg_value["UnreadUserMessage"]=UnreadUserMessage;
                                                                                  LOG_DEBUG<<"用户所有未读消息获取完毕";
      ack["msg_value"]=msg_value;
      Json::FastWriter fastWriter;
      std::string jsonString = fastWriter.write(ack); 
      
      message longin_ack_data(jsonString);
                                                                                     LOG_DEBUG<<jsonString; LOG_DEBUG<<"data数据长度"<<longin_ack_data.size();
      conn->send(longin_ack_data.data(),longin_ack_data.size());
      return;
}
/*
{
    "msg_id":
  "msg_value":{
    "Friendship":[]
    "Group":[
      {"GroupID":
      "GroupName":
      "Description":
      "GroupMember":[]
      }
    ]
    "UnreadUserMessage":[
      {
        
      }
    ]
  }
}size_t
*/