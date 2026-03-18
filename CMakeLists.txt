
cmake_minimum_required(VERSION 3.31)
project(RevitaModdingAPI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Settings
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/local_config.cmake")
    message(FATAL_ERROR "You need to create a local_config.cmake file!")
endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/local_config.cmake")

include_directories(include)
set(MINHOOK_LIB ${REVITA_GAME_FOLDER}/loader/MinHook.x64.lib)

# Loader
add_library(execute_shell_simple SHARED loader/dllmain.cpp
        loader/Console/Console.cpp
        loader/Loader.cpp
)
target_include_directories(execute_shell_simple PRIVATE loader)

# Core Mods
add_subdirectory(example_mod)
