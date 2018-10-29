#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

project(system_config C)

assert(COMPILER "Variable COMPILER has to be set to build system_config")
assert(DEVICE "Variable DEVICE has to be set to build system_config")

file(GLOB static
    mmu.c
    cache.c
    ${COMPILER}/cpu.c
    ${COMPILER}/cp15.S
    ${COMPILER}/init.S
    ${DEVICE}/interrupt.c
    ${DEVICE}/startup.c
    ${DEVICE}/clock.c
    ${DEVICE}/device.c
    ${DEVICE}/${COMPILER}/exceptionhandler.S
)

# Tell CMake to treat these files as C-files
set_property(SOURCE ${COMPILER}/cp15.S PROPERTY LANGUAGE C)
set_property(SOURCE ${COMPILER}/init.S PROPERTY LANGUAGE C)
set_property(SOURCE ${DEVICE}/${COMPILER}/exceptionhandler.S PROPERTY LANGUAGE C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=neon -mfloat-abi=softfp")

add_library(system_config EXCLUDE_FROM_ALL ${static})
target_include_directories(system_config PUBLIC
    ${ROOT_PATH}/include/hw
    ${ROOT_PATH}/include/${TARGET}
    ${ROOT_PATH}/include/${TARGET}/${DEVICE}
)
