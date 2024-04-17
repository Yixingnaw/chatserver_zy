#ifndef ADDGROUPSERVICE_H_
#define ADDGROUPSERVICE_H_
#include"gloab/gloabal.h"
#include"model/UserModel.h"
#include"service/service.h"
using namespace muduo;
using namespace muduo::net;
class AddGroupService:public service
{
    //尚未测试
private:
    /* data */
public:
    AddGroupService(/* args */);
    ~AddGroupService();
    void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};


#endif