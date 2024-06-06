#!/bin/bash

# 获取当前目录
current_dir=$(pwd)

# 设置动态库搜索路径为当前目录下的 lib 目录
export LD_LIBRARY_PATH="${current_dir}/lib:$LD_LIBRARY_PATH"



# 运行可执行文件
./build/bin/server
