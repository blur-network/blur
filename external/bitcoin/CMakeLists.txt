# Copyright (c) 2018-2019, Blur Network
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are
# permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list
#    of conditions and the following disclaimer in the documentation and/or other
#    materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be
#    used to endorse or promote products derived from this software without specific
#    prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
# THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
# THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

message(STATUS "Adding bitcoin-specfic dependencies for DPoW integrations")

cmake_minimum_required(VERSION 3.0)

project(bitcoin LANGUAGES C CXX)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=c++11")

add_library(bitcoin
  ${PROJECT_NAME}.cpp)

set(header_files
  ${PROJECT_NAME}.h)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(bitcoin)

# GUI/libwallet install target
if (BUILD_GUI_DEPS)
    if(IOS)
        set(lib_folder lib-${ARCH})
    else()
        set(lib_folder lib)
    endif()
    install(TARGETS bitcoin
        ARCHIVE DESTINATION ${lib_folder}
        LIBRARY DESTINATION ${lib_folder})
endif()
set_property(TARGET bitcoin APPEND PROPERTY COMPILE_FLAGS "-fPIC")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

string(TOUPPER "${PROJECT_NAME}" setting_prefix)
function(get_setting setting_name setting_type setting_description)
    string(TOUPPER "${setting_prefix}_${setting_name}" setting_external_name)
    set("${setting_external_name}" "" CACHE "${setting_type}" "${setting_description}")
    set("${setting_name}" "${${setting_external_name}}" PARENT_SCOPE)
endfunction()


# Project files

set(source_files
  ${PROJECT_NAME}.cpp
  arith_uint256.cpp
  strencodings.cpp
  uint256.cpp
  arith_uint256.h
  attributes.h
  endian.h
  strencodings.h
  tinyformat.h
  uint256.h)


set(header_files
  ${PROJECT_NAME}.h)

# Compile options

get_setting(target_arch STRING "Target system architecture (fed to the compiler's -march=...).")
if(NOT target_arch AND NOT CMAKE_CROSSCOMPILING)
    set(target_arch native)
endif()

set(compile_options
        # GNU, Clang
        $<$<OR:$<C_COMPILER_ID:AppleClang>,$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:
            # Optimizations
            -Os $<$<BOOL:${target_arch}>:-march=${target_arch}> -fno-exceptions
            # Warnings
            -Wall -Wextra -Wdiv-by-zero  -Wcast-align
            -Wcast-qual -Wfloat-equal -Wmissing-declarations -Wno-unknown-pragmas
            -Wpointer-arith -Wredundant-decls -Wswitch-enum -Wno-type-limits>

        # MSVC
        $<$<C_COMPILER_ID:MSVC>:
            # Optimizations
            /Os /EHsc
            # Warnings
            /WX /W4
            /wd4197 # suppress warning "top-level volatile in cast is ignored"
            /wd4146 # suppress warning "unary minus operator applied to unsigned type, result still unsigned"
            /wd4310 # suppress warning "cast truncates constant value"
        >)


# Main library

add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_sources("${PROJECT_NAME}" PRIVATE ${project_source_files})

target_include_directories("${PROJECT_NAME}" PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_options("${PROJECT_NAME}" PRIVATE ${compile_options})

# Installation

set(targets_export_name "${PROJECT_NAME}-targets")

install(TARGETS "${PROJECT_NAME}"
        EXPORT "${targets_export_name}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(FILES ${project_header_files}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# CMake find_package() support

set(install_config_dir "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}")

set(targets_export_file_name "${targets_export_name}.cmake")
set(targets_export_file "${PROJECT_BINARY_DIR}/${targets_export_file_name}")

install(EXPORT "${targets_export_name}"
        FILE "${targets_export_file_name}"
        NAMESPACE "${PROJECT_NAME}::"
        DESTINATION "${install_config_dir}")

set(config_file_name "${PROJECT_NAME}-config.cmake")
set(config_template_file "${PROJECT_SOURCE_DIR}/cmake/${config_file_name}.in")
set(config_file "${PROJECT_BINARY_DIR}/${config_file_name}")

CONFIGURE_PACKAGE_CONFIG_FILE("${config_template_file}" "${config_file}"
        INSTALL_DESTINATION "${install_config_dir}")

install(FILES "${config_file}"
        DESTINATION "${install_config_dir}")

export(EXPORT "${targets_export_name}"
        FILE "${targets_export_file}"
        NAMESPACE "${PROJECT_NAME}::")

export(PACKAGE "${PROJECT_NAME}")
