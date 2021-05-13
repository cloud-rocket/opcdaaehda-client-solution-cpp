#
# Copyright (c) 2011-2018 Technosoftware GmbH. All rights reserved
# Web: https://technosoftware.com 
# 
# Purpose: 
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
project(Technosoftware)


# Specify a minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Provide the path which contains CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")

# Load some functions defined by Technosoftware
include(Technosoftware)

# Set the build type to release
# setBuildTypeToRelease()

# Set the Technosoftware compiler flags
setTechnosoftwareCompilerFlags()

# Set linker restrictions
setTechnosoftwareLinkerRestrictions()

# Include the src/ directory.
include_directories("${PROJECT_SOURCE_DIR}/../include")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Technosoftware")

# add the Technosoftware subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/Technosoftware)

# set the output directories
setTechnosoftwareOutputDirectories()

# Print the include dirs
message(STATUS "The following directories are included:")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS " * ${dir}")
endforeach()