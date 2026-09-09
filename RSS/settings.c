//=======================================================================
//		 FlashPage[3]		 Температура в термостате 
//		 FlashPage[7]		 MAC адрес
//		 FlashPage[13]		 скорость UART для GPS
//		 FlashPage[14]		 протокол обмена для GPS
//		 FlashPage[15]		 частота выдачи
//		 FlashPage[16]		 усиление АЦП
//		 FlashPage[17]		 накопление
//		 FlashPage[18]		 фильтрация
//		 FlashPage[19]		 удалённый порт
//		 FlashPage[20]		 удалённый IP
//		 FlashPage[21]		 адрес IP
//
//		 FlashPage[22]		 Имя станции
//		 FlashPage[23]
//
//		 FlashPage[24]		 ЦНРК емкостной калибровочный
//		 FlashPage[25]			  X
//
//		 FlashPage[26]			  Y
//		 FlashPage[27]
//
//		 FlashPage[28]			  Z
//		 FlashPage[29]
//
//		 FlashPage[30]		 ЦНРК резистивный калибровочный
//		 FlashPage[31]			  X
//
//		 FlashPage[32]			  Y
//		 FlashPage[33]
//
//		 FlashPage[34]			  Z
//		 FlashPage[35]

//		 FlashPage[36]		 ЦНРК измерительный
//		 FlashPage[37]			  X
//
//		 FlashPage[38]			  Y
//		 FlashPage[39]
//
//		 FlashPage[40]			  Z
//		 FlashPage[41]

//		 FlashPage[42]		 ЦНРК регистратора
//		 FlashPage[43]			  X
//
//		 FlashPage[44]			  Y
//		 FlashPage[45]
//
//		 FlashPage[46]			  Z
//		 FlashPage[47]
//
//		 FlashPage[59]		 Выбор коэффициента дополнительногo усиления АЦП
//
//		 FlashPage[60]		 чётность UART для GPS
//		 FlashPage[61]		 стоповые биты UART для GPS


#include <LPC22XX.H>
#include <string.h>
#include <RTL.h>
#include "..\APP\EXTERNALS.h"


extern U8   txt[];
extern U8   lcd_text[15][8+1];
extern U8   request_frame [];
extern U8	header_frame[];


void Init_Set(void){
 
//U8 i;
   	
//========= Установка параметров UART1 для GPS/ГЛОНАСС ===========
   
	

	if (FlashPage[14] != 0) PiState = FlashPage[14];
  	else PiState = '1';	                               // По умолчанию протокол обмена NMEA;

		  set_protokol();

	if (FlashPage[13] != 0) PickState = FlashPage[13];
  	else PickState = '1';	                           // По умолчанию скорость - 4800;

//		  set_bod_rate();

	if (FlashPage[60] != 0) PickStateQ = FlashPage[60];
  	else PickStateQ = '3';	                           // По умолчанию Чётность - Нет;

//		  set_bod_rate();

	if (FlashPage[61] != 0) PiStateS = FlashPage[61];
  	else PiStateS = '1';	                               // По умолчанию стоповых бит - 1;

		  set_bod_rate();






//==============================================================================
	if (FlashPage[17] != 0) ParState = FlashPage[17];
  	else ParState = '1';	                           // По умолчанию накопление 1 с;

		  set_time_mem();

	if (FlashPage[15] != 0) ParamState = FlashPage[15];
  	else ParamState = '9';	                           // По умолчанию частота выдачи 40 Гц;

		  set_data_parametr();
//		  set_data_rate();
	
	if (FlashPage[16] != 0) PState = FlashPage[16];
  	else PState = '1';	                               // По умолчанию усиление АЦП = 1;

		  set_ampl();

//	if (FlashPage[59] != 0) PSDtate = FlashPage[59];
//  	else PSDtate = '1';	                           // По умолчанию коэффициент 
													  //  дополнительногo усиления АЦП = 1;
//		  set_ampl_d();

	if (FlashPage[18] != 0) PaState = FlashPage[18];
  	else PaState = '1';	                               // По умолчанию фильтрации нет;

		  set_filtr();

//		  init_info();


//================== Network Settings =============================
		 // Адрес регистратора //
	if (FlashPage[21] != 0){
	   memcpy(&LocM.IpAdr[0],&FlashPage[21],4);
	 }

  	else {
		 LocM.IpAdr[0]=	10;			                  // По умолчанию адрес IP 10.22.0.2
		 LocM.IpAdr[1]=	22;
		 LocM.IpAdr[2]=	0;
		 LocM.IpAdr[3]=	2;
	     }

		 // MAC Адрес регистратора //

	if (FlashPage[7] != 0){
	   memcpy(&own_hw_adr[0],&FlashPage[7],6);
	}

	else{
		MAC_LEAST    = 0x02030419;                  // MAC адрес 0..3 байты
		MAC_MOST     = 0x00000000 | (0) | (2<<8);   // MAC адрес 4..5 байты
	    }
//------------------------------------------------------------------------------
		 // Адрес удалённого узла //

	if (FlashPage[19] != 0) PORT_NUM = FlashPage[19];
  	else PORT_NUM = 8500;	                          // По умолчанию удалённый порт 8500

	if (FlashPage[20] != 0){
	   memcpy(&Rem_IP[0],&FlashPage[20],4);
	 }

  	else {
		 Rem_IP[0]=	10;			                     // По умолчанию удалённый IP 10.0.0.7
		 Rem_IP[1]=	0;
		 Rem_IP[2]=	0;
		 Rem_IP[3]=	7;
	     }

	  exchange_paket();

   }



//------------------------------------
// Установка частоты дискретизации АЦП 
//-----------------------------------
void set_data_parametr(void){

			delta_data_rate =	0.0;

	 switch (ParamState) {
				 case '1':
         				  data_rate = 1;
         		 break;
				 case '2':
         				  data_rate = 2;
         		 break;
				 case '3':
         				  data_rate = 5;
         		 break;
				 case '4':
         				  data_rate = 10;
         		 break;
				 case '5':
         				  data_rate = 15;
         		 break;
				 case '6':
         				  data_rate = 20;
         		 break;
				 case '7':
         				  data_rate = 25;
						  delta_data_rate =	3.0;
         		 break;
				 case '8':
         				  data_rate = 30;
         		 break;
				 case '9':
         				  data_rate = 40;
						  delta_data_rate =	0.2;
         		 break;
				 case 'a':
         				  data_rate = 50;
         		 break;
				 case 'b':
         				  data_rate = 60;
         		 break;
				 case 'c':
         				  data_rate = 80;
						  delta_data_rate =	1.2;
         		 break;
				 case 'd':
         				  data_rate = 100;
         		 break;
				 case 'e':
         				  data_rate = 200;
         		 break;
				 case 'f':
         				  data_rate = 300;
         		 break;
//				 case 'g':
//         				  data_rate = 400;
//         		 break;

			   		
			   }
		}

 

//------------------------------------
// Установка усиления АЦП 
//-----------------------------------
void set_ampl(void){
	switch (PState) {
				 case '1':
         				  ADCON = 0x00;	    //1
						  NPK = 1;		 // ДЛЯ Проверки алгоритма восстановления пакета
         		 break;
				 case '2':
         				  ADCON = 0x01;	    //2
						  NPK = 2;		 // ДЛЯ Проверки алгоритма восстановления пакета
         		 break;
				 case '3':
         				  ADCON = 0x02;		//4
						  NPK = 3;		 // ДЛЯ Проверки алгоритма восстановления пакета
         		 break;
				 case '4':
         				  ADCON = 0x03;	    //8
						  NPK = 4;		 // ДЛЯ Проверки алгоритма восстановления пакета
         		 break;
				 case '5':
         				  ADCON = 0x04;	    //16
						  NPK = 5;		 // ДЛЯ Проверки алгоритма восстановления пакета
         		 break;
				 case '6':
         				  ADCON = 0x05;	    //32
         		 break;
				 case '7':
         				  ADCON = 0x06;	    //64
         		 break;
			  }	 

}

//----------------------------------------------
// Установка дополнительного усиления АЦП 
//------------------------------------------------
void set_ampl_d(void){
	switch (PSDtate) {
				 case '1':
         				  GPIO  |= 0x02;;	    //1
         		 break;
				 case '2':
         				  GPIO  &= 0xFD;;	    //5
         		 break;
				 
			  }	 

}

//------------------------------------
// Установка времени накопления данных
//-----------------------------------
void set_time_mem(void){
			switch (ParState) {
				 case '1':
         				  time_write =1;	    //1
         		 break;
				 case '2':
         				  time_write =2;	    //2
         		 break;
				 case '3':
         				  time_write =4;		//4
         		 break;
				 case '4':
         				  time_write =8;	    //10
         		 break;
				 
			  }
	//		  size = data_rate*4*time_write;	 // размер данных по 1 каналу

}

//------------------------------------
// Установка фильтрации данных
//-----------------------------------
void set_filtr(void){

 		switch (PaState)
			 {
			 	case '1':
						   CLEARBIT(flag1,FILTR_ON);  // Фильтр ОТКЛ
					break;
				case '2':
						   SETBIT(flag1,FILTR_ON);	  // Фильтр ВКЛ
					break;
				default:
					break;
			}


}

///////////---------/////////////-------------//////////////-------------////////////

//------------------------------------
// Установка скорости порта UART1 
//-----------------------------------

void set_bod_rate(void){

			switch (PickStateQ)
			{
				case '1':	
							U1LCR =0x0F;   // Чётность -  нечет
					//		U1LCR &=0xCF;
		
					break;
				case '2':	
							U1LCR =0x1F;   //  Чётность - чёт
					//		U1LCR &=0xDF;
		
					break;
				case '3':	
							U1LCR =0x03;   // 	Чётность - нет
							
		
					break;
				case '4':	
							U1LCR =0x2F;   // Чётность - маркер (1)
				//			U1LCR &=0xF;
		
					break;
				case '5':	
							U1LCR =0x3F;   // Чётность - пробел (0)
				//			U1LCR &=0xDF;
		
					break;
			 }

			switch (PiStateS)
			{
				case '1':	
							U1LCR &= 0xFB;   // стоповых - 1
							
		
					break;
				case '2':	
							U1LCR |= 0x04;   // стоповых - 2
							
		
					break;
			}

	   						U1LCR |= 0x80;	  // DLAB = 1 
		

			switch (PickState)
			{
				case '1':	
							U1DLL = 0x00;   // 4800 Baud Rate 58.9824 MHz    VPB Clock
							U1DLM = 0x03;
		
					break;
				case '2':	
							U1DLL = 0x80;   // 9600  Baud Rate 58.9824 MHz   VPB Clock
							U1DLM = 0x01;
		
					break;
				case '3':
							U1DLL = 0xC0;   // 19200  Baud Rate 58.9824 MHz  VPB Clock
							U1DLM = 0x00;			    
		
					break;
				case '4':	
							U1DLL = 0x60;   // 38400  Baud Rate 58.9824 MHz  VPB Clock
							U1DLM = 0x00;
			
					break;
				case '5':	
						    U1DLL = 0x40;   // 57600  Baud Rate 58.9824 MHz  VPB Clock
							U1DLM = 0x00;
			
					break;
				case '6':	
						    U1DLL = 0x20;   // 115200  Baud Rate 58.9824 MHz  VPB Clock
							U1DLM = 0x00;
			
					break;
				default:
					break;
			}
							U1LCR &= 0x7F;	  // DLAB = 0		
			
}

//-------------------------------------------------------
// Установка протокола обмена c приёмником GPS/ГЛОНАС 
//-------------------------------------------------------

void set_protokol(void){

		 switch (PiState)
			 {
			 	case '1':
						   SETBIT(flag1,NMEA);	   // NMEA
					break;
				case '2':
						   CLEARBIT(flag1,NMEA);   // BINARY
					break;
				default:
					break;
			}


}



