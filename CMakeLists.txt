cmake_minimum_required(VERSION 3.16)
project(PacWoman VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system QUIET)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Maze.cpp
    src/PacWoman.cpp
    src/Ghost.cpp
    src/Pellet.cpp
    src/HUD.cpp
)

set(HEADERS
    include/PacWoman/Game.hpp
    include/PacWoman/Maze.hpp
    include/PacWoman/PacWoman.hpp
    include/PacWoman/Ghost.hpp
    include/PacWoman/Pellet.hpp
    include/PacWoman/HUD.hpp
    include/PacWoman/Constants.hpp
    include/PacWoman/Entity.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(SFML_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
else()
    message(STATUS "SFML not found. Building without linking SFML (structure-only build).")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NO_SFML)
endif()
