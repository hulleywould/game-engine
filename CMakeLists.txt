cmake_minimum_required(VERSION  3.5)
project(Game_Engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "src/*.cpp")

set(INCLUDE_DIR include)

find_package(glfw3 3.1 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(lib/nanogui)

add_definitions(${NANOGUI_EXTRA_DEFS})

add_executable(game-engine ${SOURCES})

include_directories(${GLFW_INCLUDE_DIRS} ${NANOGUI_EXTRA_INCS} ${INCLUDE_DIR} lib/nanogui/include)
target_link_libraries(game-engine ${GLFW_LIBRARIES} glfw ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} nanogui ${NANOGUI_EXTRA_LIBS})
