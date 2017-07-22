cmake_minimum_required(VERSION  2.6)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "src/*.cpp")

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(PkgConfig REQUIRED)
find_package(glfw3 3.1 REQUIRED)
find_package(GLEW REQUIRED)

find_package(OpenGL REQUIRED)
add_executable(bomberman ${SOURCES})

include_directories(${GLFW_INCLUDE_DIRS} ${INCLUDE_DIR})
target_link_libraries(bomberman ${GLFW_LIBRARIES} glfw ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})







