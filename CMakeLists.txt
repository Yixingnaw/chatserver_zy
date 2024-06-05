cmake_minimum_required(VERSION 3.0.0)
project(server VERSION 0.1.0 LANGUAGES C CXX)

add_compile_options(-finput-charset=UTF-8)

include(CTest)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "debug")
endif()

if(NOT MUDUO_PATH)
  set(MUDUO_PATH "/home/$ENV{USER}/muduo/build/release-install-cpp11")
endif()

set(CXX_FLAGS
 -g
 # -DVALGRIND
 # -DMUDUO_STD_STRING
 -Wall
 -Wextra
 # -m32
 #-Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)



# 设置第三方库路径
set(MUDUO_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CPPDB_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# 查找 第三方库 库路径
find_library(Muduo_NET_LIBRARY libmuduo_net.a PATHS "${MUDUO_LIB_PATH}")
find_library(Muduo_BASE_LIBRARY libmuduo_base.a PATHS "${MUDUO_LIB_PATH}")
find_library(CPPDB_LIBRARY libcppdb.a PATHS "${CPPDB_LIB_PATH}")

include_directories(${Boost_INCLUDE_DIRS})#boost库头文件
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include/muduo)

file(GLOB LIB_SOURCES lib/*.cpp)#加入所有lib
file(GLOB SRC_SOURCES src/*.cpp)#加入所有src

add_executable(server main.cpp ${LIB_SOURCES} ${SRC_SOURCES}) 
# 添加modle目录
add_subdirectory(src/model)
#添加serviece目录
add_subdirectory(src/service)
#添加server_chat目录
add_subdirectory(src/server_chat)
add_subdirectory(src/uitls)



target_link_libraries(server model)#model层
target_link_libraries(server server_chat)
target_link_libraries(server service)
target_link_libraries(server uitls)



# 链接 第三方库,需要安装的系统第三方库
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(server pthread rt)
target_link_libraries(server mysqlclient)
#本项目需要的第三方库，需要自行编译，在lib下面给出
target_link_libraries(server ${Muduo_NET_LIBRARY} ${Muduo_BASE_LIBRARY})
target_link_libraries(server ${CPPDB_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
