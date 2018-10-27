#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

# List all BeagleBone example apps
set(APPS
    gpio
    uart
)

# Add each app subdirectory
foreach(APP ${APPS})
    add_subdirectory(${APP})
endforeach()

# Add a target to build all apps
add_custom_target(beaglebone DEPENDS ${APPS})
