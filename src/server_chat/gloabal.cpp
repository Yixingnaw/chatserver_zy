#include"gloab/gloabal.h"
#include"gloab/MessageQueue.h"
#include<string>
  //连接数据库，初始化数据库连接池4
 std::string connection_string("mysql:database=server;user=root;password='511304Woaini@'"); 
    ThreadSafeVector<int> gloabal_users;//服务器所有的在线用户,线程安全
     ThreadSafeMap<int,muduo::net::TcpConnectionPtr> user_connection_map;
    cppdb::pool::pointer my_pool = cppdb::pool::create(connection_string);

cppdb::session db_connector(cppdb::pool::pointer& x){
         cppdb::session sql(x->open());
         return sql;
}
MessageQueue<UnreadGroupMessage> messageQueue;//消息队列