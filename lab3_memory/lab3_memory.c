#include "msp432.h"
#include "driverlib.h"

#include "string.h"
#include "functions.h"
#include "macros.h"
//#pragma NOINIT(buffer)

//uint32_t buttonPushed = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	Init_Ports();
    //MAP_WDT_A_holdTimer(); // stop watch dog timer

	P1OUT |= BIT0;				// turn red LED on
	delay_1sec();				// wait 1 second
	P1OUT &= ~BIT0;				// turn red LED off
	P2OUT |= BIT1;				// turn green LED on
	delay_1sec();
	P2OUT &= ~BIT1;

    //MAP_Interrupt_enableInterrupt(INT_PORT1);
    //MAP_Interrupt_enableMaster();
    //MAP_Interrupt_disableMaster();

	//NVIC_ISER1 = 1 << ((INT_PORT1 - 16) & 31);
	//__enable_interrupt(); // enable all interrupts

    /* Setting our MCLK to 48MHz for faster programming */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    WDTCTL = WDTPW |WDTSSEL_3|WDTIS_4|WDTCNTCL;		//start WDT counter with a 1 second expiration

    /* Memory test #2: SRAM */
    //TestSRAMBankEnable();

    //![FlashCtl Program]
    while(1){
        /* Memory test #1: Flash */
        EraseFlash();
        ProgramFlash();
    }
}
