#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

project(bootloader C)

file(GLOB static
    src/bl_main.c
    src/bl_copy.c
    src/${TARGET}/gcc/*.S
    src/${TARGET}/${DEVICE}/bl_platform.c
    ${ROOT_PATH}/system_config/${TARGET}/cache.c
    ${ROOT_PATH}/system_config/${TARGET}/mmu.c
    ${ROOT_PATH}/system_config/${TARGET}/gcc/cp15.S
    ${ROOT_PATH}/system_config/${TARGET}/${DEVICE}/device.c
)

# Where the bootloader will be loaded to by the ROM code.
# Starting 1Kbyte cannot be used due to hardware limitation.
set(START_ADDR 0x402F0400)

add_library(bootloader EXCLUDE_FROM_ALL ${static})
target_link_libraries(
    bootloader
    drivers
    utils
    platform
    --defsym BOOT_START_ADDR=${START_ADDR}
)
target_include_directories(bootloader PUBLIC
    include
    include/${TARGET}/${DEVICE}
)
