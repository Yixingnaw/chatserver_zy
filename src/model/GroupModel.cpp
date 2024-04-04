#include"model/GroupModel.h"
#include<iostream>
#include"gloab/gloabal.h"
using namespace std;

bool  GroupModel::create_group(Group &x){
     //注意创建群表之后还必须要操作从表
     try {
         auto sql=db_connector(my_pool);
           cppdb::statement stat;
               stat = sql << 
                        "INSERT INTO `Group`(GroupName,Description) "//说多了都是泪！！注意表名插入反引号！！
                        "VALUES(?,?)"
                        << x.getGroupName()<< x.getDescription() ;
                stat.exec();
                
               return true;              

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
       return false;
        }
        return false;
}
bool  GroupModel::delele_group(Group &x){
          try {
         auto sql=db_connector(my_pool);
           // 首先删除与主表相关的从表数据
    sql << "DELETE FROM GroupMember WHERE GroupID = ?" << x.getGroupID()<< cppdb::exec;
         //再删除主表数据
    sql << "DELETE FROM `Group` WHERE GroupID =?" << x.getGroupID()<<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
        }
        return false;
   }
bool  GroupModel::update_group(Group &x){
      try {
         auto sql=db_connector(my_pool);
          sql << "update  `Group` set GroupName=? ,Description=? where GroupID=?" << x.getGroupName() << x.getDescription() <<x.getGroupID() <<cppdb::exec;
          return true;

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return false;
        }
        return false;
}

bool  GroupModel::add_group(GroupMember &x){
     try {
         auto sql=db_connector(my_pool);
          cppdb::statement stat;
               stat = sql << 
                        "INSERT INTO GroupMember(Role,JoinTime,GroupID,UserID) "
                        "VALUES(?,?,?,?)"
                        << x.getRole() << x.getJoinTime() <<x.getGroupID() <<x.getUserID();
                stat.exec();
                x.setGroupID(stat.last_insert_id());

               return true;              

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
       return false;
        }
        return false;
         
}

bool  GroupModel::out_group(GroupMember & x){
     try {
         auto sql=db_connector(my_pool);
          sql << "DELETE FROM GroupMember WHERE UserID =? " << x.getUserID()<<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
        }
        return false;

}
   //初次登陆时候返回用户所有群以及群里面对应的所有用户
std::map<Group,std::vector<GroupMember>> GroupModel::query_group(User& user){

     std::map<Group,std::vector<GroupMember>> map_;
        try {
         auto sql=db_connector(my_pool);
     std::vector<Group> vec_;
          cppdb::result res;
          //连表查询，查寻group表里面
          res=sql << "SELECT `Group`.* FROM `Group`  JOIN GroupMember ON `Group`.GroupID = GroupMember.GroupID WHERE GroupMember.UserID=?" 
          <<  user.getId() ;
          while(res.next()) {
             Group group;
                        group.setGroupID(res.get<int>(0));
                        group.setGroupName(res.get<string>(1));
                        group.setDescription(res.get<string>(2));
            vec_.push_back(group);
           }
           for(const auto &group_x:vec_){
               res.clear();
               std::vector<GroupMember> groupmenber_vec;
               res=sql << "SELECT * FROM GroupMember WHERE GroupID=?" << group_x.getGroupID();
               while(res.next()){
                    GroupMember groupmember;
                        groupmember.setRole(res.get<string>(0));
                        groupmember.setJoinTime(res.get<string>(1));
                        groupmember.setGroupID(res.get<int>(2));
                        groupmember.setUserID(res.get<int>(3));
                        groupmenber_vec.push_back(groupmember);
                    }
               map_.emplace(group_x,groupmenber_vec);
           }
             return map_;               

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
              return map_;
              }


}