#include"gloab/gloabal.h"
#include"gloab/MessageQueue.h"
#include<string>

ThreadSafeMap<int,muduo::net::TcpConnectionPtr> user_connection_map;
cppdb::session db_connector(cppdb::pool::pointer& x) {
    try {
        return cppdb::session(x->open());
    } catch (cppdb::cppdb_error const &e) {
        LOG_ERROR << "Database connection error: " << e.what();
        throw; // 重新抛出异常以便外层捕获
    } catch (std::exception const &e) {
        LOG_ERROR << "Standard exception in db_connector: " << e.what();
        throw; // 重新抛出异常以便外层捕获
    } catch (...) {
        LOG_ERROR << "Unknown error in db_connector";
        throw; // 重新抛出异常以便外层捕获
    }
}
MessageQueue<UnreadGroupMessage> UnreadGroup_messageQueue;//消息队列
MessageQueue<UserMessage>      UnreadUser_messageQueue;
