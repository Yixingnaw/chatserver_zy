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
    
    
int main()
{
       muduo::Logger::setLogLevel(muduo::Logger::DEBUG);

 
      auto sql=db_connector(my_pool);//不写上会链接不上为啥

    
    User ass("3,","23","2312",2);
       UserModel().insert(ass);
      User awww= UserModel().query(1);
      User ashda=UserModel().query(1);
      gloabal_users.push_back(awww);
     if(gloabal_users.find(awww))std::cout<<"成功找到"<<std::endl;
      if(awww==ashda){std::cout<<"wiaubu"<<std::endl;}
      std::cout<<static_cast<int>(UserModel().is_hava_user(awww))<<std::endl;
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

     //记住这一定是操作数据库usermessage的顺序using namespace placeholders;
      UserMessage test_message("你是啥比","2000-10-05",ass.getId(),ass.getId(),1);
      UserMessageModel().insert(test_message);
     std::vector< UserMessage>  vec_test_message2=   UserMessageModel().query({1});
    UnreadUserMessage testunreadusemessage(ass.getId(),test_message.getMessageID());
    UnreadUserMessageModel().insert(testunreadusemessage);
      auto vec__back__int=  UnreadUserMessageModel().query(ass.getId());
      UnreadUserMessageModel().delete_UnreadUserMessage(ass.getId());
    std::cout<<"test"<<std::endl;
    RegistService();
/* json数组操作
    Json::Value js_value;
    js_value["woaini"]="woaini";
    js_value["wohenni"]="wohenni";
  Json::Value js_value1;
  js_value1["js_value"]=js_value;
    Json::StreamWriterBuilder writerBuilder;
    std::string jsonStr = Json::writeString(writerBuilder, js_value1);
    std::cout << jsonStr << std::endl;
*/

      //这下面这一段必须先用来写上，不然会报链接错误，找不到muduonet库
    EventLoop loop; //epoll
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");
    server.start(); //启动服务：listenfd通过epoll_ctl添加到epoll上
    loop.loop(); //类似于epoll_wait以阻塞的方式等待新用户连接或处理已连接用户的读写事件
    //接上面一段

    
    return 0;
}
