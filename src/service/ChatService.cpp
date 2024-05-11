#include "service/ChatService.h"

ChatService::ChatService(/* args */)
{
    //注册不同的回调函数
      std::shared_ptr<RegistService> regist= std::make_shared<RegistService>();
      std::shared_ptr< LoginService>  login= std::make_shared<LoginService>();
      std::shared_ptr< FriendchatService>  friendchat= std::make_shared<FriendchatService>();
      std::shared_ptr<GroupchatService>  groupchat= std::make_shared<GroupchatService>();
      std::shared_ptr<AddFriendService> addfriend= std::make_shared<AddFriendService>();
      std::shared_ptr<AddGroupService> addgroup= std::make_shared<AddGroupService>();
      std::shared_ptr<CreatGroupService> craetgroup= std::make_shared<CreatGroupService>();
      std::shared_ptr<LoginOutService> loginout= std::make_shared<LoginOutService>();
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::LOGIN_MSG),std::move(login)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::REG_MSG),std::move(regist)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::ONE_CHAT_MSG),std::move(friendchat)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::GROUP_CHAT_MSG),std::move(groupchat)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::ADD_FRIEND_MSG),std::move(addfriend)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::ADD_GROUP_MSG),std::move(addgroup)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::CREATE_GROUP_MSG),std::move(craetgroup)));
    msg_hander.insert(std::make_pair(static_cast<int>(ServerMessage::LOGINOUT_MSG),std::move(loginout)));
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
