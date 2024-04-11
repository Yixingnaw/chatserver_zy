#ifndef USERMODEL_H
#define USERMODEL_H

#include "model/User.h"

//User表的数据操作类
class UserModel
{
public:
    //增加User
    bool insert(User &user);

    //根据ID查询user信息
    User query(int id);

    //更新状态操作
    bool update_state(User user);

    //重置用户状态信息
    bool reset_state();

    bool is_hava_user(User user);
    //查询是否在线
    bool is_online(int userid);
};
#endif