#include "service/ChatService.h"

ChatService::ChatService(/* args */)
{
 
      std::shared_ptr<RegistService> regist= std::make_shared<RegistService>();
      std::shared_ptr< LoginService>  login= std::make_shared<LoginService>();

    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::LOGIN_MSG),std::move(login)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::REG_MSG),std::move(regist)));
}

ChatService::~ChatService()
{
}
ChatService&  ChatService::instance(){
      static ChatService x;
      return x;
}
std::shared_ptr<service>  ChatService:: get_handler(int x){
    return msg_hander[x];
}
