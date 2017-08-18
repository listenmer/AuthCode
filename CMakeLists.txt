CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(AuthCode)

add_compile_options(-std=c++11)

file(GLOB_RECURSE  native_srcs "cpp/*.cpp" "cpp/*.cc")

ADD_EXECUTABLE(TestAuthCode main.cpp ${native_srcs})