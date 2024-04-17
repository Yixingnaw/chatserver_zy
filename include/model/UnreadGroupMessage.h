#ifndef UNREADGROUPMESSAGE_H
#define UNREADGROUPMESSAGE_H

#include <string>

class UnreadGroupMessage {
public:
    // Constructor
    UnreadGroupMessage(const std::string& content, const std::string& sendTime,
                       int senderID, int receiverID, int groupID,int id=-1)
        : Content(content), SendTime(sendTime),//“2000-09-09”
          SenderID(senderID), ReceiverID(receiverID), GroupID(groupID),UnreadGroupMessageID(id){

          }

    // Accessors
    int getUnreadGroupMessageID() const { return UnreadGroupMessageID; }
    std::string getContent() const { return Content; }
    std::string getSendTime() const { return SendTime; }
    int getSenderID() const { return SenderID; }
    int getReceiverID() const { return ReceiverID; }
    int getGroupID() const { return GroupID; }

    // Mutators
    void setUnreadGroupMessageID(int id) { UnreadGroupMessageID = id; }
    void setContent(const std::string& content) { Content = content; }
    void setSendTime(const std::string& sendTime) { SendTime = sendTime; }
    void setSenderID(int senderID) { SenderID = senderID; }
    void setReceiverID(int receiverID) { ReceiverID = receiverID; }
    void setGroupID(int groupID) { GroupID = groupID; }

private:
    int UnreadGroupMessageID;
    std::string Content;
    std::string SendTime;
    int SenderID;
    int ReceiverID;
    int GroupID;
};

#endif // UNREADGROUPMESSAGE_H
