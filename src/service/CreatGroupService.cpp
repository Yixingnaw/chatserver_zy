#include"service/CreatGroupService.h"
#include"model/GroupModel.h"
CreatGroupService::CreatGroupService(/* args */)
{
}

CreatGroupService::~CreatGroupService()
{
}
/*
{
    "msg_id":
     "msg_vlaue":{
         "GroupName":
         "Description":
         "JoinTime":
         "UserID":
     }
}
*/
void CreatGroupService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
       Json::Value ack;
        ack["msg_id"]=static_cast<int>(ServerMessage::CREATE_GROUP_MSG_ACK);

       Group group_;
       group_.setGroupName(js["GroupName"].asString());
       group_.setDescription(js["Description"].asString());
      if(GroupModel().create_group(group_)){ 
        GroupMember groupmember_;
        groupmember_.setJoinTime(js["JoinTime"].asString());
        groupmember_.setUserID(js["UserID"].asInt());
        groupmember_.setRole("Owner");
        groupmember_.setGroupID(group_.getGroupID());
        GroupModel().add_group(groupmember_);
        Json::Value msg_value;
          msg_value["value"] = std::string("创建群组成功");
          msg_value["GroupID"]=group_.getGroupID();
         ack["msg_value"]=msg_value;
             Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
         message message_data(jsonString);
          conn->send(message_data.data(),message_data.size()); 
                                                                             LOG_DEBUG<<jsonString;
              return;
      }
      else{
          Json::Value msg_value;
          msg_value["value"] = std::string("创建群组失败");
         ack["msg_value"]=msg_value;
             Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
          message message_data(jsonString);
          conn->send(message_data.data(),message_data.size());
                                                                             LOG_DEBUG<<jsonString;
              return;
      }
}
/*
{
    "msg_id":
     "msg_vlaue":{
        "value":
        "GroupID":
     }
}
*/
