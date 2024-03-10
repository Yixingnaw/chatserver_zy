
#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "muduo/net/TcpServer.h" 
#include"gloab/gloabal.h"
#include"gloab/server.h"
#include"model/User.h"
#include"iostream"
#include"json/json.h"
#include"model/UserModel.h"
#include"model/UserMessageModel.h"
#include"model/UnreadUserMessageModel.h"
#include"model/GroupModel.h"
int main(int argc,char **argv)
{
       // 设置日志级别为TRACE 
  muduo::Logger::setLogLevel(muduo::Logger::TRACE);
 
      auto sql=db_connector(my_pool);//不写上会链接不上为啥
       User ass(1,"2","2","3");
       UserModel().insert(ass);
      User awww= UserModel().query(1);
      awww.setState(true);
      UserModel().update_state(awww);
      UserModel().reset_state();


      UserMessage test_message(1,"你是啥比","2000-10-05",awww.getId(),awww.getId());
      UserMessageModel().insert(test_message);
      UserMessage test_message2=   UserMessageModel().query(1);
      //UserMessageModel().delete_UserMessage(1);
       Json::Value a;
       a["woain"]="dasdas";   
      std::cout<<woaini111()<<std::endl; 
      
      Group  test_group(3,"1112321","222");
      GroupModel().create_group(test_group);
   //  GroupModel().delele_group(test_group); 
     Group  test_group1(4,"1112321","222");
     GroupModel().update_group(test_group1); 
   /*  for(int i=10;i<30;i++){
     GroupMember test_groupmember(7,i);
     GroupMember test_groupmember2(8,i);
      GroupModel().add_group(test_groupmember2) ; 
     GroupModel().add_group(test_groupmember) ; }*/
 
     
    std::map<Group,std::vector<GroupMember>>  ashddas;
   User assss(10,"2","2","3");
    ashddas= GroupModel().query_group(assss);

	return 0;
}
