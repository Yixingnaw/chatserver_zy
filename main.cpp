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
#include"service/LoginService.h"
#include"service/RegistService.h"
#include"service/service.h"
int main()
{
       muduo::Logger::setLogLevel(muduo::Logger::DEBUG);

      auto sql=db_connector(my_pool);//不写上会链接不上为啥
      
       User ass("3,","23","2312",2);
       User awww= UserModel().query(1);
     // gloabal_users.push_back(awww);
 
     
   /*  for(int i=10;i<30;i++){
     GroupMember test_groupmember(7,i);
     GroupMember test_groupmember2(8,i);
      GroupModel().add_group(test_groupmember2) ; 
     GroupModel().add_group(test_groupmember) ; }*/
 
      //这下面这一段必须先用来写上，不然会报链接错误，找不到muduonet库
    FriendshipModel().query_friendship(ass);
    GroupModel().query_group(ass);
    EventLoop loop; //epoll
    InetAddress addr2("192.168.124.14", 9999);
    Server server2(&loop,addr2,"chatserver2");
    server2.start(); //启动服务：listenfd通过epoll_ctl添加到epoll上
    loop.loop(); //类似于epoll_wait以阻塞的方式等待新用户连接或处理已连接用户的读写事件
    //接上面一段
    
    return 0;
}
