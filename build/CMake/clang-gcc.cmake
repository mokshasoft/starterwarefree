#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

set(CMAKE_SYSTEM_NAME Generic)

# Only needed for TI StarterWare code, not for the CMake toolchain.
set(COMPILER gcc) # hopefully clang can compile the gcc code..

if("${CROSS_COMPILER_PREFIX}" STREQUAL "")
    set(CROSS_COMPILER_PREFIX "arm-none-eabi" CACHE INTERNAL "")
    message(STATUS "Using default value for CROSS_COMPILER_PREFIX (${CROSS_COMPILER_PREFIX})")
endif()

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${CROSS_COMPILER_PREFIX})
include_directories(/usr/${CROSS_COMPILER_PREFIX}/include)
set(CMAKE_LD ${CROSS_COMPILER_PREFIX}-ld)

set(CMAKE_C_FLAGS "\
    -mcpu=cortex-a8 -mtune=cortex-a8 -march=armv7-a \
    -c \
    -mlong-calls -fdata-sections -funsigned-char -ffunction-sections -Wall \
    -Dgcc -D SUPPORT_UNALIGNED -D MMCSD -DUARTCONSOLE -g -O2"
)

# Find the path to GCC's libc.a and libgcc.a
execute_process(
    COMMAND ${CROSS_COMPILER_PREFIX}-gcc -print-file-name=libc.a
    OUTPUT_VARIABLE LIB_C_FILE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${CROSS_COMPILER_PREFIX}-gcc -print-file-name=libgcc.a
    OUTPUT_VARIABLE LIB_GCC_FILE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
get_filename_component(LIB_C_PATH ${LIB_C_FILE} DIRECTORY)
get_filename_component(LIB_GCC_PATH ${LIB_GCC_FILE} DIRECTORY)

set(CMAKE_C_LINK_EXECUTABLE
    "${CMAKE_LD} \
    -e Entry -u Entry -u __aeabi_uidiv -u __aeabi_idiv --gc-sections \
    -lc -lgcc -L ${LIB_GCC_PATH} -L ${LIB_C_PATH} \
    <OBJECTS> \
    -Map <TARGET>.map \
    -o <TARGET> \
    <LINK_LIBRARIES>"
)

set(ARFLAGS "-c -r")
set(CMAKE_C_ARCHIVE_CREATE "${CROSS_COMPILER_PREFIX}-ar ${ARFLAGS} <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "${CROSS_COMPILER_PREFIX}-ar ${ARFLAGS} <TARGET> <LINK_FLAGS> <OBJECTS>")

set(BINFLAGS "-O binary")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

mark_as_advanced(FORCE CMAKE_TOOLCHAIN_FILE)
