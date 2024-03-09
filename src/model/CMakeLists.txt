# 在 src/model 目录下的 CMakeLists.txt

# 获取当前目录下的所有源文件
file(GLOB MODEL_SOURCES *.cpp)

# 添加库
add_library(model ${MODEL_SOURCES})
