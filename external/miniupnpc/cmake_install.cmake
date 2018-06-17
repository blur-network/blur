# Install script for directory: /home/biz/github/repos/blur/external/miniupnpc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/biz/github/repos/blur/external/miniupnpc/libminiupnpc.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniupnpc" TYPE FILE FILES
    "/home/biz/github/repos/blur/external/miniupnpc/miniupnpc.h"
    "/home/biz/github/repos/blur/external/miniupnpc/miniwget.h"
    "/home/biz/github/repos/blur/external/miniupnpc/upnpcommands.h"
    "/home/biz/github/repos/blur/external/miniupnpc/igd_desc_parse.h"
    "/home/biz/github/repos/blur/external/miniupnpc/upnpreplyparse.h"
    "/home/biz/github/repos/blur/external/miniupnpc/upnperrors.h"
    "/home/biz/github/repos/blur/external/miniupnpc/upnpdev.h"
    "/home/biz/github/repos/blur/external/miniupnpc/miniupnpctypes.h"
    "/home/biz/github/repos/blur/external/miniupnpc/portlistingparse.h"
    "/home/biz/github/repos/blur/external/miniupnpc/miniupnpc_declspec.h"
    )
endif()

