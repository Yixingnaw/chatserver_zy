#include"service/RegistService.h"

RegistService::RegistService(/* args */)
{
}

RegistService::~RegistService()
{
}
void  RegistService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
       User user;
       user.setPassword(js["Password"].asString());
       user.setUsername(js["Username"].asString());
       user.setPersonalSignature(js["PersonalSignature"].asString());
       user.setState(false);
      if(UserModel().insert(user)){
          Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::REG_MSG_ACK);
          Json::Value msg_value;
          msg_value["value"]=std::string("注册成功");
          ack["msg_value"]=msg_value;
          Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack);   
         conn->send(muduo::StringPiece(jsonString));
                                                                          LOG_DEBUG<<"注册成功账户"<<user.getId()<<"   "<<user.getUsername();
          return;
      }
      else{
        Json::Value ack;
          ack["msg_id"]= static_cast<int>(ServerMessage::REG_MSG_ACK);
          Json::Value msg_value;
          msg_value["value"]=std::string("注册失败");
          ack["msg_value"]=msg_value;
            Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
          conn->send(muduo::StringPiece(jsonString));
                                                                           LOG_DEBUG<<"注册失败"<<user.getUsername();
          return;
  }

}
/*
{
  "msg_id":
  "msg_value":{
    "value":
  }
}
*/
