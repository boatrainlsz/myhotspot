
cmake_minimum_required(VERSION 3.0)

project(myhotspot)

set(CMAKE_CXX_FLAGS,"${CMAKE_CXX_FLAGS}")

aux_source_directory(./src/utilities SOURCE_FILES)
aux_source_directory(./src/runtime SOURCE_FILES)
aux_source_directory(./src/os SOURCE_FILES)
add_executable(myhotspot main.cpp ${SOURCE_FILES})
target_link_libraries(myhotspot dl pthread)