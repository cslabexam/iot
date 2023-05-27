//3. Write an embedded C program Using on board interrupt B15 blink LED A12 on interrupt
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"

void call() {
		DrvGPIO_ClrBit(E_GPA, 12); // output Low to turn on LED
		DrvSYS_Delay(300000);	   // delay 
		DrvGPIO_SetBit(E_GPA, 12); // output Hi to turn off LED
		DrvSYS_Delay(300000);	   // delay
}
void Init_LED() // Initialize GPIO pins
{
		DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT); // GPC12 pin set to output mode
		DrvGPIO_SetBit(E_GPA, 12);            // Goutput Hi to turn off LED
}

int main (void) {
	UNLOCKREG();			    // unlock register for programming
  DrvSYS_Delay(48000000);// set System Clock to run at 48MHz 
	                      // 12MHz crystal input, PLL output 48MHz
	LOCKREG();				    // lock register from programming

  Init_LED();        // Initialize LEDs (four on-board LEDs below LCD panel)
   DrvGPIO_Open(E_GPB, 15, E_IO_INPUT);                             // configure external interrupt pin GPB15
  DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE,call); // configure external interrupt
	while (1)				   // forever loop to keep flashing four LEDs one at a time
	{
  // delay
	}

}