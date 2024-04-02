#include"service/LoginService.h"
#include"model/FriendshipModel.h"
#include"model/GroupModel.h"
#include"model/UnreadUserMessageModel.h"
#include"model/UserMessageModel.h"
#include"model/UserModel.h"
LoginService::LoginService(/* args */)
{
    
}

LoginService::~LoginService()
{
}
// 
void LoginService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time){
          Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::LOGIN_MSG_ACK);
        //检测账号密码是否正确
        User user;
        user.setId(js["UserID"].asInt());
        user.setPassword(js["Password"].asString());
        if(!UserModel().is_hava_user(user)){
               ack["msg_value"]=std::string("密码错误");
               conn->send(muduo::StringPiece(ack.asString()));
              return;

        }
        user= UserModel().query(user.getId());
        //检测是否在线
      if(gloabal_users.find(user)){
       //在线（这个有问题，正常逻辑应该是挤出另一个在线的客户端）
          ack["msg_value"]=std::string("用户在线");
               conn->send(muduo::StringPiece(ack.asString()));
              return;
      }
      
       //不在线，插入在线列表，更新数据库状态,登陆成功
       Json::Value ack1;
       gloabal_users.push_back(user);
       UserModel().update_state(user);

       //返回用户好友列表
  
       //返回用户群组列表

       //返回用户未读好友消息

       //返回用户未读群消息

     //   ack["msg_value"]=std::string("用户在线");
      

}