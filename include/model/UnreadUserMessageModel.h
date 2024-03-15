#ifndef UNREADUSERMESSAGEMODEL_H
#define UNREADUSERMESSAGEMODEL_H
#include"model/UnreadUserMessage.h"
#include<vector>
class UnreadUserMessageModel{

    public:
    bool insert(UnreadUserMessage &unreadUsermessage);
    
      //根据ID查询
     std::vector<int> query(int userid);

    //根据id查询之后，删除数据
    bool delete_UnreadUserMessage(int userid);
    
};
#endif
