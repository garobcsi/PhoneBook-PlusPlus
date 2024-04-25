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
    include(FetchContent)
    set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
    FetchContent_Declare(tabulate
            GIT_REPOSITORY https://github.com/p-ranav/tabulate
            GIT_TAG v1.5
            SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/tabulate"
    )
    FetchContent_MakeAvailable(tabulate)
    #TABLE LIB
    target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/tabulate/single_include/tabulate/tabulate.hpp )
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

#PHONE BOOK
target_sources(${PROJECT_NAME} PRIVATE
        string.cpp string.h
        array.h
        contact.cpp contact.h
        contacts.cpp contacts.h
)

#TERMINAL
target_sources(${PROJECT_NAME} PRIVATE
        menu.cpp menu.h
)

#LIBS
target_sources(${PROJECT_NAME} PRIVATE
        gtest_lite.h
        memtrace.cpp memtrace.h)
