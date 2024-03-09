#include"gloab/gloabal.h"
#include<string>
  //连接数据库，初始化数据库连接池4
 std::string connection_string("mysql:database=server;user=root;password='511304Woaini@'");   
    cppdb::pool::pointer my_pool = cppdb::pool::create(connection_string); 
   std::string woaini111(){
      return "woaii";
}
cppdb::session db_connector(cppdb::pool::pointer& x){
         cppdb::session sql(x->open());
         return sql;
}

 
