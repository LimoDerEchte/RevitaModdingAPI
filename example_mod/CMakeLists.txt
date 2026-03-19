
cmake_minimum_required(VERSION 3.31)
project(RevitaModdingAPI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Mod Library
add_library(RevitaExampleMod SHARED RevitaMod.cpp)

target_include_directories(RevitaExampleMod PRIVATE . ../loader ../minhook/include ${YYTK_INCLUDE})
target_link_libraries(RevitaExampleMod PRIVATE ${MINHOOK_LIB})
