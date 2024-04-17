#ifndef CREATGROUPSERVICE_H_
#define CREATGROUPSERVICE_H_
#include"gloab/gloabal.h"
#include"model/UserModel.h"
#include"service/service.h"
using namespace muduo;
using namespace muduo::net;
class CreatGroupService:public service
{//还没测试
private:
    /* data */
public:
    CreatGroupService(/* args */);
    ~CreatGroupService();
    void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const;
};

#endif