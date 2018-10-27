#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

project(usblib C)

file(GLOB static
    *.c
    device/*.c
    host/*.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDMA_MODE")

add_library(usblib EXCLUDE_FROM_ALL ${static})
target_include_directories(usblib PUBLIC
    include
    ${ROOT_PATH}/include
    ${ROOT_PATH}/include/hw
    ${ROOT_PATH}/include/${TARGET}/${DEVICE}
)
