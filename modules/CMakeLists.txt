###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(test_dynamic_win)

###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)

###############################################################################
# Compilation modes
option(USE_DEBUG "Enter debug mode" ON)
option(USE_LOG "Log Execution in a file" OFF)
option(GH_TESTS "Github tests for disable port audio" OFF)


if (UNIX)
    add_compile_options(-Wall -Wextra -Wno-unused-parameter)
    add_compile_definitions(LOG_UNIX)
    add_compile_options(-g3)
endif (UNIX)

###############################################################################
# Generate .so/.ddl

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

SET(ZIA_DIR ../Zia-Docs/include/zia)
SET(ZIA_SERVER ../Server)

add_library(PHP SHARED ./PHP-CGI/PHP.cpp)
target_include_directories(PHP PRIVATE
                    ./PHP-CGI/
                    ${ZIA_DIR}
                    ${ZIA_DIR}/module
                    ${ZIA_SERVER}/inc
                    ${ZIA_SERVER}/src
                    )

add_library(Handler1 SHARED ./Handler/Handler1.cpp)
target_include_directories(Handler1 PRIVATE
                    ./Handler/
                    ${ZIA_DIR}
                    ${ZIA_DIR}/module
                    )

add_library(FileLogger SHARED ./FileLogger/FileLogger.cpp)
target_include_directories(FileLogger PRIVATE
                    ./FileLogger/
                    ${ZIA_DIR}
                    ${ZIA_DIR}/module
                    )

add_library(Parser SHARED ./Parser/Parser.cpp ../Server/src/Request.cpp)
target_include_directories(Parser PRIVATE
                    ./Parser/
                    ${ZIA_DIR}
                    ${ZIA_DIR}/module
                    ../Server/inc)

add_library(SSL SHARED ./SSL/ConnectionWrapper.cpp)
target_include_directories(Handler1 PRIVATE
                    ./SSL/SSLConnection.cpp
                    ./SSL/
                    ${ZIA_DIR}
                    ${ZIA_DIR}/module
                    ${ZIA_SERVER}/inc
                    )