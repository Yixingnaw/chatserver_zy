#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include <string>
#include<vector>
class UserMessage {
private:
    std::string Content;
    std::string SendTime;
    int SenderID;
    int ReceiverID;
        int UserMessageID;
   // bool IsRead;
public:
    // 构造函数
    UserMessage(const std::string& content, const std::string& date="1999-08-05",
                int senderID=0, int receiverID=0,int id=1)
        : Content(content), SendTime(date),
         SenderID(senderID), ReceiverID(receiverID) ,UserMessageID(id) {}
     UserMessage(){
        UserMessageID=-1;
     }
    // 获取消息ID
    int getMessageID() const { return UserMessageID; }

    // 获取消息内容
    const std::string& getContent() const { return Content; }

    // 获取发送日期
    const std::string& getDate() const { return SendTime; }

    // 获取发送者ID
    int getSenderID() const { return SenderID; }

    // 获取接收者ID
    int getReceiverID() const { return ReceiverID; }

     void setUserMessageID(int id){UserMessageID=id;}
    // 设置消息内容
    void setContent(const std::string& content) { Content = content; }

    // 设置发送日期
    void setDate(const std::string& date) { SendTime = date; }

    // 设置发送者ID
    void setSenderID(int senderID) { SenderID = senderID; }

    // 设置接收者ID
    void setReceiverID(int receiverID) { ReceiverID = receiverID; }
};

#endif
