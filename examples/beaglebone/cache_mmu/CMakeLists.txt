#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

set(APP cache_mmu)
project(${APP} C)

file(GLOB static
    *.c
)

add_executable(${APP} EXCLUDE_FROM_ALL ${static})
target_link_libraries(
    ${APP}
    drivers
    utils
    platform
    system_config
    -T ${ROOT_PATH}/build/beaglebone.lds
)
gen_bin(${APP})
