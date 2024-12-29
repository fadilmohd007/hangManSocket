# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(HangMan)

# Add the executable and specify the C file(s) to compile
add_executable(hangManServer server/main.c)
add_executable(hangManClient client/main.c)

add_library(randomGen STATIC randomGen.c)
add_library(charOps STATIC charOps.c)
add_library(hangMan STATIC hangMan.c)
find_package(SQLite3 REQUIRED)

target_include_directories(hangManServer PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(hangManClient PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(hangManServer randomGen charOps hangMan) 
target_link_libraries(hangManClient randomGen charOps)
target_link_libraries(hangMan randomGen charOps ) 


# Optionally, set C standard (e.g., C11)
set(CMAKE_C_STANDARD 11)
