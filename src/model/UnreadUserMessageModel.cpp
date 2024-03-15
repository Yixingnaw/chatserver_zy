#include"model/UnreadUserMessageModel.h"
#include<iostream>
#include"gloab/gloabal.h"
using namespace std;
bool UnreadUserMessageModel::insert(UnreadUserMessage &unreadUsermessage){
     try {
         auto sql=db_connector(my_pool);
          cppdb::statement stat;
               stat = sql << 
                        "INSERT INTO UnreadUserMessage(ReceiverID,UserMessageID) "
                        "VALUES(?,?)"
                        << unreadUsermessage.getReceiverID()<< unreadUsermessage.getUserMessageID();
                stat.exec();
                unreadUsermessage.setUserMessageID(stat.last_insert_id());

               return true;              
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
       return false;
        }
        return false;
}
    
      //根据ID查询,返回所以UnreadUserMessageID主键
std::vector<int> UnreadUserMessageModel::query(int userid){
            std::vector<int> vec_;
      try {
         auto sql=db_connector(my_pool);    
          cppdb::result res;
          res=sql << "SELECT * FROM UnreadUserMessage WHERE ReceiverID=?" << userid ;
          while(res.next()) {
                               int xxx=   res.get<int>(0);
              vec_.push_back(xxx);
          
           return vec_;
         }
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
               
              }


}


    //根据id查询之后，删除数据
bool UnreadUserMessageModel::delete_UnreadUserMessage(int userid){
       try {
         auto sql=db_connector(my_pool);
          sql << "DELETE FROM UnreadUserMessage WHERE ReceiverID =?" << userid<<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
        }
        return false;
}
     