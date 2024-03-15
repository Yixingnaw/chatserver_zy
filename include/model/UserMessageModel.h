#ifndef USERMESSAGEMODEL__H__
#define USERMESSAGEMODEL__H__
#include"model/UserMessage.h"
#include<vector>
class UserMessageModel
{
private:
    /* data */
public:
     bool insert(UserMessage &usermessage);
    
      //根据ID查询
    std::vector<UserMessage> query( std::vector<int> UserMessageid);


    //根据id查询之后，删除数据
    bool delete_UserMessage(int Userid);
     
};




#endif