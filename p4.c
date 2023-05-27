//Write an embedded C program to blink LED on interrupt from INT0 and buzz on interrupt from INT1
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"

void EINT1Callback(void) {
    DrvGPIO_ClrBit(E_GPB,11); // GPB11 = 0 to turn on Buzzer
		DrvSYS_Delay(10000000000);	    // Delay 
		DrvGPIO_SetBit(E_GPB,11); // GPB11 = 1 to turn off Buzzer	
		DrvSYS_Delay(10);	    // Delay 	
}

void call() {
		DrvGPIO_ClrBit(E_GPC, 12); // output Low to turn on LED
		DrvSYS_Delay(300000);	   // delay 
		DrvGPIO_SetBit(E_GPC, 12); // output Hi to turn off LED
		DrvSYS_Delay(300000);	   // delay
}
void Init_LED() // Initialize GPIO pins
{
	  DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT); // GPC12 pin set to output mode
	  DrvGPIO_SetBit(E_GPC, 12);            // Goutput Hi to turn off LED
}

int main (void) {
		UNLOCKREG();			    // unlock register for programming
  DrvSYS_Delay(48000000);// set System Clock to run at 48MHz 
		                      // 12MHz crystal input, PLL output 48MHz
		LOCKREG();				    // lock register from programming
	  
		DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT);
	  Init_LED();        // Initialize LEDs (four on-board LEDs below LCD panel)
	   DrvGPIO_Open(E_GPB, 14, E_IO_INPUT);                             // configure external interrupt pin GPB15
	  DrvGPIO_EnableEINT0(E_IO_BOTH_EDGE, E_MODE_EDGE,call); // configure external interrupt
	
		 DrvGPIO_Open(E_GPB, 15, E_IO_INPUT);                             // configure external interrupt pin GPB15
	  DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE,EINT1Callback); // configure external interrupt
	
		while (1)				   // forever loop to keep flashing four LEDs one at a time
		{
	  // delay
		}
	
}