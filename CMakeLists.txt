cmake_minimum_required(VERSION  3.5)
project(Game_Engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "src/*.cpp")

set(INCLUDE_DIR include)

# Find GLFW3
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    find_package(glfw QUIET)
    if(NOT glfw_FOUND)
        message(FATAL_ERROR "GLFW3 not found. Install libglfw3-dev")
    endif()
endif()

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

# GLM is header-only, find it via pkg-config or assume it's in system include
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(GLM glm QUIET)
endif()

add_executable(game-engine ${SOURCES})

# Copy shader files and assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/src/shaders DESTINATION ${CMAKE_BINARY_DIR}/src)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Include directories
include_directories(${INCLUDE_DIR})

if(glfw3_FOUND)
    include_directories(${GLFW_INCLUDE_DIRS})
elseif(glfw_FOUND)
    include_directories(${glfw_INCLUDE_DIRS})
endif()

if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
endif()

include_directories(${FREETYPE_INCLUDE_DIRS})

# Link libraries
if(glfw3_FOUND)
    target_link_libraries(game-engine ${GLFW_LIBRARIES} glfw)
elseif(glfw_FOUND)
    target_link_libraries(game-engine ${glfw_LIBRARIES} glfw)
else()
    target_link_libraries(game-engine glfw)
endif()

target_link_libraries(game-engine ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${FREETYPE_LIBRARIES})

if(GLM_FOUND)
    target_link_libraries(game-engine ${GLM_LIBRARIES})
endif()
