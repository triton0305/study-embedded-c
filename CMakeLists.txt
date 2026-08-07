cmake_minimum_required(VERSION 3.16)
project(msvc_cli C) # 중요!

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/app
    ${CMAKE_CURRENT_SOURCE_DIR}/source/hw
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/source/hw/driver
)

file(GLOB_RECURSE SOURCES
    "source/*.c"
) # 중요!

add_executable(msvc_cli ${SOURCES}) # 중요!


target_link_libraries(msvc_cli PRIVATE Kernel32 Winmm)

target_compile_options(msvc_cli PRIVATE
    "/utf-8"
)