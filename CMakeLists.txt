#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

include(build/CMake/utils.cmake)

# Configuration options

if(NOT DEVICE)
    set(DEVICE "am335x")
    message(STATUS "Using default value for DEVICE (${DEVICE})")
endif()

if(NOT EVM)
    set(EVM "beaglebone")
    message(STATUS "Using default value for EVM (${EVM})")
endif()

if(NOT TARGET)
    set(TARGET "armv7a")
    message(STATUS "Using default value for TARGET (${TARGET})")
endif()

if(NOT BOOT)
    set(BOOT "MMCSD")
    message(STATUS "Using default value for BOOT (${BOOT})")
endif()

if(NOT IMG_LOAD_ADDR)
    set(IMG_LOAD_ADDR "0x80000000")
    message(STATUS "Using default value for IMG_LOAD_ADDR (${IMG_LOAD_ADDR})")
endif()

if(NOT BUILD_TYPE)
    set(BUILD_TYPE "release")
    message(STATUS "Using default value for BUILD_TYPE (${BUILD_TYPE})")
    message(STATUS "  Available BUILD_TYPE values: release, debug")
endif()

# Setup build variables

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${DEVICE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${EVM}")

# Add library components

add_subdirectory(bootloader)
add_subdirectory(drivers)
add_subdirectory(platform/${EVM})
add_subdirectory(system_config/${TARGET})
add_subdirectory(utils)
add_subdirectory(mmcsdlib)
add_subdirectory(grlib)
add_subdirectory(usblib)

# Add third party libs

add_subdirectory(third_party/fatfs)

# Add example apps

add_subdirectory(examples/${EVM})
