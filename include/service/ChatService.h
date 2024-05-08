#ifndef CHATSERVICE__H
#define CHATSERVICE__H
#include"gloab/gloabal.h"
#include"service/LoginService.h"
#include"service/RegistService.h"
#include"service/FriendchatService.h"
#include"service/GroupchatService.h"
#include<map>
#include<memory>
class ChatService
{
private:
    /* data */
        ChatService(/* args */);
    ~ChatService();
    
    std::map<int,std::shared_ptr<service>> msg_hander;//不同的消息对应不同的service对象
public:

    static ChatService& instance();//创造单例对象（不是单个）
    std::shared_ptr<service> get_handler(int);
    
};


#endif