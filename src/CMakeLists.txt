cmake_minimum_required(VERSION 3.3)
set(meme_SRCS main.cpp)
add_executable(memegen ${meme_SRCS})
target_link_libraries(memegen curlpp curl )
