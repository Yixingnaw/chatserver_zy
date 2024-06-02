#include"gloab/chatServer.h"
#include"gloab/gloabal.h"
#include"gloab/server.h"
#include"model/User.h"
#include"iostream"
#include"json/json.h"
#include"model/UserModel.h"
#include"model/UserMessageModel.h"
#include"model/UnreadUserMessageModel.h"
#include"model/GroupModel.h"
#include"model/FriendshipModel.h"
#include"model/UnreadUserMessageModel.h"
#include"model/UnreadGroupMessageModel.h"
#include"service/LoginService.h"
#include"service/RegistService.h"
#include"service/GroupchatService.h"
#include"service/CreatGroupService.h"
#include"service/AddGroupService.h"
#include"service/AddFriendService.h"
#include"service/service.h"
#include"gloab/MessageQueue.h"

  //连接数据库，初始化数据库连接池4
 std::string connection_string("mysql:database=server;user=root;password='511304Woaini@'"); 
  cppdb::pool::pointer my_pool = cppdb::pool::create(connection_string);

int main()
{
     
     muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
      //测试功能函数,不写上会链接不上为啥子
      {
      auto sql=db_connector(my_pool);
       User ass("3,","23","2312",2);
       ass.setId(10);
       User awww= UserModel().query(1);
   auto xxx= UserMessageModel().query(std::vector<int>{1,2,3});
    UnreadUserMessageModel().query(1);
    FriendshipModel().query_friendship(ass);
     auto xxxx=  GroupModel().query_group(ass);
    UnreadUserMessageModel();
    UnreadGroupMessageModel();
    CreatGroupService();
    AddGroupService();
    GroupchatService();
    message();
      }
    //启动数据库异步插入线程
   std::thread  group_consumerThread(UnreadGroupMessage_consumer<UnreadGroupMessage>, std::ref(UnreadGroup_messageQueue));
    group_consumerThread.detach();
    std::thread  UserMessage_consumerThread(UserMessage_consumer<UserMessage>, std::ref(UnreadUser_messageQueue));
    UserMessage_consumerThread.detach();


    EventLoop loop; //epoll
    InetAddress addr2("192.168.124.14", 9999);
    Server server2(&loop,addr2,"chatserver2");
    server2.start(); //启动服务：listenfd通过epoll_ctl添加到epoll上    loop.loop(); //类似于epoll_wait以阻塞的方式等待新用户连接或处理已连接用户的读写事件
    loop.loop();
    //接上面一段
    return 0;
}
