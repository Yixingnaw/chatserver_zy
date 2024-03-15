#ifndef FRIENDSHIPMODEL_H
#define FRIENDSHIPMODEL_H
#include"model/Friendship.h"
#include<vector>
#include"model/User.h"
#include"gloab/gloabal.h"
class FriendshipModel
{
public:
    //增加
    bool add_friendship(Friendship&);
    //删除
    bool delete_freindship(Friendship&);
    //查
    std::vector<User> query_friendship(User&);

    
};





#endif
