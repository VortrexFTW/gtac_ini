cmake_minimum_required(VERSION 3.13)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(mod_ini C CXX)

# Embedded pdb in static libraries
set(EMBEDDED_PDB ON)

include(j-generic)

# include the SDK
include_directories("sdk/include")
include_directories("sdk/Helper")
include_directories("extern/ini")

add_subdirectory(module)

