##==================================================================================================
##  LEA - Little Engine Adventure
##  Copyright 2020 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
add_library ( lea SHARED
              ##====================================================================================
              ## General game engine
              ##====================================================================================
              engine/game.cpp
              engine/interpreter.cpp
              engine/scene.cpp
              engine/drawable.cpp
              ##====================================================================================
              ## General game engine - Drawing primitive
              ##====================================================================================
              engine/primitive/quad.cpp
              ##====================================================================================
              ## System interoperability
              ##====================================================================================
              system/directory.cpp
              system/random.cpp
              system/window.cpp
            )

add_library(lea::lea ALIAS lea)

if( MSVC )
target_compile_options  ( lea PRIVATE /W3 /EHsc)
else()
target_compile_options  ( lea PRIVATE -Wall -fvisibility=hidden)
endif()

set_target_properties     ( lea PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/demo" )
target_compile_features   ( lea PRIVATE     cxx_std_20                                            )
target_compile_definitions( lea PRIVATE     LEA_API_EXPORTS=1                                     )

target_include_directories( lea
                            PUBLIC
                                $<INSTALL_INTERFACE:include>
                                $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                            PRIVATE
                                ${PROJECT_SOURCE_DIR}/src
                                ${LUA_INCLUDE_DIR}
                          )

find_package(Lua  5.4 EXACT REQUIRED  )
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
set(LEA_LIBRARIES sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${LUA_LIBRARIES})

target_link_libraries(lea ${LEA_LIBRARIES})

target_compile_options( lea PRIVATE ${options} )
