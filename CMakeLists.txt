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

find_path(Muduo_INCLUDE_DIR muduo "${MUDUO_PATH}/include")
find_path(Muduo_LIBRARY_DIR libmuduo_net.a "${MUDUO_PATH}/lib")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Muduo_LIBRARY_DIR})
#message(STATUS ${Muduo_INCLUDE_DIR})
#message(STATUS ${Muduo_LIBRARY_DIR})

include_directories(${Muduo_INCLUDE_DIR})

find_library(muduo_base muduo_base)
find_library(muduo_net muduo_net)
#message(STATUS ${muduo_base})
#message(STATUS ${muduo_net})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#前面都是找到muduo库头文件，和对应的muduo库与boost库



include_directories(${PROJECT_SOURCE_DIR})
include_directories(/home/zy/code/server/include)


file(GLOB LIB_SOURCES lib/*.cpp)#加入所有lib
file(GLOB SRC_SOURCES src/*.cpp)#加入所有src

add_executable(server main.cpp ${LIB_SOURCES} ${SRC_SOURCES}) 
# 添加modle目录
add_subdirectory(src/model)
#添加serviece目录
add_subdirectory(src/service)
#添加server_chat目录
add_subdirectory(src/server_chat)


target_link_libraries(server ${muduo_net})
target_link_libraries(server ${muduo_base})
target_link_libraries(server pthread rt)
target_link_libraries(server mysqlclient)
target_link_libraries(server cppdb)
target_link_libraries(server model)#model层
target_link_libraries(server server_chat)
target_link_libraries(server service)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
