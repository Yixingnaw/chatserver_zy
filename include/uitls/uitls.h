#pragma once
#include <muduo/base/Logging.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Timestamp.h>
namespace uitls
{

  void asyncOutput(const char* msg, int len);//
};
extern muduo::AsyncLogging asyncLog;
