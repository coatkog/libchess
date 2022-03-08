cmake_minimum_required(VERSION 3.16.3)

project(libchess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_LINK_DEPENDS_NO_SHARED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Generate compile_commands.json file for clang
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory(submodules/spdlog)

add_library(chess SHARED
    "src/board.cpp"
    "src/move.cpp"
    "src/piece.cpp"
    "src/square.cpp"
    "src/internal/log.cpp"
)
target_include_directories(chess PUBLIC include)
target_link_libraries(chess spdlog)

add_executable(demo demo/main.cpp)
target_link_libraries(demo chess)

add_executable(demo-gui
    demo-gui/main.cpp
    demo-gui/game.cpp
    demo-gui/sprites.cpp
)
target_link_libraries(demo-gui chess sfml-graphics sfml-window sfml-system)
