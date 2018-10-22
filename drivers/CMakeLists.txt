#
# Copyright 2018, Mokshasoft AB (mokshasoft.com)
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#

cmake_minimum_required(VERSION 3.7.2)

project(drivers C)

# All drivers does currently not build
file(GLOB static
    #cppi41dma.c
    cpsw.c
    dcan.c
    dmtimer.c
    ecap.c
    #edma.c
    #ehrpwm.c
    elm.c
    gpio_v2.c
    gpmc.c
    hsi2c.c
    hs_mmcsd.c
    mailbox.c
    #mcasp.c
    mcspi.c
    mdio.c
    phy.c
    pruss.c
    raster.c
    rtc.c
    tsc_adc.c
    uart_irda_cir.c
    #usb.c
    #usbphyGS70.c
    watchdog.c
)

add_library(drivers EXCLUDE_FROM_ALL ${static})
target_include_directories(drivers PUBLIC
    ${ROOT_PATH}/include
    ${ROOT_PATH}/include/hw
)
