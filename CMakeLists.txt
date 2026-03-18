
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

include_directories(include)
set(MINHOOK_LIB ${REVITA_GAME_FOLDER}/loader/MinHook.x86.lib)

# Loader
add_library(loader_proxy SHARED loader/dllmain.cpp
        loader/Console/Console.cpp
        loader/Loader.cpp
)
target_include_directories(loader_proxy PRIVATE loader)

# Core Mods
add_subdirectory(example_mod)
