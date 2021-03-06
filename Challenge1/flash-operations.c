/*
 * flash-operations.c
 *
 *  Created on: Feb 5, 2016
 *      Author: Steffon Brigman
 */
#include "msp432.h"
#include "driverlib.h"

#include "string.h"
#include "macros.h"
#include "functions.h"

void ProgramFlash(void)
{
	int memory_location = BUFFER_MEMORY_START;
	int sectorCount = 0;
	 uint8_t buffer[4096];
	/* Initializing our buffer to a pattern of 0xA5 */
	memset(buffer, 0xA5, 4096);
	//![FlashCtl Program]
	/* Unprotecting Info Bank 0, Sector 0  */

	/* Set breakpoint here to check memory @ 0x000200000 before erase */
	__no_operation();

MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,
FLASH_SECTOR0 | FLASH_SECTOR1 | FLASH_SECTOR2 | FLASH_SECTOR3 | FLASH_SECTOR4 | FLASH_SECTOR5 | FLASH_SECTOR6 | FLASH_SECTOR7 |
FLASH_SECTOR8 | FLASH_SECTOR9 | FLASH_SECTOR10 | FLASH_SECTOR11 | FLASH_SECTOR12 | FLASH_SECTOR13 | FLASH_SECTOR14 | FLASH_SECTOR15 |
FLASH_SECTOR16 | FLASH_SECTOR17 | FLASH_SECTOR18 | FLASH_SECTOR19 | FLASH_SECTOR20 | FLASH_SECTOR21 | FLASH_SECTOR22 | FLASH_SECTOR23 |
FLASH_SECTOR24 | FLASH_SECTOR25 | FLASH_SECTOR26 | FLASH_SECTOR27 | FLASH_SECTOR28 | FLASH_SECTOR29 | FLASH_SECTOR30 | FLASH_SECTOR31);

	/* Program the sector with the new data. */
	while(sectorCount < 32){
		MAP_WDT_A_clearTimer();
		while (!MAP_FlashCtl_programMemory(buffer,(void*) memory_location, 4096 ));

		while(!(P1IN & BIT4)){
			P1OUT |= BIT0;				// turn red LED on
			delay_1sec();				// wait 1 second
			P1OUT &= ~BIT0;				// turn red LED off
			WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
			WDTCTL = WDTPW |WDTSSEL_3|WDTIS_4|WDTCNTCL;		//start WDT counter with a 1 second expiration
		}

		memory_location += 4096;
		sectorCount++;
		MAP_WDT_A_clearTimer();
	}

	/* Setting the sector back to protected  */
MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR0 | FLASH_SECTOR1 | FLASH_SECTOR2 | FLASH_SECTOR3 | FLASH_SECTOR4 |
FLASH_SECTOR5 | FLASH_SECTOR6 | FLASH_SECTOR7 | FLASH_SECTOR8 | FLASH_SECTOR9 | FLASH_SECTOR10 | FLASH_SECTOR11 | FLASH_SECTOR12 |
FLASH_SECTOR13 | FLASH_SECTOR14 | FLASH_SECTOR15 | FLASH_SECTOR16 | FLASH_SECTOR17 | FLASH_SECTOR18 | FLASH_SECTOR19 | FLASH_SECTOR20 |
FLASH_SECTOR21 | FLASH_SECTOR22 | FLASH_SECTOR23 | FLASH_SECTOR24 | FLASH_SECTOR25 | FLASH_SECTOR26 | FLASH_SECTOR27 | FLASH_SECTOR28 |
FLASH_SECTOR29 | FLASH_SECTOR30 | FLASH_SECTOR31);

	/* Set breakpoint here to check memory @ 0x000200000 after programming*/
	__no_operation();

	P2OUT |= BIT1;				// turn green LED on
	delay_1sec();
	MAP_WDT_A_clearTimer();
	P2OUT &= ~BIT1;
}

void EraseFlash(void){
	uint8_t buffer[4096];
	/* Initializing our buffer to a pattern of 0xA5 */
	memset(buffer, 0xA5, 4096);
	//![FlashCtl Program]
	/* Unprotecting Info Bank 0, Sector 0  */

	/* Set breakpoint here to check memory @ 0x000200000 before erase */
	__no_operation();

MAP_FlashCtl_unprotectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR0 | FLASH_SECTOR1 | FLASH_SECTOR2 | FLASH_SECTOR3 | FLASH_SECTOR4 |
FLASH_SECTOR5 | FLASH_SECTOR6 | FLASH_SECTOR7 | FLASH_SECTOR8 | FLASH_SECTOR9 | FLASH_SECTOR10 | FLASH_SECTOR11 | FLASH_SECTOR12 |
FLASH_SECTOR13 | FLASH_SECTOR14 | FLASH_SECTOR15 | FLASH_SECTOR16 | FLASH_SECTOR17 | FLASH_SECTOR18 | FLASH_SECTOR19 | FLASH_SECTOR20 |
FLASH_SECTOR21 | FLASH_SECTOR22 | FLASH_SECTOR23 | FLASH_SECTOR24 | FLASH_SECTOR25 | FLASH_SECTOR26 | FLASH_SECTOR27 | FLASH_SECTOR28 |
FLASH_SECTOR29 | FLASH_SECTOR30 | FLASH_SECTOR31);

	/* Erase the flash sector starting BUFFER_MEMORY_START.  */
	//while(!MAP_FlashCtl_performMassErase());
	while(!MAP_FlashCtl_performMassErase());

	/* Set breakpoint here to check memory @ 0x000200000 after erase */
			__no_operation();

	/* Setting the sector back to protected  */
MAP_FlashCtl_protectSector(FLASH_MAIN_MEMORY_SPACE_BANK1,FLASH_SECTOR0 | FLASH_SECTOR1 | FLASH_SECTOR2 | FLASH_SECTOR3 | FLASH_SECTOR4 |
FLASH_SECTOR5 | FLASH_SECTOR6 | FLASH_SECTOR7 | FLASH_SECTOR8 | FLASH_SECTOR9 | FLASH_SECTOR10 | FLASH_SECTOR11 | FLASH_SECTOR12 |
FLASH_SECTOR13 | FLASH_SECTOR14 | FLASH_SECTOR15 | FLASH_SECTOR16 | FLASH_SECTOR17 | FLASH_SECTOR18 | FLASH_SECTOR19 | FLASH_SECTOR20 |
FLASH_SECTOR21 | FLASH_SECTOR22 | FLASH_SECTOR23 | FLASH_SECTOR24 | FLASH_SECTOR25 | FLASH_SECTOR26 | FLASH_SECTOR27 | FLASH_SECTOR28 |
FLASH_SECTOR29 | FLASH_SECTOR30 | FLASH_SECTOR31);

	/* Set breakpoint here to check memory @ 0x000200000 after programming*/
	__no_operation();

}

void TestSRAMBankEnable(void)
{
    uint32_t i;

    /* Test #1 */
    /* Write & read back from an SRAM memory location in bank 7*/
    while (!(SYSCTL_SRAM_BANKEN & SYSCTL_SRAM_BANKEN_SRAM_RDY));
    SysCtl_enableSRAMBank(SYSCTL_SRAM_BANK7);
    while (!(SYSCTL_SRAM_BANKEN & SYSCTL_SRAM_BANKEN_SRAM_RDY));

    /* Checking for valid read & write access to memory address
     * located in SRAM bank 7
     */

    * ( (uint32_t*) 0x2000EFFC) = 0xDEADBEEF;
    i = * ( (uint32_t*) 0x2000EFFC);
    if (i== 0xDEADBEEF)
    {
        /* Set breakpoint here, or watch for the pulsing LED*/
        P1DIR |= BIT0;
        P1OUT |= BIT0;
        for (i=0;i<100000;i++);
        P1OUT &= ~BIT0;
    }
    else
        while(1);

    /* Test #2 */
    /* After disabling SRAM banks, Write/access should have invalid results */

    /* Disable SRAM Banks # 4 to 7 */
    while (!(SYSCTL_SRAM_BANKEN & SYSCTL_SRAM_BANKEN_SRAM_RDY));
    SysCtl_disableSRAMBank(SYSCTL_SRAM_BANK4);
    while (!(SYSCTL_SRAM_BANKEN & SYSCTL_SRAM_BANKEN_SRAM_RDY));

    /* Confirming invalid read & write access to memory address
    * located in SRAM bank 7
    */

    * ( (uint32_t*) 0x2000EFFC) = 0xDEADBEEF;
    i = * ( (uint32_t*) 0x2000EFFC);
    if (i!= 0)
    {
        /* Set breakpoint here, or watch for the pulsing LED*/
        P1DIR |= BIT0;
        P1OUT |= BIT0;
        for (i=0;i<100000;i++);
        P1OUT &= ~BIT0;
    }
    else
        while(1);

}


