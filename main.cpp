
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
int main(int argc,char **argv)
{
       // 设置日志级别为TRACE 
  muduo::Logger::setLogLevel(muduo::Logger::TRACE);
  // 配置日志文件名、文件路径、日志滚动方式等选项
  // 记录不同级别的日志信息
  LOG_TRACE << "trace level log message";
  LOG_DEBUG << "debug level log message";
  LOG_INFO << "info level log message";
  LOG_WARN << "warn level log message";
  LOG_ERROR << "error level log message";
<<<<<<< HEAD


=======
     int x;
<<<<<<< HEAD
     int xxxx;
=======
>>>>>>> dba3ffc3017ca7eee21ff4579804ca25a6d7a5e8
>>>>>>> 976e2139cc253890da8358e93cd68469c62fae3c
       User ass(1,"2","2","3");
       UserModel().insert(ass);
      User awww= UserModel().query(1);
      awww.setState(true);
      UserModel().update_state(awww);
      UserModel().reset_state();


      UserMessage test_message(1,"你是啥比","2000-10-05",awww.getId(),awww.getId());
      UserMessageModel().insert(test_message);
      UserMessage test_message2=   UserMessageModel().query(1);
      UserMessageModel().delete_UserMessage(1);
       Json::Value a;
       a["woain"]="dasdas";   
      std::cout<<woaini111(); 
   auto sql=db_connector(my_pool);
	return 0;
}
