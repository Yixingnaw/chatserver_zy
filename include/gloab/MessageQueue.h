#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include "muduo/base/Logging.h"
#include"model/UnreadGroupMessageModel.h"
#include"model/UnreadUserMessageModel.h"
#include"model/UserMessageModel.h"
#include<vector>
#include<algorithm>

template <typename T>
class MessageQueue {
public:
    MessageQueue() : isRunning(true) {}
     
    void push(const T& message) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(message);
        // 每更新二十条数据,通知等待中的消费者线程
        if(queue_.size()>500){
        condition_.notify_one();
        }else{
            return;
        }

    }

    bool pop(std::vector<T> & message) {
        std::unique_lock<std::mutex> lock(mutex_);
        // 消费者函数或定时器唤醒之后，检查消息队列是否为空
            condition_.wait(lock,[this](){
                                                          // LOG_DEBUG<<"消息队列被唤醒";
                 return (!queue_.empty())||(!isRunning);
            });
       //非空
        if (!queue_.empty()) {
           while (!queue_.empty())
           {
               message.push_back(queue_.front());
               queue_.pop();
                                                           //LOG_DEBUG<<"数据库开始异步存入";          
            }
            return true; 
        }
        //停止信号
        LOG_ERROR<<"消息队列停止了";
        return false;
    }

    void stop() {
        isRunning = false;
        condition_.notify_all(); // 唤醒所有等待中的消费者线程
    }
    void startTimer(){
      time_.startTimer(condition_,mutex_);
    }
private:
class Timer {
public:
    Timer() : shouldStop(false) {}

    // 启动定时器线程
    void startTimer(std::condition_variable& condVar, std::mutex& mtx) {
        std::thread timerThread([this, &condVar, &mtx]() {
            while (!shouldStop) {
                // 等待 20 秒
                std::this_thread::sleep_for(std::chrono::seconds(10));

                // 使用互斥锁锁定条件变量
                std::unique_lock<std::mutex> lock(mtx);

                // 唤醒条件变量
                condVar.notify_one();
                                                                      //  LOG_DEBUG<<"定时器已经唤醒";
            }
        });

        timerThread.detach(); // 在后台运行定时器线程
    }

    // 停止定时器
    void stopTimer() {
        shouldStop = true;
    }

private:
    bool shouldStop;
};

private:
    bool isRunning;
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
     Timer time_;
};

// 生产者线程函数，插入消息队列
template<typename T>
void producer(MessageQueue<T>& mq,const T &data) {
    mq.push(data);
    LOG_DEBUG<<"有数据来了";
}

// 消费者线程函数，执行数据库插入
template<typename T>
void  UnreadGroupMessage_consumer(MessageQueue<T>& mq) 
{
    mq.startTimer();//启动定时器线程，每隔一定时间唤醒消息队列。
    std::vector<UnreadGroupMessage> message;
    while (mq.pop(message)) {
        UnreadGroupMessageModel model_;
          for(auto& x:message){
            model_.insert(x);
          }
          message.clear();
    }
}
template<typename T>
void  UserMessage_consumer(MessageQueue<T>& mq) 
{
    mq.startTimer();//启动定时器线程，每隔一定时间唤醒消息队列。
    std::vector<UserMessage> message;
    while (mq.pop(message)) {
      UserMessageModel usermessage_model;
      UnreadUserMessageModel unreadUserMessage_model;
          for(auto& x:message){
            usermessage_model.insert(x);
             UnreadUserMessage friend_unreadusemessage(x.getReceiverID(),x.getMessageID());
             unreadUserMessage_model.insert(friend_unreadusemessage);
                                         //   LOG_DEBUG<<"开始插入第"<<message.size()<<"条";
          }
          message.clear();
    }
}
extern   MessageQueue<UnreadGroupMessage> UnreadGroup_messageQueue;//消息队列
extern   MessageQueue<UserMessage>      UnreadUser_messageQueue;

