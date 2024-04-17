#include "service/ChatService.h"

ChatService::ChatService(/* args */)
{
    //注册不同的回调函数
      std::shared_ptr<RegistService> regist= std::make_shared<RegistService>();
      std::shared_ptr< LoginService>  login= std::make_shared<LoginService>();
      std::shared_ptr< FriendchatService>  friendchat= std::make_shared<FriendchatService>();
      std::shared_ptr<GroupchatService>  groupchat= std::make_shared<GroupchatService>();
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::LOGIN_MSG),std::move(login)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::REG_MSG),std::move(regist)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::ONE_CHAT_MSG),std::move(friendchat)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::GROUP_CHAT_MSG),std::move(groupchat)));
    
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
