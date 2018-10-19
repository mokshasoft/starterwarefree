#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

project(gpioLedBlink C)

set(ROOT "../../../")
set(APPDIR "gpio")

file(GLOB static
    *.c
)

add_executable(gpioLedBlink EXCLUDE_FROM_ALL ${static})
target_link_libraries(
    gpioLedBlink
    drivers
    utils
    platform
    system_config
)
