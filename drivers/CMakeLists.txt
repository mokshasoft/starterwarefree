#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

project(drivers C)

# All drivers does currently not build
file(GLOB static
    *.c
)

add_library(drivers EXCLUDE_FROM_ALL ${static})
target_include_directories(drivers PUBLIC
    ${ROOT_PATH}/include
    ${ROOT_PATH}/include/hw
    ${ROOT_PATH}/include/${TARGET}
    ${ROOT_PATH}/include/${TARGET}/${DEVICE}
    ${ROOT_PATH}/usblib/include
)
