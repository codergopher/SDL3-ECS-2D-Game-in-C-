cmake_minimum_required (VERSION 4.1)

project (Main)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(Lua REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(sol2 REQUIRED)

#Compiler flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -m64 -g -Wall -fno-omit-frame-pointer -L ")
set (source_dir "${PROJECT_SOURCE_DIR}/src")

#We want to output our .exe to the "bin" dir, and if we make any .a or .dll.a files we'll output them to "lib"
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#This list should contain all your include directories
set (include_list "")

#This list should contain all your link libraries, such as .a files for static linking, and .dll.a files for dynamic linking
#If you have a library installed via MSYS2 you can append it to the list with just -lfoo for example
set (lib_list "")
list (APPEND lib_list "SDL3")
list (APPEND lib_list "SDL3_image")
list (APPEND lib_list "lua")
list (APPEND lib_list "jsoncpp")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable (Main ${source_files})

target_link_libraries(Main PRIVATE ${lib_list})
target_include_directories(Main PRIVATE src ${include_list})