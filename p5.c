//5. Write an embedded C program to display a string on LCD On interrupt.
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "NUC1xx-LB_002\LCD_Driver.h"

void call() {
		print_lcd(0, "Smpl_LCD_Text   ");	  
		print_lcd(1, "Nu-LB-NUC140    ");
		print_lcd(2, "Test LCD Display");
		print_lcd(3, "Nuvoton NuMicro ");  
}

int main(void) {
		UNLOCKREG();
  DrvSYS_Delay(48000000);// set System Clock to run at 48MHz 
		LOCKREG(); 
	
		Initial_panel(); 
		clr_all_panel();
		
		DrvGPIO_Open(E_GPB, 15, E_IO_INPUT);    // configure external interrupt pin GPB15
	  DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE, call); // configure external interrupt
	
	  while(1)
		{

	  }
}