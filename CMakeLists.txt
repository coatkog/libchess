cmake_minimum_required(VERSION 3.16.3)

project(libchess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_LINK_DEPENDS_NO_SHARED ON)

add_library(chess SHARED
    src/board.cpp
)
target_include_directories(chess PUBLIC include)

add_executable(demo demo/main.cpp)
target_link_libraries(demo chess)
