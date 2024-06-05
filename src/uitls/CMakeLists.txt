# 获取当前目录下的所有源文件
file(GLOB UITLS_SOURCES *.cpp)

# 添加库
add_library(uitls ${UITLS_SOURCES})
