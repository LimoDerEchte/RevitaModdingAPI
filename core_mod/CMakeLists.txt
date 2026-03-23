
cmake_minimum_required(VERSION 3.31)
project(RevitaModdingAPI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Mod Library
add_library(RevitaCoreMod SHARED RevitaCoreMod.cpp
        impl/RevitaModImpl.cpp
        ${LIB_SOURCES}
)

target_include_directories(RevitaCoreMod PUBLIC
        .
        ${LIB_INCLUDES}
)

target_compile_definitions(RevitaCoreMod PUBLIC
        YYTK_DEFINE_INTERNAL
)

add_custom_command(TARGET RevitaCoreMod POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:RevitaCoreMod> ${REVITA_GAME_FOLDER}/mods/Aurie)
