#ifndef GLOABAL___H_
#define GLOABAL___H_
#include"cppdb/backend.h"
#include"cppdb/connection_specific.h"
#include"cppdb/conn_manager.h"
#include"cppdb/defs.h"
#include"cppdb/driver_manager.h"
#include"cppdb/errors.h"
#include"cppdb/frontend.h"
#include"cppdb/numeric_util.h"
#include"cppdb/pool.h"
#include"cppdb/ref_ptr.h"
#include"cppdb/shared_object.h"
#include"cppdb/utils.h"
#include <muduo/base/Logging.h>
#include"json/json.h"

/*用来注册不同的回调函数*/
enum class JsonMessage{
    LOGIN_MSG = 1,  //登录消息，绑定login
    LOGIN_MSG_ACK,  //登录响应消息
    REG_MSG,        //注册消息，绑定regist
    REG_MSG_ACK,    //注册响应消息
    ONE_CHAT_MSG,   //一对一聊天消息
    ADD_FRIEND_MSG, //添加好友消息
    CREATE_GROUP_MSG, //创建群聊
    ADD_GROUP_MSG,    //加入群聊
    GROUP_CHAT_MSG,   //群聊消息
    LOGINOUT_MSG,   //注销消息
};
cppdb::session db_connector(cppdb::pool::pointer&);
std::string woaini111();
extern   cppdb::pool::pointer my_pool;

#endif