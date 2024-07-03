# Project settings
cmake_minimum_required (VERSION 3.10)
project (Project1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_BUILD_TYPE Debug)

# Paths etc
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
file (GLOB source_files ${source_dir}/*.cpp)

# Output directories
set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")
#include_directories(${PROJECT_SOURCE_DIR}/inc)


add_executable (Project1 src/main.cpp)

# links header files from ./inc directory
target_link_directories (Project1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)