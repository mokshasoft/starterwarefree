#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

set(COMPILER "gcc")
message(STATUS "Using the ${COMPILER} compiler")

if(${BUILD_TYPE} STREQUAL release)
    set(Release_FLAG "-g -O2")
    message(STATUS "Building release configuration")
else()
    set(Debug_FLAG "-g")
    message(STATUS "Building debug configuration")
endif()

if(DEVICE)
    set(DEVICE_D "-D${DEVICE}")
endif()

if(EVM)
    set(EVM_D "-D${EVM}")
endif()

if(NOT CROSS_COMPILER_PREFIX)
    set(CROSS_COMPILER_PREFIX "arm-none-eabi-")
    message(STATUS "Using default value for CROSS_COMPILER_PREFIX (${CROSS_COMPILER_PREFIX})")
endif()

set(CC "${CROSS_COMPILER_PREFIX}gcc")
set(LD "${CROSS_COMPILER_PREFIX}ld")
set(AR "${CROSS_COMPILER_PREFIX}ar")
set(BIN "${CROSS_COMPILER_PREFIX}objcopy")

set(CFLAGS "-mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a")
set(CFLAGS "${CFLAGS}
    -c ${${TARGET_MODE}_FLAG} \
    -mlong-calls -fdata-sections -funsigned-char \
    -ffunction-sections -Wall ${IPATH} -Dgcc ${DEVICE_D} ${EVM_D} \
    -D SUPPORT_UNALIGNED -D ${BOOT} -D${CONSOLE}"
)
set(ARFLAGS "-c -r")
set(LDFLAGS "-e Entry -u Entry -u __aeabi_uidiv -u __aeabi_idiv --gc-sections")
set(BINFLAGS "-O binary")
