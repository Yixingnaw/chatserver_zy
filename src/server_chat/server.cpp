#include <functional>
#include <string>
#include <iostream>
#include "gloab/server.h"
#include "json/json.h"
using namespace muduo;
using namespace muduo::net;
using namespace std; 
using namespace placeholders;

//初始化聊天服务器对象
Server::Server(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg)
    : server_(loop, listenAddr, nameArg),
      loop_(loop)
{
    //注册连接回调
    server_.setConnectionCallback(bind(&Server::on_connection, this, _1));

    //注册消息回调,子线程异步调用
    server_.setMessageCallback(bind(&Server::on_message, this, _1, _2, _3));

    //设置线程数量
    server_.setThreadNum(4);

    
}

//启动服务
void Server::start()
{
    server_.start();
}

//上报连接相关信息的回调函数
void Server::on_connection(const TcpConnectionPtr &conn)
{
    //用户断开连接
    if (!conn->connected())
    {
     if(user_connection_map.contains(conn)){
        //如果是在线用户断开连接
        auto user_id= user_connection_map.remove(conn);
        conn->shutdown();
        LOG_INFO<< user_id <<"断开连接";  
        return;
     }else{
        //其他连接断开，譬如说注册等
     LOG_INFO<<"客户端断开连接";
         return;
     }
    }
    LOG_INFO<<"新连接";
}

//上报读写时间相关信息的回调函数
void Server::on_message(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
                                                          LOG_DEBUG<<"exute: "<<buf;
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(buf, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
  {
   //解耦网络和业务模块的代码
    //通过js里面的msgid，绑定msgid的回调函数，获取业务处理器handler
    auto  msg_handler= ChatService::instance().get_handler(root["msg_id"].asInt());//返回service对象

          
       (*msg_handler)(conn, root["msg_value"], time);
  }
    
}
