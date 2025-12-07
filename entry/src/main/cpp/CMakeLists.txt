# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(MyVulkanApp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
ADD_DEFINITIONS(-DVK_USE_PLATFORM_OHOS=1)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(entry SHARED napi_init.cpp main.cpp ../cpp/types/vulkan_library/src/application.cpp ../cpp/types/vulkan_library/src/utils/command_context.cpp
../cpp/types/vulkan_library/src/utils/pipelines.cpp ../cpp/types/vulkan_library/src/utils/queues.cpp ../cpp/types/vulkan_library/src/utils/render_pass.cpp
../cpp/types/vulkan_library/src/utils/swap_chain.cpp ../cpp/types/vulkan_library/src/utils/sync_objects.cpp)
target_link_libraries(entry PUBLIC libace_napi.z.so libace_ndk.z.so libnative_window.so libvulkan.so libhilog_ndk.z.so)
