//1. Write an embedded C program using ADC Channel 6 display the analog voltage equivalent on the LCD
#include <stdio.h>																				
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Seven_Segment.h"
#include "DrvADC.h"
#include "LCD_Driver.h"

int32_t main (void) {  
	uint16_t value;  
  char TEXT[16];			   
	
	UNLOCKREG();
	DrvSYS_Delay(48000000);
	LOCKREG();
	Initial_panel();  // initialize LCD pannel
  clr_all_panel();  // clear LCD panel 
  print_lcd(0,"variable reistor");

	DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x40,INTERNAL_HCLK , 1); 	
	while(1) {
    DrvADC_StartConvert();   // start A/D conversion
    while(DrvADC_IsConversionDone()==FALSE);
    value = ADC->ADDR[6].RSLT & 0xFFF;    
    
    sprintf(TEXT,"Value: %d",value); // convert ADC0 value into text
  	print_lcd(1, TEXT); // output TEXT to LCD
	  }
}