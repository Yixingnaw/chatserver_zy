#pragma once
#include <muduo/base/Logging.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Timestamp.h>
namespace  chatserver_uitls
{
  void asyncOutput(const char* msg, int len);//
  uint64_t htonll(uint64_t host64); //转化为网络字节序
};
extern muduo::AsyncLogging asyncLog;
