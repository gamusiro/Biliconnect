cmake_minimum_required(VERSION 3.20.0)

set(NAME "Biliconnect")
project(${NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT WIN32)
    message(FATAL_ERROR "platform windows only")
    return()
endif()

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16.0)
    message(FATAL_ERROR "must be at least 16.0" ${CMAKE_CXX_COMPILER_VERSION})
    return()
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

file(GLOB CODES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.rc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hlsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/Material/Texture/*.ico"
    "${CMAKE_CURRENT_SOURCE_DIR}/original/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/original/*.cpp"
)

add_executable(${NAME} WIN32 ${CODES})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/stb_library")
target_compile_options(${NAME} PRIVATE /W3 /sdl /MP)