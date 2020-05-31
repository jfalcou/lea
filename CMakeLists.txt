##==================================================================================================
##  LEA - Little Engine Adventure
##  Copyright 2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.5)

##==================================================================================================
## Setup project
##==================================================================================================
project(LEA VERSION 0.1 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

##==================================================================================================
## Prevent in-source build
##==================================================================================================
if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message( FATAL_ERROR "[lea] Building in-source, not recommended! Build in a separate directory." )
endif()

##==================================================================================================
## Options
##==================================================================================================
option( LEA_BUILD_TEST    "Build tests for lea"     ON  )
option( LEA_IS_DEPENDENT  "Dependent mode for lea"  OFF )

##==================================================================================================
## Setup Install target only if not used as dependent
##==================================================================================================
# UNCOMMENT WHEN SOMETHING CAN BE INSTALLED
# if( NOT LEA_IS_DEPENDENT )
#   include(install)
# else()
#   message(STATUS "[lea] LEA is used as a in-project dependency - No install targets available")
# endif()

add_subdirectory(src/lib)
add_subdirectory(src/demo)
