#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

set(CMAKE_SYSTEM_NAME Generic)

if("${CROSS_COMPILER_PREFIX}" STREQUAL "")
    set(CROSS_COMPILER_PREFIX "arm-none-eabi-" CACHE INTERNAL "")
    message(STATUS "Using default value for CROSS_COMPILER_PREFIX (${CROSS_COMPILER_PREFIX})")
endif()

set(CMAKE_C_COMPILER ${CROSS_COMPILER_PREFIX}gcc)

set(CMAKE_C_FLAGS "-mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
    -c \
    -mlong-calls -fdata-sections -funsigned-char \
    -ffunction-sections -Wall -Dgcc \
    -D SUPPORT_UNALIGNED"
)
set(ARFLAGS "-c -r")
set(CMAKE_EXE_LINKER_FLAGS "-e Entry -u Entry -u __aeabi_uidiv -u __aeabi_idiv --gc-sections")
set(BINFLAGS "-O binary")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

mark_as_advanced(FORCE CMAKE_TOOLCHAIN_FILE)

