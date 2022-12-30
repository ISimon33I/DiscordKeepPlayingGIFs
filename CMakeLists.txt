cmake_minimum_required (VERSION 3.2)
project ("DiscordKeepPlayingGIFs")

set(CMAKE_CXX_STANDARD 20)
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif(MSVC)

add_executable(${PROJECT_NAME} main.cpp)
