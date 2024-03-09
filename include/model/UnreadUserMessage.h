#ifndef UNREADUSERMESSAGE_H
#define UNREADUSERMESSAGE_H

class UnreadUserMessage {
private:
    int UnreadUserMessageID;
    int ReceiverID;
    int UserMessageID;

public:
    // 构造函数
    inline UnreadUserMessage(int id, int receiverID, int userMessageID)
        : UnreadUserMessageID(id), ReceiverID(receiverID), UserMessageID(userMessageID) {}
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
