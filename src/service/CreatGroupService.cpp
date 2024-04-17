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
     }
}
*/
void CreatGroupService::operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const{
       Json::Value ack;
        ack["msg_id"]=static_cast<int>(ServerMessage::CREATE_GROUP_MSG_ACK);

       Group group_;
       group_.setGroupName(js["GroupName"].asString());
       group_.setDescription(js["Description"].asString());
       GroupModel().create_group(group_);
        
        Json::Value msg_value;
          msg_value["value"]=group_.getGroupID();
         ack["msg_value"]=msg_value;
             Json::FastWriter fastWriter;
         std::string jsonString = fastWriter.write(ack); 
          conn->send(muduo::StringPiece(jsonString));
              return;

}
/*
{
    "msg_id":
     "msg_vlaue":{
        "GroupID":
     }
}
*/
