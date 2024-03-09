# 在 src/service 目录下的 CMakeLists.txt

# 获取当前目录下的所有源文件
file(GLOB SERVICE_SOURCES *.cpp)

# 添加库
add_library(service ${SERVICE_SOURCES})
