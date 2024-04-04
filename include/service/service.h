#ifndef SERVICE__H_
#define SERVICE__H_
#include"gloab/gloabal.h"
using namespace muduo;
using namespace muduo::net;
class service
{
private:
    /* data */
public:
   virtual ~service();
    virtual void operator()(const TcpConnectionPtr &conn, Json::Value &js, Timestamp time)const=0;
};



#endif