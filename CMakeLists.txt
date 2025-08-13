cmake_minimum_required(VERSION 3.31)
project(CDGE)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED glslang)
if (DEFINED Vulkan_INCLUDE_DIRS)
    message(STATUS "Vulkan include path: ${Vulkan_INCLUDE_DIRS}")
endif ()

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(CDGE
        src/main.cpp
        src/Renderer.cpp
        vendored/imgui/imgui.cpp
        vendored/imgui/imgui_draw.cpp
        vendored/imgui/imgui_tables.cpp
        vendored/imgui/imgui_widgets.cpp
)

target_include_directories(CDGE PRIVATE ${Vulkan_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/vendored/imgui)
target_link_libraries(CDGE PRIVATE SDL3::SDL3)
