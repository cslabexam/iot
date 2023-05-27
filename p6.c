//6. Write an embedded C program 7 segment counter program to count 0 to 2500
#include <stdio.h>																											 
#include "NUC1xx.h"
#include "DrvSYS.h"
#include "Seven_Segment.h"

// display an integer on four 7-segment LEDs
void seg_display(int16_t value) {
	  int8_t digit;
		digit = value / 1000;
		close_seven_segment();
		show_seven_segment(3,digit);
		DrvSYS_Delay(5000);
			
		value = value - digit * 1000;
		digit = value / 100;
		close_seven_segment();
		show_seven_segment(2,digit);
		DrvSYS_Delay(5000);

		value = value - digit * 100;
		digit = value / 10;
		close_seven_segment();
		show_seven_segment(1,digit);
		DrvSYS_Delay(5000);

		value = value - digit * 10;
		digit = value;
		close_seven_segment();
		show_seven_segment(0,digit);
		DrvSYS_Delay(5000);
}

int32_t main (void) {
	int32_t i = 0;
	
	UNLOCKREG();
  DrvSYS_Delay(48000000);// set System Clock to run at 48MHz 
	LOCKREG();			 	

 	while(i<2500) 	{
	   seg_display(i);		// display i on 7-segment display
	   DrvSYS_Delay(10000);	// delay for keeping display
	   i++;					// increment i
	}
}