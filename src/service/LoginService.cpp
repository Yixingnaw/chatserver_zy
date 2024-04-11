#include"service/LoginService.h"

LoginService::LoginService(/* args */)
{
    
}

LoginService::~LoginService()
{
}
// 
void LoginService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
          Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::LOGIN_MSG_ACK);
        //检测账号密码是否正确
        User user;
        user.setId(js["UserID"].asInt());
        user.setPassword(js["Password"].asString());
        if(!UserModel().is_hava_user(user)){
               ack["msg_value"]=std::string("密码错误");
         Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
          conn->send(muduo::StringPiece(jsonString));
              return;

        }
        user= UserModel().query(user.getId());
        //检测是否在线
      if(gloabal_users.find(user.getId())){
       //在线（这个有问题，正常逻辑应该是挤出另一个在线的客户端）
          ack["msg_value"]=std::string("用户在线");
            Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
          conn->send(muduo::StringPiece(jsonString));
        
              return;
      }
      
       //不在线，插入在线列表，更新数据库状态,登陆成功
       Json::Value msg_value;
        user_connection_map.insert(user.getId(),conn);
       UserModel().update_state(user);
        
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
       //返回用户未读好友消息

       //返回用户未读群消息,待完成

     //   ack["msg_value"]=std::string("用户在线");
      

}