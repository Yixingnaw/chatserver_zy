#ifndef UNREADUSERMESSAGE_H
#define UNREADUSERMESSAGE_H

class UnreadUserMessage {
private:
    int ReceiverID;
    int UserMessageID;
     int UnreadUserMessageID;
public:
    // 构造函数
    inline UnreadUserMessage( int receiverID, int userMessageID,int id=1)
        : ReceiverID(receiverID), UserMessageID(userMessageID),UnreadUserMessageID(id) {}
     UnreadUserMessage(){
        UnreadUserMessageID=-1;
     }
    // 获取未读消息ID
    inline int getUnreadMessageID() const { return UnreadUserMessageID; }
    
    // 获取接收者ID
    inline int getReceiverID() const { return ReceiverID; }

    // 获取用户消息ID
    inline int getUserMessageID() const { return UserMessageID; }

    // 设置接收者ID
    inline void setReceiverID(int receiverID) { ReceiverID = receiverID; }

    // 设置用户消息ID
    inline void setUserMessageID(int userMessageID) { UserMessageID = userMessageID; }
};

#endif
