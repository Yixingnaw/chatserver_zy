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
      catch (...) {
        LOG_ERROR << "Unknown error in ";
        return false;
    }
}


   //根据ID查询之后返回UserMessage数据
 std::vector<UserMessage> UserMessageModel::query(std::vector<int> UserMessageid){
   
      std::vector<UserMessage> vec_;
      try {
         auto sql=db_connector(my_pool);
         for(auto x:UserMessageid){
           //  LOG_DEBUG<<"vector 不是空的";
          cppdb::result res;
          res=sql << "SELECT * FROM UserMessage WHERE UserMessageID=?" << x ;
          while(res.next()) {
        //        LOG_DEBUG<<"数据库不是空的";
             UserMessage userMessage;
                        userMessage.setUserMessageID(res.get<int>(0));
                        userMessage.setContent(res.get<string>(1));
                        userMessage.setDate(res.get<string>(2));
                        userMessage.setSenderID(res.get<int>(3));
                         userMessage.setReceiverID(res.get<int>(4));
              vec_.push_back(userMessage);
            
           }
         }
    //      LOG_DEBUG<<"数据库查询函数返回";
          return vec_;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return std::vector<UserMessage>{};
       }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return std::vector<UserMessage>{};
    }


 }
  //查询之后根据user删除
bool UserMessageModel::delete_UserMessage(int Userid){
    //组装SQL语句
       try {
         auto sql=db_connector(my_pool);
          sql << "DELETE FROM UserMessage WHERE ReceiverID =?" << Userid<<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                 return false;
        }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return false;
    }
       
}