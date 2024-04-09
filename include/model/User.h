#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    // 构造函数
    User(const std::string& password, const std::string& username, const std::string& personalSignature,int id);
     User();
    // 获取用户ID
    int getId() const;

    // 设置用户ID
    void setId(int id);

    // 获取密码
    const std::string& getPassword() const;

    // 设置密码
    void setPassword(const std::string& password);

    // 获取用户名
    const std::string& getUsername() const;

    // 设置用户名
    void setUsername(const std::string& username);

    // 获取个人签名
    const std::string& getPersonalSignature() const;

    // 设置个人签名
    void setPersonalSignature(const std::string& personalSignature);

    // 获取用户状态
    bool getState() const;

    // 设置用户状态
    void setState(bool state);
    
    bool operator==(const User&x);

    bool operator<(const User& x);
private:
 
    std::string password_; // 密码
    std::string username_; // 用户名
    std::string personalSignature_; // 个人签名
    bool state_; // 用户状态
       int id_; // 用户ID

};
inline User::User(){
    id_=-1;
}

// 构造函数
 inline User::User(const std::string& password, const std::string& username, const std::string& personalSignature,int id=1)
    : password_(password), username_(username), personalSignature_(personalSignature),id_(id) {}

// 获取用户ID
inline int User::getId() const {
    return id_;
}

// 设置用户ID
inline void User::setId(int id) {
    id_ = id;
}

// 获取密码
inline const std::string& User::getPassword() const {
    return password_;
}

// 设置密码
 inline void User::setPassword(const std::string& password) {
    password_ = password;
}

// 获取用户名
inline const std::string& User::getUsername() const {
    return username_;
}

// 设置用户名
inline void User::setUsername(const std::string& username) {
    username_ = username;
}

// 获取个人签名
inline const std::string& User::getPersonalSignature() const {
    return personalSignature_;
}

// 设置个人签名
inline void User::setPersonalSignature(const std::string& personalSignature) {
    personalSignature_ = personalSignature;
}

// 获取用户状态
inline bool User::getState() const {
    return state_;
}

// 设置用户状态
inline void User::setState(bool state) {
    state_ = state;
}


   inline bool User::operator==(const User&x){
      return id_==x.getId();
   }


   inline bool User::operator<(const User& x){
          return id_<x.getId();
   }
namespace std
{
    template<>
    struct hash<User>
    {
        typedef User argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s) const
        {
            result_type const h1 ( std::hash<int>()(s.getId()) );
            result_type const h2 ( std::hash<int>()(s.getId()) );
            return h1 ^ (h2 << 1);
        }
    };

    template<>
    struct   equal_to<User>
    {
        typedef User argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s1,argument_type const& s2) const
        {
            result_type const h1 ( std::hash<int>()(s1.getId()) );
            result_type const h2 ( std::hash<int>()(s2.getId()) );
            return h1==h2;
        }
    };

}


#endif // USER_H
