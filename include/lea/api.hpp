//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LEA_API_HPP_INCLUDED
#define LEA_API_HPP_INCLUDED

#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
  #ifdef LEA_API_EXPORTS
    #ifdef __GNUC__
      #define LEA_API __attribute__ ((dllexport))
    #else
      #define LEA_API __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define LEA_API __attribute__ ((dllimport))
    #else
      #define LEA_API __declspec(dllimport)
    #endif
  #endif
  #define LEA_INTERNAL
#else
  #define LEA_API       __attribute__ ((visibility ("default")))
  #define LEA_INTERNAL  __attribute__ ((visibility ("hidden")))
#endif

#endif
