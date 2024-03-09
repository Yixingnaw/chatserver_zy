# 在 src/server 目录下的 CMakeLists.txt

# 获取当前目录下的所有源文件
file(GLOB SERVER_SOURCES *.cpp)

# 添加库
add_library(server_chat ${SERVER_SOURCES})
