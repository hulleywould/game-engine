cmake_minimum_required(VERSION  2.6)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "src/*.cpp")

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)
set(GL_LIBRARY -lGLEW -lglfw3 -lGL -ldl -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread)
add_executable(bomberman ${SOURCES})

include_directories(${GLFW_INCLUDE_DIRS} ${INCLUDE_DIR})
target_link_libraries(bomberman ${GLFW_LIBRARIES} ${GL_LIBRARY})







