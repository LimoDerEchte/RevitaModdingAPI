
cmake_minimum_required(VERSION 3.31)
project(RevitaModdingAPI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Mod Library
add_library(RevitaTestMod SHARED RevitaTestMod.cpp
        ${LIB_SOURCES}
)

target_include_directories(RevitaTestMod PUBLIC
        .
        ../core_mod/include
        ${LIB_INCLUDES}
)

target_compile_definitions(RevitaTestMod PUBLIC
        YYTK_DEFINE_INTERNAL
)

add_custom_command(TARGET RevitaTestMod POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:RevitaTestMod> ${REVITA_GAME_FOLDER}/mods/Aurie)
