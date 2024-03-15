#ifndef GROUP_H
#define GROUP_H

#include <string>

class Group {
private:
   
    std::string GroupName;
    std::string Description;
     int GroupID;
public:
    // 构造函数
    inline Group(const std::string& groupName, const std::string& description,int id=1)
        : GroupName(groupName), Description(description),GroupID(id){}
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
