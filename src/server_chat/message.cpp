#include"gloab/message.h"
#include<memory.h>
#include<string>
using namespace std;
message::message(/* args */)
{
}

 message::message(std::string &data){
            
 
      int64_t data_size=data.size()+8;
      data_.resize(data_size);
      memcpy(data_.data(),&data_size,8);
      memcpy(data_.data()+8,data.c_str(),data.size());
 }
message::~message()
{
}

void message::resize(int x){
    data_.resize(x);
}

const  void* message::data()const{
    return data_.data();
}
int64_t message::size()const{
    return data_.size();
}
