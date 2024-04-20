# OPTIONS
option(MEMTRACE "ENABLE Memtrace" ON)
option(WALL "ENABLE Wall Werror Wdeprecated pedantic " ON)
option(DEBUGGER "ENABLE Debugger" ON)

option(TEST "OVERRIDE/RUN UNIT TESTS (it will disable main program from running)" OFF)
#OPTIONS END

cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PhoneBook)
if (NOT TEST)
    add_executable(${PROJECT_NAME} main.cpp)
else ()
    enable_testing()
    add_executable(${PROJECT_NAME} main_test.cpp)
endif()
unset(TEST CACHE)

if(MEMTRACE)
    add_compile_definitions(MEMTRACE)
endif(MEMTRACE)
unset(MEMTRACE CACHE)

if(WALL)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wdeprecated -pedantic)
endif(WALL)
unset(WALL CACHE)

if(DEBUGGER)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif(DEBUGGER)
unset(DEBUGGER CACHE)

add_subdirectory(src)

