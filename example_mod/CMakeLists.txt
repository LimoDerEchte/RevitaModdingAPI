
add_library(RevitaExampleMod SHARED RevitaMod.cpp)

target_include_directories(RevitaExampleMod PRIVATE . ../loader ../minhook/include)
target_link_libraries(RevitaExampleMod PRIVATE ${MINHOOK_LIB})
