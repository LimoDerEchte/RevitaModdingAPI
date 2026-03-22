
cmake_minimum_required(VERSION 3.31)
project(RevitaModdingAPI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make sure to use x86
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "You need to compile this project with a 32 bit toolchain!")
endif()

# Settings
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/local_config.cmake")
    message(FATAL_ERROR "You need to create a local_config.cmake file!")
endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/local_config.cmake")

# Libs
set(LIB_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/YYToolkit
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/Aurie
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/patches
)

set(IMGUI_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_win32.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_dx11.cpp
)

# Proxy
add_library(winmm SHARED proxy/proxy.cpp)
set_target_properties(winmm PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/proxy/proxy.def")

# Core Mods
add_subdirectory(core_mod)
