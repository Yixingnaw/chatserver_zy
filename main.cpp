
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
#include"model/FriendshipModel.h"

int main(int argc,char **argv)
{
       // 设置日志级别为TRACE 
  muduo::Logger::setLogLevel(muduo::Logger::DEBUG);

 
      auto sql=db_connector(my_pool);//不写上会链接不上为啥
     User ass("3,","23","2312",2);
       UserModel().insert(ass);
      User awww= UserModel().query(1);
      awww.setState(true);
      UserModel().update_state(awww);
      UserModel().reset_state();


      //UserMessageModel().delete_UserMessage(1);
       Json::Value a;
       a["woain"]="dasdas";   
      std::cout<<woaini111()<<std::endl; 
      
      Group  test_group("1112321","222",3);
      GroupModel().create_group(test_group);
   //  GroupModel().delele_group(test_group); 
     Group  test_group1("1112321","222",4);
     GroupModel().update_group(test_group1); 
   /*  for(int i=10;i<30;i++){
     GroupMember test_groupmember(7,i);
     GroupMember test_groupmember2(8,i);
      GroupModel().add_group(test_groupmember2) ; 
     GroupModel().add_group(test_groupmember) ; }*/
    std::map<Group,std::vector<GroupMember>>  ashddas;
   User assss("2","2","3",10);
    ashddas= GroupModel().query_group(assss);
        
     std::cout<<"test"<<std::endl;
     Friendship test_friendship("我是你爹",7,3);
    if(!FriendshipModel().add_friendship(test_friendship)){
      std::cout<<"已经是好友了"<<std::endl;
    }
     FriendshipModel().delete_freindship(test_friendship);
     User   asassssa("2.","3","4",5);
    auto  data=   FriendshipModel().query_friendship(asassssa);

     //记住这一定是操作数据库usermessage的顺序
      UserMessage test_message("你是啥比","2000-10-05",ass.getId(),ass.getId(),1);
      UserMessageModel().insert(test_message);
     std::vector< UserMessage>  vec_test_message2=   UserMessageModel().query({1});
    UnreadUserMessage testunreadusemessage(ass.getId(),test_message.getMessageID());
    UnreadUserMessageModel().insert(testunreadusemessage);
      auto vec__back__int=  UnreadUserMessageModel().query(ass.getId());
      UnreadUserMessageModel().delete_UnreadUserMessage(ass.getId());



    std::cout<<"test";

    
	return 0;
}
