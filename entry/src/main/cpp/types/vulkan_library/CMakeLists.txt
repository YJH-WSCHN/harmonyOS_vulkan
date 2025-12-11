# Only for Windows test...
cmake_minimum_required(VERSION 3.27)
project(test)

if (NOT WIN32)
    message(FATAL_ERROR "You should only use the test app on Windows!")
endif()

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(test main.cpp ${SOURCE_FILES})

# Vulkan
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})
target_link_libraries(test ${Vulkan_LIBRARIES})

# Glfw
include_directories(glfw/include)
target_link_libraries(test ${PROJECT_SOURCE_DIR}/glfw/lib/libglfw3.a)