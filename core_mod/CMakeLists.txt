
cmake_minimum_required(VERSION 3.31)
project(RevitaModdingAPI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Mod Library
add_library(RevitaCoreMod SHARED RevitaCoreMod.cpp
        ${IMGUI_SOURCE}
)

target_include_directories(RevitaCoreMod PRIVATE
        .
        ${LIB_INCLUDES}
)
