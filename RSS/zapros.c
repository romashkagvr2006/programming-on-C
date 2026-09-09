#include <RTL.h>
#include "..\APP\EXTERNALS.h"

extern U8 N_status;
extern U16 st_hider;
extern  U8 DATA_UART1[8];
extern U8 DATA_UART3[8];
extern U8 HIDER_UART3[3];

U32 n_datchik;
U32 cykl;
U32 max_uart1 = 0;

void zapros(void){
											HIDER_UART3[0] = '*';				// Начало пакета идет с *
							if (n_datchik < 5){
											HIDER_UART3[1] = 'A';				// Группа А
	
							}
								else	HIDER_UART3[1] = 'B';				// Группа B
	
	
							if (++cykl == 6) cykl = 1;
									
									HIDER_UART3[2] = (0x30 + cykl);				// датчик №1
						   
										DATCHIK = __TRUE;							// ставлю флаг занятости сейсмоприемника
									
										HIDER = 	__TRUE;							// флаг выдачи заголовка в RS-485
		 
										DATA_UART1[0] = 'I';
										DATA_UART1[1]	= 'M';
										DATA_UART1[2] = 'K';
				 						DATA_UART1[3] = 0x0D;  				//  VK
				 
										max_uart1 = 4;
									  st_hider = 0;
										N_status = 11;
										
										if (++n_datchik == 10){						//  ЕСЛИ сформировал все запросы
											CLEARBIT(flag1,ZAPROS_ON);			//  снимаю флаг
	
										}
										
										CLEARBIT(flag1,PREPARE);					// Очистил флаг готовности принятых данных
										SETBIT(flag4,UART3_TX);   				// Установил флаг начала передачи команды в СЕЙСМОМЕТР
										ZPR = __TRUE;
}							

void slep(void){
										
											
										DATA_UART1[0] = 'S';
										DATA_UART1[1]	= 'L';
										DATA_UART1[2] = 'P';
				 						DATA_UART1[3] = 0x0D;  						//  VK
				 
										max_uart1 = 4;

				 
										DATCHIK = __FALSE;								//ОЧИЩАЮ флаг занятости сейсмоприемника
										
										
										SETBIT(flag4,UART3_TX);   				//Установил флаг начала передачи команды в СЕЙСМОМЕТР
										
}
