#include <iostream>
#include "model/UserModel.h"

#include"gloab/gloabal.h"
using namespace std;

//增加User
bool UserModel::insert(User &user)
{

      try {
         auto sql=db_connector(my_pool);
          cppdb::statement stat;
               stat = sql << 
                        "INSERT INTO User(Password,Username,PersonalSignature) "
                        "VALUES(?,?,?)"
                        << user.getPassword()<< user.getUsername() << user.getPersonalSignature() ;
                stat.exec();
                user.setId(stat.last_insert_id());

               return true;              

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
       return false;
        }
        return false;
}

//根据ID查询user信息，失败返回一个默认构造User，id = -1
User UserModel::query(int id)
{
    
      try {
         auto sql=db_connector(my_pool);
          cppdb::result res;
          res=sql << "SELECT * FROM User WHERE UserID=?" << id << cppdb::row;
          if(!res.empty()) {
             User user;
                        user.setId(res.get<int>(0));
                        user.setPassword(res.get<string>(1));
                        user.setUsername(res.get<string>(2));
                        user.setPersonalSignature(res.get<string>(3));
                         user.setState(res.get<int>(4));//数据库是bool类型这里用int获取bool类型然后再改成bool类型不知道会不会有bug
              return user;
           }
        else return User();               

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return User();
              }

}

//更新状态操作
bool UserModel::update_state(User user)
{

      try {
         auto sql=db_connector(my_pool);
          sql << "update  User set State=? where UserID=?" << user.getState() << user.getId() <<cppdb::exec;
          return true;

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return false;
        }
        return false;
}

//重置服务器所有用户状态信息,
bool UserModel::reset_state()
{
     //组装SQL语句
       try {
         auto sql=db_connector(my_pool);
          sql << "update  User set State=? where State=?" << 0 << 1 <<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
        }
        return false;
}


bool   UserModel::is_hava_user(User user){

          try {
         auto sql=db_connector(my_pool);
          cppdb::result res;
          res=sql << "SELECT * FROM User WHERE UserID=? AND Password=?" << user.getId()<<user.getPassword() << cppdb::row;
          if(!res.empty()) {
               return true;
           }
        else return false;         

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return false;
              }
}