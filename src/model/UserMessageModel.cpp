#include"model/UserMessageModel.h"
#include"gloab/gloabal.h"
using namespace std;
bool UserMessageModel::insert(UserMessage &usermessage){

 try {
         auto sql=db_connector(my_pool);
          cppdb::statement stat;
               stat = sql << 
                        "INSERT INTO UserMessage(Content,SendTime,SenderID,ReceiverID) "
                        "VALUES(?,?,?,?)"
                        << usermessage.getContent()<< usermessage.getDate() << usermessage.getSenderID()<<usermessage.getReceiverID();
                stat.exec();
                usermessage.setUserMessageID(stat.last_insert_id());

               return true;              

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
       return false;
        }
        return false;
}


   //根据ID查询之后返回UserMessage数据
 UserMessage UserMessageModel::query(int UserMessageid){
   
      try {
         auto sql=db_connector(my_pool);
          cppdb::result res;
          res=sql << "SELECT * FROM UserMessage WHERE UserMessageID=?" << UserMessageid << cppdb::row;
          if(!res.empty()) {
             UserMessage userMessage;
                        userMessage.setUserMessageID(res.get<int>(0));
                        userMessage.setContent(res.get<string>(1));
                        userMessage.setDate(res.get<string>(2));
                        userMessage.setSenderID(res.get<int>(3));
                         userMessage.setReceiverID(res.get<int>(4));
              return userMessage;
           }
        else return UserMessage();               

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return UserMessage();
              }


 }
  //查询之后删除
bool UserMessageModel::delete_UserMessage(int UserMessageid){
    //组装SQL语句
       try {
         auto sql=db_connector(my_pool);
          sql << "DELETE FROM UserMessage WHERE UserMessageID =?" << UserMessageid<<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
        }
        return false;

}