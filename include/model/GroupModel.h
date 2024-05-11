#ifndef GROUPMODEL_H
#define GROUPMODEL_H
#include"model/Group.h"
#include"model/GroupMember.h"
#include"model/User.h"
#include<vector>
#include<map>
class GroupModel{
    /*这个类管理两张表*/
    public:
   bool  create_group(Group &);//创建群
   bool  delele_group(Group &);//注意需要先把从表删除
   bool  update_group(Group &); //更改群信息
   bool  add_group(GroupMember &);//加入群
   bool  out_group(GroupMember &);//退出群
   std::map<Group,std::vector<GroupMember>> query_group(User&);//初次登陆时候返回用户所有群以及群里面对应的所有用户
   std::vector<int> query_gropumembers(int groupid);
};
#endif