# IoT Lab | SEE 2023

Suhas Katrahalli

v1.1

Setup Videos

https://drive.google.com/drive/folders/1pP-vNcaFCnKrKXAj5biwPDNc2UTnoAFu?usp=share_link

- **Student is required to solve two programs**
- **Student is required to demonstrate and present their project work.**

<aside>
💡 1. Write an embedded C program using ADC Channel 6 display the analog voltage equivalent on the LCD

</aside>

```c
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
```

---

<aside>
💡 2. Write an embedded C program toggle LED at port C 12 to C 15 sequentially  on interrupt at port B15

</aside>

```c
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"

void call() {
		DrvGPIO_ClrBit(E_GPC, 12); // output Low to turn on LED
		DrvSYS_Delay(300000);	   // delay 
		DrvGPIO_SetBit(E_GPC, 12); // output Hi to turn off LED
		DrvSYS_Delay(300000);	   // delay
		DrvGPIO_ClrBit(E_GPC, 13); // output Low to turn on LED
		DrvSYS_Delay(300000);	   // delay 
		DrvGPIO_SetBit(E_GPC, 13); // output Hi to turn off LED
		DrvSYS_Delay(300000);	   // delay
		DrvGPIO_ClrBit(E_GPC, 14); // output Low to turn on LED
		DrvSYS_Delay(300000);	   // delay 
		DrvGPIO_SetBit(E_GPC, 14); // output Hi to turn off LED
		DrvSYS_Delay(300000);	   // delay
		DrvGPIO_ClrBit(E_GPC, 15); // output Low to turn on LED
		DrvSYS_Delay(300000);	   // delay 
		DrvGPIO_SetBit(E_GPC, 15); // output Hi to turn off LED
		DrvSYS_Delay(300000);	   // delay
}
void Init_LED() // Initialize GPIO pins
{
	  DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT); // GPC12 pin set to output mode
		DrvGPIO_SetBit(E_GPC, 12);            // Goutput Hi to turn off LED
		DrvGPIO_Open(E_GPC, 13, E_IO_OUTPUT); // GPC12 pin set to output mode
		DrvGPIO_SetBit(E_GPC, 13);            // Goutput Hi to turn off LED
		DrvGPIO_Open(E_GPC, 14, E_IO_OUTPUT); // GPC12 pin set to output mode
		DrvGPIO_SetBit(E_GPC, 14);            // Goutput Hi to turn off LED
		DrvGPIO_Open(E_GPC, 15, E_IO_OUTPUT); // GPC12 pin set to output mode
		DrvGPIO_SetBit(E_GPC, 15);            // Goutput Hi to turn off LED
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
```

---

<aside>
💡 3. Write an embedded C program Using on board interrupt B15 blink LED A12 on interrupt

</aside>

```c
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
```

---

<aside>
💡 4. Write an embedded C program to blink LED on interrupt from INT0 and buzz on interrupt from INT1

</aside>

```c
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
```

---

<aside>
💡 5. Write an embedded C program to display a string on LCD On interrupt.

</aside>

```c
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
```

---

<aside>
💡 6. Write an embedded C program 7 segment counter program to count 0 to 2500

</aside>

```c
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
```

---

<aside>
💡 7. Write a python program using Raspberry Pi blink led GPIO  using  SSh

</aside>

```python
from gpiozero import LED
from signal import pause

led=LED(4)
led.blink()

pause()
```

---

<aside>
💡 8. Write an embedded C program using INTO and INT1 interrupt routine light led A12 and C12 respectively

</aside>

```c
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"

void EINT1Callback(void) {
	 	DrvGPIO_ClrBit(E_GPA, 12); // output Low to turn on LED
		DrvSYS_Delay(300000);	   // delay 
		DrvGPIO_SetBit(E_GPA, 12); // output Hi to turn off LED
		DrvSYS_Delay(300000);	   
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
		DrvGPIO_SetBit(E_GPC, 12);  
	 DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT); // GPC12 pin set to output mode
		DrvGPIO_SetBit(E_GPA, 12); 	// Goutput Hi to turn off LED
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
```

---

<aside>
💡 9. Write a python program using Raspberry Pi  Key pressed  and using   SSh

</aside>

```python
from gpiozero import Button
from signal import pause

button = Button(4)

def button_pressed():
  print("Button was pressed")

def button_held():
  print("Button was held")

def button_released():
  print("Button was released")

button.when_pressed = button_pressed
button.when_held = button_held
button.when_released = button_released

pause()
```

---

<aside>
💡 10. Write an embedded C program using generic interrupt handler increment counter on sensing interrupt signal at A port 14 pin and buzzing for 2 sec when interrupt  is sensed at  E port pin 10

</aside>

```c
// smpl_GPIO_Interrupt
//
// GPA15 to input interrupt
// GPD15 to input interrupt

#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvUART.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
#include "LCD_Driver.h"

volatile int A = 0;
volatile int E = 0;

void EINT1Callback(void) {
	  DrvGPIO_ClrBit(E_GPB,11); // GPB11 = 0 to turn on Buzzer
		DrvSYS_Delay(10000000000);	    // Delay 
		DrvGPIO_SetBit(E_GPB,11); // GPB11 = 1 to turn off Buzzer	
		DrvSYS_Delay(10);	    // Delay 	
}

void ab(int a, int b) {
	 if ((a>>14) & 0x01) A++;
	 print_lcd(3,"GPA interrupt !!");
}

void cde(int c, int d, int e) {  
	 if ((e>>15) & 0x01) EINT1Callback();E++;
	//print_lcd(3,"GPC interrupt !!");
}

int32_t main() {
		char TEXT[16];

		UNLOCKREG();
  DrvSYS_Delay(48000000);// set System Clock to run at 48MHz 
    LOCKREG();
	

	  // setup GPA15 & GPD15 to get interrupt input
		DrvGPIO_Open(E_GPA,14,E_IO_INPUT);
		DrvGPIO_Open(E_GPE,15,E_IO_INPUT);
		//DrvGPIO_Open(E_GPE, 15, E_IO_OUTPUT);
	  DrvGPIO_EnableInt(E_GPA, 14, E_IO_RISING, E_MODE_EDGE);
	  DrvGPIO_EnableInt(E_GPE, 15, E_IO_RISING, E_MODE_EDGE);
	  DrvGPIO_SetDebounceTime(5, 1);
		DrvGPIO_EnableDebounce(E_GPA, 14);
		DrvGPIO_EnableDebounce(E_GPE, 15);	
		DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT);
	  DrvGPIO_SetIntCallback(ab, cde);
	
	  Initial_panel();
		clr_all_panel();
	    				
		print_lcd(0,"Smpl_GPIO_Intr");
		
		while(1) 		{
			sprintf(TEXT,"IRQ_A: %d",A);
			print_lcd(1, TEXT);
			sprintf(TEXT,"IRQ_E: %d",E);
			print_lcd(2, TEXT);
		}
}
```

---

<aside>
💡 11. Write an embedded C program using get port identify port bit. As A0, A1,A2, A3

</aside>

```c
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "NUC1xx-LB_002\LCD_Driver.h"

int main (void) {
		int32_t number;
		char TEXT0[16]="SmplKeypad";
		char TEXT1[16];
		UNLOCKREG();			    // unlock register for programming
  DrvSYS_Delay(48000000);// set System Clock to run at 48MHz 
		LOCKREG();				    // lock register from programming
		        // Initialize LEDs (four on-board LEDs below LCD panel)	
		Initial_panel(); 
		clr_all_panel();	    
		print_lcd(0,TEXT0); // print title	
		while (1)				   // forever loop to keep flashing four LEDs one at a time
		{
				number=DrvGPIO_GetPortBits(E_GPA);			
				sprintf(TEXT1,"%x",number); // print scankey input to string			  
				print_lcd(1,TEXT1); 
				if(number==0xfffe)
						print_lcd(2,"A0");	
				else if(number==0xfffd)
						print_lcd(2,"A1");
				else if(number==0xfffb)
						print_lcd(2,"A2");
				else if(number==0xfff7)
						print_lcd(2,"A3");
		}
		
	}
```

---

<aside>
💡 12. Write an embedded C program with a PWM program vary intensity of led A12.  With a delay loop

</aside>

```c
#include <stdio.h>
#include "NUC1xx.h"
#include "LCD_Driver.h"

void Delay(int count) {
	while(count--) {
//		__NOP;
	 }
}

int32_t main (void) {
		//Enable 12Mhz and set HCLK->12Mhz
		char adc_value[15]="ADC Value:";	
		UNLOCKREG();
	  DrvSYS_Delay(48000000);// set System Clock to run at 48MHz 
		LOCKREG();
	
		InitPWM();
		InitADC();
	
		Initial_panel();  //call initial pannel function
		clr_all_panel();
								 	
		/* Synch field transmission & Request Identifier Field transmission*/
						 
		while(1) {
			while(ADC->ADSR.ADF==0);
			ADC->ADSR.ADF=1;
			PWMA->CMR0=ADC->ADDR[7].RSLT<<4;
			/*Show_Word(0,11,' ');
			Show_Word(0,12,' ');
			Show_Word(0,13,' ');
			sprintf(adc_value+4,"%d",ADC->ADDR[7].RSLT);
			print_lcd(0, adc_value);*///we can remove this in exam
			Delay(20000);
			ADC->ADCR.ADST=1;
		}
}
```

---

<aside>
💡 13. Write a python program using Raspberry Pi motion detector  using SSh

</aside>
