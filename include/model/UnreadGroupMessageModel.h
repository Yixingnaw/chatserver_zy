#ifndef UNREADGROUPMESSAGEMODEL_H_
#define UNREADGROUPMESSAGEMODEL_H_
#include"model/UnreadGroupMessage.h"
#include<vector>
class UnreadGroupMessageModel
{//尚未完成
private:
    /* data */
public:
    UnreadGroupMessageModel(/* args */);
    ~UnreadGroupMessageModel();
       bool insert(UnreadGroupMessage &grouomessage);
    
      //根据ID查询
    std::vector<UnreadGroupMessage> query(int groupid);

    //根据id查询之后，删除数据
    bool delete_UserMessage(int groupid);
};



#endif