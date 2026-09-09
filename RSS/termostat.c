#include <RTL.h>
#include "..\APP\EXTERNALS.h"




void Termostat(void){
U16 adc_data;

		if(ADDR & 0x80000000){		   // Опрос готовности АЦП
		   adc_data = ADDR >>6;		   // ЦНРК АЦП 3.3 mV/квант
		   FlashPage[3] = adc_data;

				 if (adc_data <= 121){	          //  -10 градусов Цельсия (400 mV)
				     IO1SET |= 0x00080000;		  //	ВКЛ термостат
				 }
												  //   0  градусов Цельсия (500 mV)
				 	if (adc_data >= 167){		  //  +5  градусов Цельсия (550 mV)
					    IO1CLR |= 0x00080000;  	  //	ОТКЛ термостат
				 	}

		   ADCR  = 0x0020FF01;
		 }
}
