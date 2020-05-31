##==================================================================================================
##  LEA - Little Engine Adventure
##  Copyright 2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup Demos
##==================================================================================================
add_executable(sandbox sandbox/sandbox.cpp)

target_include_directories( sandbox
                            PRIVATE
                            ${PROJECT_SOURCE_DIR}/include
                            ${PROJECT_SOURCE_DIR}/src
                            ${LUA_INCLUDE_DIR}
                          )

target_link_libraries(sandbox lea)
target_compile_features( sandbox PRIVATE cxx_std_20  )
