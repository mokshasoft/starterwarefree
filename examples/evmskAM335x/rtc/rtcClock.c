/**
 *  \file   rtcClock.c
 *
 *  \brief  This is a sample application to demonstrate the configuration and
 *          usage of RTC.
 *
 *          Application Configuration:
 *
 *              Modules Used:
 *                  RTC
 *                  UART0
 *                  Interrupt Controller
 *
 *              Configurable parameters(Runtime)
 *                  1) Time Information  - User input
 *                  2) Calendar Information - User input
 *
 *              Hard coded configurations (compile time)
 *                  1) 32KHz Clock Source - Internal Clock source
 *                  2) Meridien Mode - 24 Hour mode
 *                  3) Periodic and ALARM Interrupts - Periodic Interrupt
 *
 *          Application Flow:
 *              The application sequence is as follows:
 *              1) User is asked for time and calendar information
 *              2) They are programmed in RTC registers
 *              3) Timer Interrupts are enabled and RTC interrupts the CPU
 *                 on every second.
 *              4) On every interrupt, the current time and calendar
 *                 information are read and are displayed on the serial console.
 *
 *          Running the example:
 *              1) On execution, the user will be requested to enter time and
 *                 calendar information.
 *
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "evmskAM335x.h"
#include "soc_AM335x.h"
#include "interrupt.h"
#include "consoleUtils.h"
#include "cache.h"
#include "rtc.h"
#include "mmu.h"

/*****************************************************************************
**                 INTERNAL MACRO DEFINITIONS
*****************************************************************************/

#define MASK_HOUR               (0xFF000000u)
#define MASK_MINUTE             (0x00FF0000u)
#define MASK_SECOND             (0x0000FF00u)
#define MASK_MERIDIEM           (0x000000FFu)

#define HOUR_SHIFT              (24u)
#define MINUTE_SHIFT            (16u)
#define SECOND_SHIFT            (8u)

#define MASK_DAY                (0xFF000000u)
#define MASK_MONTH              (0x00FF0000u)
#define MASK_YEAR               (0x0000FF00u)
#define MASK_DOTW               (0x000000FFu)

#define DAY_SHIFT               (24u)
#define MONTH_SHIFT             (16u)
#define YEAR_SHIFT              (8u)

#define RTC_INST_BASE           (SOC_RTC_0_REGS)
#define RTC_INT_NUM             (SYS_INT_RTCINT)

/* Definitions related to MMU Configuration. */
#define START_ADDR_DDR          (0x80000000u)
#define START_ADDR_DEV          (0x44000000u)
#define START_ADDR_OCMC         (0x40300000u)
#define NUM_SECTIONS_DDR        (512u)
#define NUM_SECTIONS_DEV        (960u)
#define NUM_SECTIONS_OCMC       (1u)

/******************************************************************************
**                 INTERNAL FUNCTION PROTOTYPES
******************************************************************************/

static void CalendarResolve(unsigned int calendarValue);
static unsigned int IntToASCII(unsigned char byte);
static void TimeResolve(unsigned int timeValue);
static unsigned int UserCalendarInfoGet(void);
static unsigned int UserTimeInfoGet(void);
static void MMUConfigAndEnable(void);
static void RTCINTCConfigure(void);
static void RTCIsr(void);

/******************************************************************************
**                 INTERNAL VARIABLE DEFINITIONS
******************************************************************************/

/* Page tables start must be aligned in 16K boundary */
#ifdef __TMS470__
#pragma DATA_ALIGN(pageTable, MMU_PAGETABLE_ALIGN_SIZE);
static volatile unsigned int pageTable[MMU_PAGETABLE_NUM_ENTRY];

#elif defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=MMU_PAGETABLE_ALIGN_SIZE
static volatile unsigned int pageTable[MMU_PAGETABLE_NUM_ENTRY];

#elif defined(gcc)
static volatile unsigned int pageTable[MMU_PAGETABLE_NUM_ENTRY]
 __attribute__((aligned(MMU_PAGETABLE_ALIGN_SIZE)));

#else
#error "Unsupported Compiler. \r\n"

#endif

/******************************************************************************
**                 INTERNAL FUNCTION DEFINITIONS
******************************************************************************/

/*
** This function will setup the MMU. The function maps three regions -
** 1. DDR
** 2. OCMC RAM
** 3. Device memory
** The function also enables the MMU.
*/
static void MMUConfigAndEnable(void)
{
    /*
    ** Define DDR memory region of AM335x. DDR can be configured as Normal
    ** memory with R/W access in user/privileged modes. The cache attributes
    ** specified here are,
    ** Inner - Write through, No Write Allocate
    ** Outer - Write Back, Write Allocate
    */
    REGION regionDdr = {
                        MMU_PGTYPE_SECTION, START_ADDR_DDR, NUM_SECTIONS_DDR,
                        MMU_MEMTYPE_NORMAL_NON_SHAREABLE(MMU_CACHE_WT_NOWA,
                                                         MMU_CACHE_WB_WA),
                        MMU_REGION_NON_SECURE, MMU_AP_PRV_RW_USR_RW,
                        (unsigned int*)pageTable
                       };
    /*
    ** Define OCMC RAM region of AM335x. Same Attributes of DDR region given.
    */
    REGION regionOcmc = {
                         MMU_PGTYPE_SECTION, START_ADDR_OCMC, NUM_SECTIONS_OCMC,
                         MMU_MEMTYPE_NORMAL_NON_SHAREABLE(MMU_CACHE_WT_NOWA,
                                                          MMU_CACHE_WB_WA),
                         MMU_REGION_NON_SECURE, MMU_AP_PRV_RW_USR_RW,
                         (unsigned int*)pageTable
                        };

    /*
    ** Define Device Memory Region. The region between OCMC and DDR is
    ** configured as device memory, with R/W access in user/privileged modes.
    ** Also, the region is marked 'Execute Never'.
    */
    REGION regionDev = {
                        MMU_PGTYPE_SECTION, START_ADDR_DEV, NUM_SECTIONS_DEV,
                        MMU_MEMTYPE_DEVICE_SHAREABLE,
                        MMU_REGION_NON_SECURE,
                        MMU_AP_PRV_RW_USR_RW  | MMU_SECTION_EXEC_NEVER,
                        (unsigned int*)pageTable
                       };

    /* Initialize the page table and MMU */
    MMUInit((unsigned int*)pageTable);

    /* Map the defined regions */
    MMUMemRegionMap(&regionDdr);
    MMUMemRegionMap(&regionOcmc);
    MMUMemRegionMap(&regionDev);

    /* Now Safe to enable MMU */
    MMUEnable((unsigned int*)pageTable);
}

/*
** Main function.
*/
int main(void)
{
    unsigned int userCalendar = 0;
    unsigned int userTime = 0;

    /* Configure and enable the MMU. */
    MMUConfigAndEnable();

    /* Enable all levels of Cache. */
    CacheEnable(CACHE_ALL);

    /* Initialize console for communication with the Host Machine */
    ConsoleUtilsInit();

    /* Select the console type based on compile time check */
    ConsoleUtilsSetType(CONSOLE_UART);

    /* Performing the System Clock configuration for RTC. */
    RTCModuleClkConfig();

    /* Disabling Write Protection for RTC registers.*/
    RTCWriteProtectDisable(RTC_INST_BASE);

    /* Selecting Internal Clock source for RTC. */
    RTC32KClkSourceSelect(RTC_INST_BASE, RTC_INTERNAL_CLK_SRC_SELECT);

    /* Enabling RTC to receive the Clock inputs. */
    RTC32KClkClockControl(RTC_INST_BASE, RTC_32KCLK_ENABLE);

    /* Enable the RTC module. */
    RTCEnable(RTC_INST_BASE);

    ConsoleUtilsPrintf("StarterWare AM335x RTC Application.\r\n");

    /* Receiving Time related information from the user. */
    userTime = UserTimeInfoGet();

    /* Receiving Calendar related information from the user. */
    userCalendar = UserCalendarInfoGet();

    /* Programming calendar information in the Calendar registers. */
    RTCCalendarSet(RTC_INST_BASE, userCalendar);

    /* Programming the time information in the Time registers. */
    RTCTimeSet(RTC_INST_BASE, userTime);

    /* Set the 32KHz counter to run. */
    RTCRun(RTC_INST_BASE);

    ConsoleUtilsPrintf("\r\n\r\n");
    ConsoleUtilsPrintf("Current Time And Date:\r\n");

    /* Enabling IRQ in CPSR of ARM processor. */
    IntMasterIRQEnable();

    /* Configure the AINTC to receive RTC interrupts. */
    RTCINTCConfigure();

    /* Enabling RTC interrupts. Configuring RTC to interrupt every second.*/
    RTCIntTimerEnable(RTC_INST_BASE, RTC_INT_EVERY_SECOND);

    while(1);
}

/*
** This function receives time related information from the user.
*/
static unsigned int UserTimeInfoGet()
{
    unsigned int time = 0;
    unsigned int temp = 0;

    ConsoleUtilsPrintf("\n\nEnter the time in 24 hour format.\r\n");
    ConsoleUtilsPrintf("Example (hh:mm:ss) 20:15:09\r\n");

    ConsoleUtilsPrintf("\n\rEnter Hours (0 to 23):");
    ConsoleUtilsScanf("%u", &temp);

    while(temp > 23)
    {
        ConsoleUtilsPrintf("\n\rValue entered is invalid. Enter value:");
        ConsoleUtilsScanf("%u", &temp);
    }

    time = (((temp / 10) << 4) << HOUR_SHIFT)
            | ((temp % 10) << HOUR_SHIFT);

    ConsoleUtilsPrintf("\n\rEnter Minutes (0 to 59):");
    ConsoleUtilsScanf("%u", &temp);

    while(temp > 59)
    {
        ConsoleUtilsPrintf("\n\rValue entered is invalid. Enter value:");
        ConsoleUtilsScanf("%u", &temp);
    }

    time |= (((temp / 10) << 4) << MINUTE_SHIFT)
            | ((temp % 10) << MINUTE_SHIFT);

    ConsoleUtilsPrintf("\n\rEnter Seconds (0 to 59):");
    ConsoleUtilsScanf("%u", &temp);

    while(temp > 59)
    {
        ConsoleUtilsPrintf("\n\rValue entered is invalid. Enter value:");
        ConsoleUtilsScanf("%u", &temp);
    }

    time |= (((temp / 10) << 4) << SECOND_SHIFT)
             | ((temp % 10) << SECOND_SHIFT);

    return time;
}

/*
** This function receives calendar related information from the user.
*/
static unsigned int UserCalendarInfoGet()
{
    unsigned int calender = 0;
    unsigned int temp = 0;

    ConsoleUtilsPrintf("\r\n\r\nEnter the calendar information.\r\n");
    ConsoleUtilsPrintf("Example (DD:MM:YY) 31:03:73\r\n");

    ConsoleUtilsPrintf("\n\rEnter the day of the month(1 to 31):");
    ConsoleUtilsScanf("%u", &temp);

    while((temp > 31) || (0 == temp))
    {
        ConsoleUtilsPrintf("\n\rValue entered is invalid. Enter value:");
        ConsoleUtilsScanf("%u", &temp);
    }

    calender = (((temp / 10) << 4) << DAY_SHIFT)
           | ((temp % 10) << DAY_SHIFT);

    ConsoleUtilsPrintf("\n\rEnter the month (Jan=01 to Dec=12)):");
    ConsoleUtilsScanf("%u", &temp);

    while((temp > 12) || (0 == temp))
    {
        ConsoleUtilsPrintf("\n\rValue entered is invalid. Enter value:");
        ConsoleUtilsScanf("%u", &temp);
    }

    calender |= (((temp / 10) << 4) << MONTH_SHIFT)
            | ((temp % 10) << MONTH_SHIFT);

    ConsoleUtilsPrintf("\n\rEnter the year (0 to 99)(Ex: 2010=10, 1987=87):");
    ConsoleUtilsScanf("%u", &temp);
    while(temp > 99)
    {
        ConsoleUtilsPrintf("\n\rValue entered is invalid. Enter value:");
        ConsoleUtilsScanf("%u", &temp);
    }

    calender |= (((temp / 10) << 4) << YEAR_SHIFT)
            | ((temp % 10) << YEAR_SHIFT);

    ConsoleUtilsPrintf("\n\rEnter Day of the week (Ex:Sun=00 ...  Sat=06):");
    ConsoleUtilsScanf("%u", &temp);

    while(temp > 6)
    {
        ConsoleUtilsPrintf("\n\rValue entered is invalid. Enter value:");
        ConsoleUtilsScanf("%u", &temp);
    }

    calender |= (((temp / 10) << 4)) | ((temp % 10));

    return calender;
}

/*
** This function prints the current time read from the RTC registers.
*/
static void TimeResolve(unsigned int timeValue)
{
    unsigned char timeArray[3] = {0};
    unsigned char bytePrint[2] = {0};
    unsigned int asciiTime = 0;
    unsigned int lIndex = 0;
    unsigned int count = 0;

    /*
    ** The variable 'timeValue' will have the time in the format
    ** <hh:mm:ss:meridiem>. Now, obtaining the individual fields
    ** to facilitate their display.
    */
    timeArray[0] = (unsigned char)((timeValue & MASK_HOUR) >> HOUR_SHIFT);
    timeArray[1] = (unsigned char)((timeValue & MASK_MINUTE) >> MINUTE_SHIFT);
    timeArray[2] = (unsigned char)((timeValue & MASK_SECOND) >> SECOND_SHIFT);

    /* Prints the time in the format: <hh:mm:ss>. */
    while(count < 3)
    {
        lIndex = 0;
        asciiTime = IntToASCII(timeArray[count]);
        bytePrint[0] = (unsigned char)((asciiTime & 0x0000FF00) >> 0x08);
        bytePrint[1] = (unsigned char)(asciiTime & 0x000000FF);
        while(lIndex < 2)
        {
            ConsoleUtilsPrintf("%c", (bytePrint[lIndex]));
            lIndex++;
        }
        count++;
        if(count != 3)
        {
            ConsoleUtilsPrintf("%c", ':');
        }
        else
        {
            ConsoleUtilsPrintf("%c", ' ');
        }
    }
}

/*
** This function prints the calendar information read from the RTC registers.
*/
static void CalendarResolve(unsigned int calendarValue)
{
    unsigned char calendarArray[3] = {0};
    unsigned char dotwString[4] = {0};
    unsigned char bytePrint[2] = {0};
    unsigned int asciiCalendar = 0;
    unsigned int dotwValue = 0;
    unsigned int lIndex = 0;
    unsigned int count = 0;

    /*
    ** The variable 'calendarValue' will have the date in the format
    ** <dd:mm:yy:day of the week>. Now, obtaining the individual fields
    ** to facilitate their display.
    */
    calendarArray[0] = (unsigned char)((calendarValue & MASK_DAY) >> DAY_SHIFT);
    calendarArray[1] = (unsigned char)((calendarValue & MASK_MONTH) >> MONTH_SHIFT);
    calendarArray[2] = (unsigned char)((calendarValue & MASK_YEAR) >> YEAR_SHIFT);

    dotwValue = (calendarValue & MASK_DOTW);

    switch(dotwValue)
    {
        case 0x00:
             dotwString[0] = 'S';
             dotwString[1] = 'u';
             dotwString[2] = 'n';
             dotwString[3] = '\0';
        break;

        case 0x01:
             dotwString[0] = 'M';
             dotwString[1] = 'o';
             dotwString[2] = 'n';
             dotwString[3] = '\0';
        break;

        case 0x02:
             dotwString[0] = 'T';
             dotwString[1] = 'u';
             dotwString[2] = 'e';
             dotwString[3] = '\0';
        break;


        case 0x03:
             dotwString[0] = 'W';
             dotwString[1] = 'e';
             dotwString[2] = 'd';
             dotwString[3] = '\0';
        break;

        case 0x04:
             dotwString[0] = 'T';
             dotwString[1] = 'h';
             dotwString[2] = 'u';
             dotwString[3] = '\0';
        break;

        case 0x05:
             dotwString[0] = 'F';
             dotwString[1] = 'r';
             dotwString[2] = 'i';
             dotwString[3] = '\0';
        break;

        case 0x06:
             dotwString[0] = 'S';
             dotwString[1] = 'a';
             dotwString[2] = 't';
             dotwString[3] = '\0';

        default:
        break;
    }

    /* Prints the date in the format: <dd:mm:yy:day of the week>. */
    while(count < 3)
    {
        lIndex = 0;
        asciiCalendar = IntToASCII(calendarArray[count]);
        bytePrint[0] = (unsigned char)((asciiCalendar & 0x0000FF00) >> 0x08);
        bytePrint[1] = (unsigned char)(asciiCalendar & 0x000000FF);
        while(lIndex < 2)
        {
            ConsoleUtilsPrintf("%c", (bytePrint[lIndex]));
            lIndex++;
        }
        count++;
        if(count != 3)
        {
            ConsoleUtilsPrintf("%c", '/');
        }
        else
        {
            ConsoleUtilsPrintf("%c", ' ');
        }
    }
    ConsoleUtilsPrintf("%s", (char *)dotwString);
}

/*
** This function converts the nibbles of an 8-bit number to their ASCII
** equivalent value. The 8-bit number is passed as a parameter to this
** function.
** For Example, if a number 19 is given to this function, this function
** returns 0x3139. Here, 0x31 is the ASCII value of 1 and 0x39 is the
** ASCII value of 9.
*/
static unsigned int IntToASCII(unsigned char byte)
{
    unsigned char highNibble = 0;
    unsigned char lowNibble = 0;
    unsigned int retVal = 0;

    lowNibble = (byte & 0x0F);
    highNibble = (byte & 0xF0) >> 0x04;

    retVal = (lowNibble + 0x30);
    retVal |= ((highNibble + 0x30) << 0x08);

    return retVal;
}

/*
** This function configures the Interrupt Controller(INTC) to receive
** RTC interrupts.
*/
static void RTCINTCConfigure(void)
{
    /* Initializing the ARM Interrupt Controller. */
    IntAINTCInit();

    /* Registering the Interrupt Service Routine(ISR). */
    IntRegister(RTC_INT_NUM, RTCIsr);

    /* Setting the priority for the system interrupt in AINTC. */
    IntPrioritySet(RTC_INT_NUM, 0, AINTC_HOSTINT_ROUTE_IRQ);

    /* Enabling the system interrupt in AINTC. */
    IntSystemEnable(RTC_INT_NUM);
}

/*
** This is the Interrupt Service Routine(ISR) for RTC.
*/
static void RTCIsr(void)
{
    unsigned int calendarValue = 0;
    unsigned int timeValue = 0;

    /* Read the current time from RTC time registers. */
    timeValue = RTCTimeGet(RTC_INST_BASE);

    /* Decode the time in 'timeValue' and display it on console.*/
    TimeResolve(timeValue);

    /* Read the current date from the RTC calendar registers. */
    calendarValue = RTCCalendarGet(RTC_INST_BASE);

    ConsoleUtilsPrintf("   ");

    /* Decode  the date in 'calendarValue' and display it on console.*/
    CalendarResolve(calendarValue);

    ConsoleUtilsPrintf("\r");
}

/****************************** End of file **********************************/
