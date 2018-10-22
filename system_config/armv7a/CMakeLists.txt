#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

project(system_config C)

file(GLOB static
    *.c
    ${COMPILER}/*.c
    ${COMPILER}/*.S
    ${DEVICE}/*.c
    ${DEVICE}/${COMPILER}/*.S
)

set(CFLAGS "${CFLAGS} -mfpu=neon -mfloat-abi=softfp")

add_library(system_config EXCLUDE_FROM_ALL ${static})
target_include_directories(system_config PUBLIC
    ${ROOT_PATH}/include/armv7a
)
