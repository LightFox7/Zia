###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(zia_2020)

###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
# Compilation modes
option(USE_DEBUG "Enter debug mode" ON)
option(USE_LOG "Log Execution in a file" OFF)
option(GH_TESTS "Github tests for disable port audio" OFF)

###############################################################################
# Set Compile Options
if (UNIX)
    add_compile_options(-Wall -Wextra)
    add_compile_definitions(LOG_UNIX)
endif (UNIX)

if (USE_LOG)
    if (UNIX)
        add_compile_definitions(LOG_UNIX)
        add_compile_definitions(_zia_LOG_)
    endif (UNIX)
endif (USE_LOG)

if (COVERAGE)
    add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
endif (COVERAGE)

if (USE_DEBUG)
    if (UNIX)
        add_compile_options(-g3)
    endif (UNIX)
    add_compile_definitions(_DEBUG_)
endif (USE_DEBUG)

###############################################################################
# Conan Build Management

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})

find_package(Boost COMPONENTS REQUIRED)

find_package(OpenSSL COMPONENTS REQUIRED)

set(CONAN_LIBS ${CONAN_LIBS} boost_thread)

###############################################################################

# zia SERVER
set(SERVER_DIR Server)

#Server Includes
set(
    SERVER_INCLUDES
    ${SERVER_DIR}/inc
)

set(API_DIR Zia-Docs)

set(
    API_INCLUDES
    ${API_DIR}/include/zia
    ${API_DIR}/include/zia/module
)

#Server Sources
set(
    SERVER_SOURCES
    ${SERVER_DIR}/src/main.cpp
    ${SERVER_DIR}/src/Config.cpp
    ${SERVER_DIR}/src/Object.cpp
    ${SERVER_DIR}/src/Array.cpp
    ${SERVER_DIR}/src/ModuleLoader.cpp
    ${SERVER_DIR}/src/Client.cpp
    ${SERVER_DIR}/src/BaseCore.cpp
    ${SERVER_DIR}/src/HttpCore.cpp
    ${SERVER_DIR}/src/HttpsCore.cpp
    ${SERVER_DIR}/src/DefaultLogger.cpp
    ${SERVER_DIR}/src/DefaultParser.cpp
    ${SERVER_DIR}/src/RequestEmitter.cpp
    ${SERVER_DIR}/src/Server.cpp
    ${SERVER_DIR}/src/Socket.cpp
    ${SERVER_DIR}/src/Connection.cpp
    ${SERVER_DIR}/src/Modules.cpp
    ${SERVER_DIR}/src/Terminal.cpp
    ${SERVER_DIR}/src/ClientsInstance.cpp
    ${SERVER_DIR}/src/Loggers.cpp
    ${SERVER_DIR}/src/RequestWrapper.cpp
    ${SERVER_DIR}/src/HttpStatusCodes.cpp
    ${SERVER_DIR}/src/Response.cpp
    ${SERVER_DIR}/src/Context.cpp
    ${SERVER_DIR}/src/Request.cpp
)

#Server Executable
add_executable(
    zia
    ${SERVER_SOURCES}
)

target_include_directories(
    zia PUBLIC
    ${API_INCLUDES}
    ${SERVER_INCLUDES}
)

target_compile_options(zia PRIVATE)
target_link_libraries(zia ${CONAN_LIBS})

if (UNIX)
    target_link_libraries(zia ${CMAKE_DL_LIBS})
endif (UNIX)

###########################

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

SET(ZIA_DIR ./Zia-Docs/include/zia)
SET(ZIA_SERVER ./Server)


add_library(SSL SHARED ./modules/SSL/ConnectionWrapper.cpp ./modules/SSL/SSLConnection.cpp)
target_include_directories(SSL PRIVATE
                    ./modules/SSL/
                    ${ZIA_DIR}
                    ${ZIA_DIR}/module
                    ./Server/inc
                    )
target_link_libraries(SSL -lssl -lcrypto ${CONAN_LIBS})

add_library(Parser SHARED ./modules/Parser/Parser.cpp ./Server/src/Request.cpp)
target_include_directories(Parser PRIVATE
                    ./modules/Parser/
                    ${ZIA_DIR}
                    ${ZIA_DIR}/module
                    ./Server/inc
                    )

add_library(PHP SHARED ./modules/PHP-CGI/PHP.cpp ./Server/src/Request.cpp)
target_include_directories(PHP PRIVATE
                        ./modules/PHP-CGI/
                        ${ZIA_DIR}
                        ${ZIA_DIR}/module
                        ./Server/inc
                        ./Server/src
                    )
target_link_libraries(PHP ${CONAN_LIBS})

#target_link_libraries(PHP -lboost_filesystem)
target_compile_options(PHP PRIVATE -w)

add_library(file-serving SHARED ./modules/file-serving/Handler.cpp ./modules/file-serving/mimeType.cpp)
target_include_directories(file-serving PRIVATE
                        ./modules/file-serving/
                        ${ZIA_DIR}
                        ./Server/inc
                    )
target_link_libraries(file-serving ${CONAN_LIBS})

add_library(error-pages SHARED ./modules/error-pages/Handler.cpp)
target_include_directories(error-pages PRIVATE
                        ./modules/error-pages/
                        ${ZIA_DIR}
                        ./Server/inc
                    )
target_link_libraries(error-pages ${CONAN_LIBS})

add_library(FileLogger SHARED ./modules/FileLogger/FileLogger.cpp)
target_include_directories(FileLogger PRIVATE
                        ./modules/FileLogger/
                        ${ZIA_DIR}
                        ./Server/inc
                    )