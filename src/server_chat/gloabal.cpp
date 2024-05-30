#include"gloab/gloabal.h"
#include"gloab/MessageQueue.h"
#include<string>

     ThreadSafeMap<int,muduo::net::TcpConnectionPtr> user_connection_map;
cppdb::session db_connector(cppdb::pool::pointer& x){
         cppdb::session sql(x->open());
         return sql;
}
MessageQueue<UnreadGroupMessage> UnreadGroup_messageQueue;//消息队列
MessageQueue<UserMessage>      UnreadUser_messageQueue;