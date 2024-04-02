#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
#include <string>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;
//基于muduo网络库开发服务器程序
class ChatServer
{



public:
    //3、明确TcpServer构造函数需要的参数，输出服务器对应类的构造函数
    ChatServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg) //事件循环、IP+port、服务器名字
    : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        //4.1、注册用户连接的创建和断开事件的回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); //利用绑定器绑定成员方法onConnection,保持参数与muduo库函数参数一致
        
        //4.2、注册用户读写事件的回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3)); //利用绑定器绑定成员方法onMessage,保持参数与muduo库函数参数一致

        //5、设置服务器端的线程数量
        _server.setThreadNum(4);
    }

    //6.开启事件循环
    void start()
    {
        _server.start();
    }

private:
    //4.1 专门处理用户的连接和断开
    void onConnection(const TcpConnectionPtr &conn) //连接
    {
        if (conn->connected())
        {
           std::cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:online" << std::endl;
        }
        else
        {
          std::cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:offline" << std::endl;
            conn->shutdown(); //连接断开将socket资源释放
            //或者调用_loop->quit()退出epoll;
        }
    }

    //4.2 专门处理用户读写事件
    void onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time) //连接、缓冲区、接收到数据的事件信息
    {
        std::string buf = buffer->retrieveAllAsString(); //将接收数据全部放入字符串中
        std::cout << "recv data:" << buf << " time:" << time.toString() << std::endl;
        conn->send(buf); //收到什么数据发回去什么数据
    }

    TcpServer _server; //1、组合TcpServer对象
    EventLoop *_loop; //2、创建EventLoop事件循环对象的指针
};

