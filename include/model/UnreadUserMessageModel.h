#ifndef UNREADUSERMESSAGEMODEL_H
#define UNREADUSERMESSAGEMODEL_H
#include"model/UnreadUserMessage.h"
class UnreadUserMessageModel{

    public:
    bool insert(UnreadUserMessage &unreadUsermessage);
    
      //根据ID查询
     UnreadUserMessage query(int UnreadUserMessageid);


    //根据id查询之后，删除数据
    bool delete_UnreadUserMessage(int UnreadUserMessageid);
};
#endif
