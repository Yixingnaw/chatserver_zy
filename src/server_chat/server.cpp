#include <functional>
#include <string>
#include <iostream>
#include"model/UserModel.h"
#include "gloab/server.h"
#include "json/json.h"
using namespace muduo;
using namespace muduo::net;
using namespace std; 
using namespace placeholders;

//初始化聊天服务器对象
Server::Server(EventLoop    *loop, const InetAddress &listenAddr, const std::string &nameArg)
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
         auto user_id= user_connection_map.remove(conn);
        User user__;
        user__.setId(user_id);
        user__.setState(false);
        UserModel().update_state(user__);
        conn->shutdown();
        LOG_INFO<< user_id <<"断开连接";  
        //取消定时器
         TimerId timerId = boost::any_cast<TimerId>(conn->getContext());
            conn->getLoop()->cancel(timerId);
        return;
     }else{
        //其他连接断开，譬如说注册等
           conn->shutdown();
        LOG_INFO<<"socket断开连接";  
          //取消定时器
           TimerId timerId = boost::any_cast<TimerId>(conn->getContext());
            conn->getLoop()->cancel(timerId);
         return;
     }
    }
    //第一次新连接
     auto timerId = conn->getLoop()->runEvery(200, [this, conn] {
                onTimeout(conn);
            });
        conn->setContext(timerId); // 保存定时器 ID 到连接上下文中

    LOG_INFO<<"有socket新连接";
      

}

//上报读写时间相关信息的回调函数
void Server::on_message(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
try{
    string buf = buffer->retrieveAllAsString();
                                                         LOG_DEBUG<<"exute: "<<buf;
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(buf, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
  {
    //通过js里面的msgid，绑定msgid的回调函数，获取业务处理器handler
    auto  msg_handler= ChatService::instance().get_handler(root["msg_id"].asInt());//返回service对象     
       (*msg_handler)(conn, root["msg_value"], time);
     
  }
    //如果是注册消息，就重置conn为onTimeout_logined
     if(ServerMessage::REG_MSG==static_cast<ServerMessage>(root["msg_id"].asInt())){
          TimerId timerId = boost::any_cast<TimerId>(conn->getContext());
        conn->getLoop()->cancel(timerId);
        timerId = conn->getLoop()->runEvery(200, [this, conn] {
                 onTimeout(conn);
        });
        conn->setContext(timerId);
   }
   else {  //其他消息，心跳包或者啥，客户端登陆之后才开启心跳包文
      
           TimerId timerId = boost::any_cast<TimerId>(conn->getContext());
        conn->getLoop()->cancel(timerId);
        timerId = conn->getLoop()->runEvery(7200, [this, conn] {
                onTimeout_logined(conn);
        });
        conn->setContext(timerId);
   }
    return;
}catch (...) {
        LOG_ERROR << "Unknown error xx_service ";
        return;
           }
}
//未登录断开连接函数
void   Server::onTimeout(const TcpConnectionPtr& conn){
        conn->shutdown();
        LOG_INFO<<"未登陆socket断开连接--来自定时器";  
        return;
 }
 //已经登陆断开连接函数
void   Server::onTimeout_logined(const TcpConnectionPtr& conn){
       if(user_connection_map.contains(conn)){
         auto user_id= user_connection_map.remove(conn);
        User user__;
        user__.setId(user_id);
        user__.setState(false);
        UserModel().update_state(user__);
        conn->shutdown();
        LOG_INFO<< user_id <<"断开连接--来自定时器";  
        return;
     }
}