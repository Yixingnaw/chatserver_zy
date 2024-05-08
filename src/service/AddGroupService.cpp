#include"service/AddGroupService.h"
#include"model/GroupModel.h"
AddGroupService::AddGroupService(/* args */)
{
}

AddGroupService::~AddGroupService()
{
}
/*
{
     "msg_id":
     "msg_vlaue":{
         "Role":
         "JoinTime":
         "GroupID":
         "UserID":
     }   
     注意role和jointime格式
}
*/
void AddGroupService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
        GroupMember groupmember_;
        groupmember_.setRole(js["Role"].asString());
        groupmember_.setJoinTime(js["JoinTime"].asString());
        groupmember_.setGroupID(js["GroupID"].asInt());
        groupmember_.setUserID(js["UserID"].asInt());
        GroupModel().add_group(groupmember_);
         //需要根据返回值判断是否加入成功！！！！！！！！！！！！1
           Json::Value ack;
          ack["msg_id"]=static_cast<int>(ServerMessage::ADD_GROUP_MSG_ACK);
          Json::Value msg_value;
          msg_value["value"]=std::string("加群成功");
          ack["msg_value"]=msg_value;
          Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack);   
         conn->send(muduo::StringPiece(jsonString));
        //其实还需要在ui界面上更新显示出来加入的群，待定，
        //qt可以这么实现，调用update(),触发绘制事件
          return;
}

/*
{
  "msg_id":
  "msg_value":{
    "value":
    “”：
  }
}
*/
