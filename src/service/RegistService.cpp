#include"service/RegistService.h"

RegistService::RegistService(/* args */)
{
}

RegistService::~RegistService()
{
}
void  RegistService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time){
       User user;
       user.setPassword(js["Password"].asString());
       user.setPersonalSignature(js["PersonalSignature"].asString());
       user.setState(false);
      if(UserModel().insert(user)){
          Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::REG_MSG_ACK);
          ack["msg_value"]=std::string("注册成功");  
         conn->send(muduo::StringPiece(ack.asString()));
          return;
      }
      else{
        Json::Value ack;
          ack["msg_id"]= static_cast<int>(ServerMessage::REG_MSG_ACK);
          ack["msg_value"]=std::string("注册失败");
          conn->send(muduo::StringPiece(ack.asString()));
      
          return;
  }

}