cmake_minimum_required(VERSION 3.7)
project(GameLoop)

set(
    SOURCE_FILES
    cpp/main.cpp
    h/GameLoop.h
    h/SDLWindow.h
    h/Events.h
)
add_executable(GameLoop ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} )

target_link_libraries(GameLoop ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -fmax-errors=1")
