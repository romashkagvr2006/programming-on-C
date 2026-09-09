#include "..\APP\EXTERNALS.h"
#include <string.h>



U8 m_receive_start;
U8 uart1_st;
U8 zapros_frame[11];
U8 otvet_frame[11]={0xAA,0x55,0,10,1,0,0,0, 0,0,0}; 
//1-2	Байты синхронизации пакета	AA 55 (Hex)	
//3-4	Время усреднения в секундах	1, 10, 60*1,…60*10	
//5	Номер команды (см. табл.1)	01, 02,…05 (Hex)	
//6	Не используется	00 (Hex)	
//7-10	Не используется	00 00 00 00 (Hex)	
//11	Контрольная сумма байтов (с 3 по 10)	0…255	

/*
float parametr_1;
float parametr_2;
float parametr_3;
float parametr_4;
float parametr_5;

*/

//===========================================================================
char getchar_m (void) 				// Read character from Serial Port 1  
{                    
  while (!(U1LSR & 0x01));
  return ( U1RBR);
}
//===========================================================================




//////////////////////// Обработчик прерывания по UART0 ////////////////////
//			 Приём запроса параметров в метеостанцию
//
 void UART1_Isr(void)__irq{
	U8 symbol;
	U8 crc;
	U8 a;
	
	if(U1IIR==4){		 // принять массив времени и даты
		symbol=getchar_m();
		
//		sendchar (symbol); 
		
		if(m_receive_start==1){
			zapros_frame[uart1_st]=symbol;   // формирую принятый массив
		  if (++uart1_st == 11){					 // если принял все байты
						crc = 0;
				    m_receive_start=0;
				    uart1_st=0;
				
	//		IO1CLR |= 0x00040000;		   //K3	
				
				for (a=2; a<10; a++){
					crc = crc ^ zapros_frame[a]; // считаю контрольную сумму c 3 по 10 байт
				}
				
						if(crc == zapros_frame[10]){
								SETBIT(flag2,METEO);			   //контрольная сумма совпала
	//						IO1CLR |= 0x00040000;		     //K3	
	//						  IO1SET |= 0x00040000;		     //K3	
						}	
			}
			
			
			goto meteo1;
		}
		
				if(symbol==0xAA){		   // Выделяю начало строки	сообщения

					zapros_frame[uart1_st]=symbol;
					m_receive_start=1;		
						uart1_st++;
					
	//				IO1SET |= 0x00040000;		   //K3		
					goto meteo1;
				}
		
	
	}
meteo1:
 		VICVectAddr = 0; // Update VIC priorities 
}


//--------------------------------------------------------------------------------









//================================================================================
int SER_PutChar (int ch)  {                 /* Write character to Serial Port    */

  while (!(U1LSR & 0x20));
  return (U1THR = ch);
}
//=====================================================================================

void write_otvet(void){
unsigned char a, crc;	
	
	crc = 0;
	
	switch (zapros_frame[4])
{
	case 1:	parametr_1 +=5;												// давление
							if (parametr_1 >= 1000.0) parametr_1 = 100.0;
					memcpy(&otvet_frame[6],&parametr_1 ,4);
					otvet_frame[4]=1;
		break;
	case 2:	parametr_2 += 1;												//температура
							if (parametr_2 >= 100.0) parametr_2 = -100.0;
					memcpy(&otvet_frame[6],&parametr_2 ,4);
					otvet_frame[4]=2;
		break;
	case 3:	parametr_3 += 1;												//влажность
							if (parametr_3 >= 99.0) parametr_3 = 10.0;
					memcpy(&otvet_frame[6],&parametr_3 ,4);
					otvet_frame[4]=3;
		break;
	case 4:	parametr_4 +=2;												//направление ветра
							if (parametr_4 >= 359.0) parametr_4 = 0.0;
					memcpy(&otvet_frame[6],&parametr_4 ,4);
					otvet_frame[4]=4;
		break;
	case 5:	parametr_5 += 1;												//скорость ветра
							if (parametr_5 >= 100.0) parametr_5 = 1.0;
					memcpy(&otvet_frame[6],&parametr_5 ,4);
					otvet_frame[4]=5;
		break;
	
	default:
		break;
}
	
 //   for (a=0; a<11; a++){
//					sendchar ( otvet_frame[a]); // 
//				}


				SER_PutChar (0xAA);
				SER_PutChar (0x55);
	 for (a=2; a<10; a++){
	      SER_PutChar (otvet_frame[a]);
		 crc = crc ^ otvet_frame[a];			//считаю контрольную сумму c 3 по 10 байт
	 }
	 otvet_frame[10] = crc;
	 
				SER_PutChar (otvet_frame[10]);
	 
	  
	 
//				for (a=0; a<11; a++){
//					sendchar ( otvet_frame[a]); // 
//				}	 
	 
}
