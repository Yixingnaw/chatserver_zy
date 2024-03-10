#ifndef GROUP_H
#define GROUP_H

#include <string>

class Group {
private:
    int GroupID;
    std::string GroupName;
    std::string Description;

public:
    // 构造函数
    inline Group(int id, const std::string& groupName, const std::string& description)
        : GroupID(id), GroupName(groupName), Description(description) {}
    Group(){
        GroupID=-1;
    }
    // 获取群组ID
    inline int getGroupID() const { return GroupID; }

     void setGroupID(int id){
        GroupID=id;
     }     

    // 获取群组名称
    inline const std::string& getGroupName() const { return GroupName; }

    // 获取群组描述
    inline const std::string& getDescription() const { return Description; }

    // 设置群组名称
    inline void setGroupName(const std::string& groupName) { GroupName = groupName; }

    // 设置群组描述
    inline void setDescription(const std::string& description) { Description = description; }

    
      bool operator<(const Group&x) const{
        return GroupID<x.GroupID;
      }
};

#endif
