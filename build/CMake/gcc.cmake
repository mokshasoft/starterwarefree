#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

set(CMAKE_SYSTEM_NAME Generic)

# Only needed for TI StarterWare code, not for the CMake toolchain.
set(COMPILER gcc)

if("${CROSS_COMPILER_PREFIX}" STREQUAL "")
    set(CROSS_COMPILER_PREFIX "arm-none-eabi-" CACHE INTERNAL "")
    message(STATUS "Using default value for CROSS_COMPILER_PREFIX (${CROSS_COMPILER_PREFIX})")
endif()

set(CMAKE_C_COMPILER ${CROSS_COMPILER_PREFIX}gcc)
set(CMAKE_LD ${CROSS_COMPILER_PREFIX}gcc)

set(CMAKE_C_FLAGS "\
    -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a \
    -c \
    -mlong-calls -fdata-sections -funsigned-char -ffunction-sections -Wall \
    -Dgcc -D SUPPORT_UNALIGNED -D MMCSD -DUARTCONSOLE -g -O2"
)

set(CMAKE_C_LINK_EXECUTABLE
    "${CMAKE_LD} \
    -e Entry -u Entry \
    -u __aeabi_uidiv -u __aeabi_idiv -u __aeabi_uidivmod \
    -Wl,--gc-sections \
    -Wl,-Map,<TARGET>.map \
    <OBJECTS> \
    -o <TARGET> \
    <LINK_LIBRARIES>"
)

set(ARFLAGS "-c -r")
set(CMAKE_C_ARCHIVE_CREATE "${CROSS_COMPILER_PREFIX}ar ${ARFLAGS} <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "${CROSS_COMPILER_PREFIX}ar ${ARFLAGS} <TARGET> <LINK_FLAGS> <OBJECTS>")

set(BINFLAGS "-O binary")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

mark_as_advanced(FORCE CMAKE_TOOLCHAIN_FILE)

