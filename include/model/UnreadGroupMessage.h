#ifndef UNREADGROUPMESSAGE_H
#define UNREADGROUPMESSAGE_H

#include <string>

class UnreadGroupMessage {
public:
    // Constructor
    UnreadGroupMessage(const std::string& content, const std::string& sendTime,
                       int senderID, int receiverID, int groupID,int id=-1)
        : Content(content), SendTime(sendTime),//“2000-09-09”
          SenderID(senderID), GroupID(groupID),UnreadGroupMessageID(id){

          }
    UnreadGroupMessage(){
        UnreadGroupMessageID=-1;
    }
    // Accessors
    int getUnreadGroupMessageID() const { return UnreadGroupMessageID; }
    std::string getContent() const { return Content; }
    std::string getSendTime() const { return SendTime; }
    int getSenderID() const { return SenderID; }
    int getGroupID() const { return GroupID; }

    // Mutators
    void setUnreadGroupMessageID(int id) { UnreadGroupMessageID = id; }
    void setContent(const std::string& content) { Content = content; }
    void setSendTime(const std::string& sendTime) { SendTime = sendTime; }
    void setSenderID(int senderID) { SenderID = senderID; }
    void setGroupID(int groupID) { GroupID = groupID; }

private:
    std::string Content;
    std::string SendTime;
    int SenderID;
    int GroupID;
    int UnreadGroupMessageID;
};

#endif // UNREADGROUPMESSAGE_H
