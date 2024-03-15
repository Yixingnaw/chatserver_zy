#include"model/FriendshipModel.h"

using namespace std;
  //增加
    bool FriendshipModel::add_friendship(Friendship& x){
           try {
         auto sql=db_connector(my_pool);
       //需要首先检查是不是好友关系
         cppdb::result res;
         res= sql<<"SELECT * FROM Friendship WHERE (UserID = ? AND FriendID = ?) OR (UserID = ? AND FriendID = ?)"
           <<x.getFriendID()<<x.getUserID()<<x.getUserID()<<x.getFriendID()<<cppdb::row;
           if(res.empty()){
                cppdb::statement stat;
               stat = sql << 
                        "INSERT INTO Friendship(FriendRemark,UserID,FriendID) "
                        "VALUES(?,?,?)"
                        << x.getFriendRemark()<< x.getUserID() <<x.getFriendID()  ;
                stat.exec();
               return true;     
           } 
          else  return false;//好友表存在

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
       return false;
        }
        return false;


    }
    //删除
    bool FriendshipModel::delete_freindship(Friendship& x){
              try {
         auto sql=db_connector(my_pool);
  
          sql << "DELETE  FROM Friendship WHERE (UserID = ? AND FriendID = ?) OR (UserID = ? AND FriendID = ?)"
         <<x.getFriendID()<<x.getUserID()<<x.getUserID()<<x.getFriendID()<<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
        }
        return false;


    }
    //查询所有用户好友
    std::vector<User> FriendshipModel::query_friendship(User& x){
   
        try {
         auto sql=db_connector(my_pool);
          std::vector<User>vec_user;
          cppdb::result res;
          //连表查询
          std::string sqldata= std::string("SELECT User.* FROM Friendship ")+
          "JOIN User ON (User.UserID = Friendship.FriendID OR User.UserID = Friendship.UserID)"+
          "WHERE (Friendship.UserID=? OR Friendship.FriendID= ?) AND User.UserID != ?";
          res=sql << sqldata<< x.getId()<<x.getId() << x.getId() ;
          while(res.next()) {
             User user;
                        user.setId(res.get<int>(0));
                        user.setPassword(res.get<string>(1));
                        user.setUsername(res.get<string>(2));
                        user.setPersonalSignature(res.get<string>(3));
                         user.setState(res.get<int>(4));
            vec_user.push_back(user);
           }
          return vec_user;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
              
              }
    }