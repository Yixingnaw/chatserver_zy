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
                        << x.getGroupName()<< x.getDescription();
                stat.exec();
           // 检查插入操作是否成功
         if (stat.affected() > 0) {
          // 获取插入的记录的自增 ID
          x.setGroupID(stat.last_insert_id());
            return true;
      } else {
             LOG_ERROR << "Failed to insert record into Group table";
           return false;
          }           
 } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
       return false;
     }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return false;
     }
}
bool  GroupModel::delele_group(Group &x){
          try {
       auto sql=db_connector(my_pool);
       // 首先删除与主表相关的从表数据
        cppdb::result result1 = sql << "DELETE FROM GroupMember WHERE GroupID = ?" << x.getGroupID() << cppdb::exec;

        // 检查删除操作是否成功
    //      if (!result1.error()) {
       // 查询成功执行，继续执行下一条 SQL 查询

        // 再删除主表数据
          cppdb::result result2 = sql << "DELETE FROM `Group` WHERE GroupID = ?" << x.getGroupID() << cppdb::exec;

         // 检查删除操作是否成功
   //         if (!result2.error()) {
        // 查询成功执行
           return true;
    //     } else {
        // 删除主表数据失败，记录错误日志等
     //   LOG_ERROR << "Failed to delete record from Group table";
     //   return false;
    //}
   // } else {
    // 删除从表数据失败，记录错误日志等
   // LOG_ERROR << "Failed to delete records from GroupMember table";
   // return false;
    // }
} catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return false;
  }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return false;
     }

 }
bool  GroupModel::update_group(Group &x){
      try {
         auto sql=db_connector(my_pool);
        auto result= sql << "update  `Group` set GroupName=? ,Description=? where GroupID=?" << x.getGroupName() << x.getDescription() <<x.getGroupID() <<cppdb::exec;
          return true;
       //if (!result.error()) {
    // 更新操作成功
          return true;
    // } else {
    // 更新操作失败，记录错误日志等
      // LOG_ERROR << "Failed to update record in Group table";
       // return false;
       // }
            
      
} catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
                return false;
  }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return false;
     }
     
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
               return true;              

      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
       return false;
        }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return false;
     }
         
}

bool  GroupModel::out_group(GroupMember & x){
     try {
         auto sql=db_connector(my_pool);
          sql << "DELETE FROM GroupMember WHERE UserID =? " << x.getUserID()<<cppdb::exec;
           return true;
      } catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                 return false;
        }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return false;
    }

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
              return std::map<Group,std::vector<GroupMember>>{};
      }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return std::map<Group,std::vector<GroupMember>>{};
    }


}
std::vector<int> GroupModel::query_gropumembers(int groupid){
     std::vector<int> vec_;
         try {
         auto sql=db_connector(my_pool);
          cppdb::result res;
               res=sql << "SELECT * FROM GroupMember WHERE GroupID=?" << groupid;
               while(res.next()){                       
                        vec_.push_back(res.get<int>(3));
                    }
                return vec_;  
           }             
       catch(std::exception const &e) {
                LOG_ERROR<< "ERROR: " << e.what() ;
                //异常终止程序
              return std::vector<int>{};
      }catch (...) {
        LOG_ERROR << "Unknown error in ";
        return std::vector<int>{};
    }
}
