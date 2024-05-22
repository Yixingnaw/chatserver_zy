#include"gloab/gloabal.h"
#include"gloab/MessageQueue.h"
#include<string>

    ThreadSafeVector<int> gloabal_users;//服务器所有的在线用户,线程安全
     ThreadSafeMap<int,muduo::net::TcpConnectionPtr> user_connection_map;
cppdb::session db_connector(cppdb::pool::pointer& x){
         cppdb::session sql(x->open());
         return sql;
}
MessageQueue<UnreadGroupMessage> messageQueue;//消息队列