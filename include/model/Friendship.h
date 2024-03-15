#ifndef FRIENDSHIP_H
#define FRIENDSHIP_H

#include <string>
/*注意这里面一组id表示一组对应的好友关系*/
class Friendship {
public:
    Friendship( std::string friendRemark_, int userID_, int friendID_,int friendshipID_=1) :
      friendRemark(friendRemark_), userID(userID_), friendID(friendID_),  friendshipID(friendshipID_){}

    // Getter methods
    int getFriendshipID() const { return friendshipID; }
    std::string getFriendRemark() const { return friendRemark; }
    int getUserID() const { return userID; }
    int getFriendID() const { return friendID; }

    // Setter methods
    void setFriendshipID(int id) { friendshipID = id; }
    void setFriendRemark(const std::string& remark) { friendRemark = remark; }
    void setUserID(int id) { userID = id; }
    void setFriendID(int id) { friendID = id; }

private:
    std::string friendRemark;
    int userID;
    int friendID;
      int friendshipID;
};

#endif // FRIENDSHIP_H
