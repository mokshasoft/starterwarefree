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
    cache_mmu
    #demo
    dmtimer
    edma
    #enet_echo
    #enet_lwip
    gpio
    hsi2c_eeprom
    hsi2c_eeprom_edma
    #hs_mmcsd
    irq_preemption
    #neonVFPBenchmark
    rtc
    uart
    uart_edma
    usb_dev_bulk
    usb_dev_comp_ser_ser
    #usb_device_host_msc
    #usb_dev_msc
    #usb_dev_serial
    #usb_host_msc
    watchdogTimer
)

# Add each app subdirectory
foreach(APP ${APPS})
    add_subdirectory(${APP})
endforeach()

# Apps that currently don't build
add_subdirectory(demo)
add_subdirectory(enet_echo)
add_subdirectory(enet_lwip)
add_subdirectory(hs_mmcsd)
add_subdirectory(neonVFPBenchmark)
add_subdirectory(usb_device_host_msc)
add_subdirectory(usb_dev_msc)
add_subdirectory(usb_dev_serial)
add_subdirectory(usb_host_msc)

# Add a target to build all apps
add_custom_target(beaglebone DEPENDS ${APPS})
