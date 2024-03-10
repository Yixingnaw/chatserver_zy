#ifndef GROUPMEMBER_H
#define GROUPMEMBER_H

#include <string>

class GroupMember {
private:
   
    int GroupID;
    int UserID;
     std::string Role;//注意数据库里面这个是enum！！
    std::string JoinTime;

public:
    // 构造函数
    inline GroupMember(int groupID, int userID,const std::string& role="Member", const std::string& joinTime="1999-08-01")
        : GroupID(groupID), UserID(userID) ,Role(role), JoinTime(joinTime){}
      GroupMember(){

      }
    // 获取角色
    inline const std::string& getRole() const { return Role; }

    // 获取加入时间
    inline const std::string& getJoinTime() const { return JoinTime; }

    // 获取群组ID
    inline int getGroupID() const { return GroupID; }

    // 获取用户ID
    inline int getUserID() const { return UserID; }

    // 设置角色
    inline void setRole(const std::string& role) { Role = role; }

    // 设置加入时间
    inline void setJoinTime(const std::string& joinTime) { JoinTime = joinTime; }

    // 设置群组ID
    inline void setGroupID(int groupID) { GroupID = groupID; }

    // 设置用户ID
    inline void setUserID(int userID) { UserID = userID; }
};

#endif
