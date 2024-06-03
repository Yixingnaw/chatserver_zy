#include"model/UnreadGroupMessageModel.h"
#include"gloab/gloabal.h"
using namespace std;
UnreadGroupMessageModel::UnreadGroupMessageModel(/* args */)
{
}

UnreadGroupMessageModel::~UnreadGroupMessageModel()
{
     
}
bool UnreadGroupMessageModel::insert(UnreadGroupMessage &grouomessage){
      try {
         auto sql=db_connector(my_pool);
          cppdb::statement stat;
               stat = sql << 
                        "INSERT INTO UnreadGroupMessage(Content,SendTime,SenderID,GroupID) "
                        "VALUES(?,?,?,?)"
                        << grouomessage.getContent()<< grouomessage.getSendTime()<< grouomessage.getSenderID()<<grouomessage.getGroupID();
                stat.exec();
                 grouomessage.setUnreadGroupMessageID(stat.last_insert_id());
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
//限定返回一百条群消息。
std::vector<UnreadGroupMessage> UnreadGroupMessageModel::query(int groupid,int history_number){
  
     vector<UnreadGroupMessage>vec_;
       try {
         auto sql=db_connector(my_pool);    
          cppdb::result res;
          res=sql << "SELECT * FROM UnreadGroupMessage WHERE GroupID=? ORDER BY UnreadGroupMessageID DESC LIMIT 100 OFFSET ?" << groupid <<history_number;
          
          while(res.next()) {
                UnreadGroupMessage groupMessage;
                groupMessage.setUnreadGroupMessageID(res.get<int>(0));
                groupMessage.setContent(res.get<string>(1));
                groupMessage.setSendTime(res.get<string>(2));
                groupMessage.setSenderID(res.get<int>(3));
                groupMessage.setGroupID(groupid);
              vec_.push_back(groupMessage);
         }   
         return vec_;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                return std::vector<UnreadGroupMessage>{};
        }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return std::vector<UnreadGroupMessage>{};
    }

}

bool UnreadGroupMessageModel::delete_UserMessage(int groupid){
    
}