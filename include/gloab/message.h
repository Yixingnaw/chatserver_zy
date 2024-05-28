#include<vector>
#include<string>
class message
{
//消息格式，每个发送数据前加入数据长度
private:
 
    std::vector<char>data_;
   
public:
    message(/* args */);
    message(std::string &data);
    ~message();

   void resize(int);
 const  void* data()const;
   int64_t size()const;
};

