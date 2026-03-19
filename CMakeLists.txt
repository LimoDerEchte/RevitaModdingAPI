
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
set(YYTK_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/lib/YYToolkit/ExamplePlugin/include)
set(MINHOOK_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/lib/minhook/include)
set(MINHOOK_LIB ${REVITA_GAME_FOLDER}/lib/loader/MinHook.x86.lib)

include_directories(include)

# Proxy
add_library(winmm SHARED proxy/proxy.cpp)
set_target_properties(winmm PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/proxy/proxy.def")

# Loader
add_library(RevitaModLoader SHARED
        loader/Loader.cpp
        loader/Console/Console.cpp
)
target_include_directories(RevitaModLoader PRIVATE loader ${YYTK_INCLUDE})

# Core Mods
add_subdirectory(example_mod)
