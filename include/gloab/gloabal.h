#ifndef GLOABAL___H_
#define GLOABAL___H_
#include"cppdb/backend.h"
#include"cppdb/connection_specific.h"
#include"cppdb/conn_manager.h"
#include"cppdb/defs.h"
#include"cppdb/driver_manager.h"
#include"cppdb/errors.h"
#include"cppdb/frontend.h"
#include"cppdb/numeric_util.h"
#include"cppdb/pool.h"
#include"cppdb/ref_ptr.h"
#include"cppdb/shared_object.h"
#include"cppdb/utils.h"
#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "muduo/net/TcpServer.h" 
#include"json/json.h"
#include"model/User.h"
#include <iostream>
#include <vector>
#include <thread>
#include <shared_mutex>
#include <map>
#include<unordered_map>
/*用来注册不同的回调函数*/
enum class ServerMessage{
    LOGIN_MSG = 1,  //登录消息，绑定login
    LOGIN_MSG_ACK,  //登录响应消息
    REG_MSG,        //注册消息，绑定regist
    REG_MSG_ACK,    //注册响应消息
    ONE_CHAT_MSG,   //一对一聊天消息
    ONE_CHAT_MSG_ACK, //一对一聊天消息响应
    ADD_FRIEND_MSG, //添加好友消息
    CREATE_GROUP_MSG, //创建群聊
    ADD_GROUP_MSG,    //加入群聊
    GROUP_CHAT_MSG,   //群聊消息
    LOGINOUT_MSG,   //注销消息
    
};
cppdb::session db_connector(cppdb::pool::pointer&);


template<typename Key, typename Value>
class ThreadSafeMap {
private:
    std::unordered_map<Key,Value>map;
    mutable std::shared_mutex mutex; // 读写锁

public:
    void insert(const Key& key, const Value& value) {
        std::unique_lock<std::shared_mutex> lock(mutex); // 写锁
        map[key] = value;
    }

    typename std::unordered_map<Key, Value>::const_iterator get(const Key& key) const {
        std::shared_lock<std::shared_mutex> lock(mutex); // 读锁
        return map.find(key);
    }

    bool contains(const Key& key) const {
        std::shared_lock<std::shared_mutex> lock(mutex); // 读锁
        return map.find(key) != map.end();
    }

    void remove(const Key& key) {
        std::unique_lock<std::shared_mutex> lock(mutex); // 写锁
        map.erase(key);
    }
};

template<typename T>
class ThreadSafeVector {
private:
    std::vector<T> vec;
    mutable std::shared_mutex mtx; // 读写锁

public:
    void push_back(const T& value) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        vec.push_back(value);
    }

    T at(size_t index) const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return vec.at(index);
    }

    size_t size() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return vec.size();
    }

    bool empty() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return vec.empty();
    }

    T front() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return vec.front();
    }

    T back() const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return vec.back();
    }

    bool pop_back() {
        std::unique_lock<std::shared_mutex> lock(mtx);
        if (vec.empty()) {
            return false;
        }
        vec.pop_back();
        return true;
    }

    T operator[](size_t index) const {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return vec[index];
    }

    bool erase(size_t index) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        if (index < 0 || index >= vec.size()) {
            return false;
        }
        vec.erase(vec.begin() + index);
        return true;
    }

    void clear() {
        std::unique_lock<std::shared_mutex> lock(mtx);
        vec.clear();
    }
    bool find(const T& value){
      std::unique_lock<std::shared_mutex> lock(mtx);
      auto it=  std::find(vec.begin(),vec.end(),value);
      if (it != vec.end()) {
             return true;          
        }   
       else {
         return false;
     }
    }
};

extern   cppdb::pool::pointer my_pool;
extern   ThreadSafeVector<int> gloabal_users;//服务器在线列表
extern   ThreadSafeMap<int,muduo::net::TcpConnectionPtr> user_connection_map;

#endif