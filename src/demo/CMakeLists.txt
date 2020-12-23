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

##==================================================================================================
## Setup Rough tests
##==================================================================================================
add_executable(ecs ecs/ecs.cpp)

target_include_directories( ecs
                            PRIVATE
                            ${PROJECT_SOURCE_DIR}/include
                            ${PROJECT_SOURCE_DIR}/src
                            ${LUA_INCLUDE_DIR}
                          )

target_link_libraries(ecs lea)
target_compile_features( ecs PRIVATE cxx_std_20  )
