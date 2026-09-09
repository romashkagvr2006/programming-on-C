
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <LPC22XX.H>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include  <stdlib.h>



#include <RTL.h>
#include "..\APP\EXTERNALS.h"
//#include "RSS.h"

struct SB_param	SB_param;

// Global time status flag
U16 m_time_st = 0;

// Global mark index
U8 mark = 0;

// Global spisok array - list structure
U8 spisok[8][6];


//#ifdef USE_RSS_RMGD
//#include "RSS.h"


//-----------------------------------------------------------------------------
// Device global variables
//-----------------------------------------------------------------------------

#define DEV_SAMPLE_SZ  12             // One sample for  (4x3 = 12 bytes) 




U8 txt[8];

U8 dev_name[16] = { "KIT" };

U8   lcd_text[23][8+1]= {
							"TВР35",      // Имя станции по умолчанию
						  "5",		      // Частота калибровки
						  "8.420E-6",	  // ЦНРК 1 канал
						  "8.420E-6",
						  "8.420E-6",
						  "8.420E-6",	
  
						  "6.080E-6",		// ЦНРК 2 канал 
						  "6.080E-6",
						  "6.080E-6",	  
						  "6.080E-6",	
	
						  "2.680E-6",	   // ЦНРК 3 канал
						  "2.680E-6",	
						  "2.680E-6",
						  "2.680E-6",
						  "9.0",			     // Амплитуда калибровки
							"CH01",
							"CH02",
							"CH03",
							"CH04",
							"CH05",
							"CH06",
							"CH07",
							"CH08"};	 	   // Имя каналов по умолчанию;

							
U32  FlashPage   [PAGE_SZ/4]; // Flash page buffer = 1024 bytes

U32  FlashPage_FF[48];
U32  FlashPage_BB[8];

U16  data_1ms;
U8         command_src=2;      // 0 - nothing, 1 - console, 2 - telnet
U8         command_complete;
U8         command_escape;
U32        command_phase;
U8         flash_changed;

float  sample[6];
float Temperatura;

U8 flag1;
U8 flag2;		
U8 flag4;
U8 CRC;
U8 N_status;

U32  index_1;
//U32 T1_st;


BOOL LEDrun;
BOOL ZPR;

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

U8 DATA_UART1[8];

U8 PickState;
 U8 PickStateQ;
 U8 PiState;
 U8 PiStateS;
 U8 PaState;
 U8 ParState;
 U8 ParamState;
 U8 PState;
 U8 PSDtate;
 U8 PCState;
 U8 PCLState;
 U8 PBState;
 U8 PAState;

U8 m_time ;
U16 clb_time ;

float a_clb;
float naklon[8];

float NAK_X;
float NAK_Y;
float NAK_S;

float OTKL_X;
float OTKL_Y;
float OTKL_Z;
float PERIOD;

S16 parametr[6];
S32 nak_data_parametr_1[10];  // массивы для накопления данных на 10с
S32 nak_data_parametr_2[10];
S32 nak_data_parametr_3[10];
S32 nak_data_parametr_4[10];
S32 nak_data_parametr_5[10];

S32 data_parametr_1_1[2];
S32 data_parametr_2_1[2];
S32 data_parametr_3_1[2];
S32 data_parametr_4_1[2];
S32 data_parametr_5_1[2];

S32 data_parametr_1_2[2];
S32 data_parametr_2_2[2];
S32 data_parametr_3_2[2];
S32 data_parametr_4_2[2];
S32 data_parametr_5_2[2];


S32* paket_adr_parametr_1;		// Поток на запись 
S32* paket_adr_parametr_2;
S32* paket_adr_parametr_3;
S32* paket_adr_parametr_4;
S32* paket_adr_parametr_5;

S32* out_paket_adr_parametr_1;	// Поток на передачу
S32* out_paket_adr_parametr_2;
S32* out_paket_adr_parametr_3;
S32* out_paket_adr_parametr_4;
S32* out_paket_adr_parametr_5;

float parametr_1;
float parametr_2;
float parametr_3;
float parametr_4;
float parametr_5;

U8 SEYSM_DATA[42];
U8 DATA_UART3[8];
U8 HIDER_UART3[3];

U8 n_sb;
U32 st_ZAPROS_ON;

U32 *adr_pserv;

U16 st_hider;
U32 file_data_count;
U32 st_data_uart3;
U32 st_adr_serial_3_in;
U8 receive_start_3;
U8 UART_2_in_CRC;

U32        pCommand_cgi;
U32        pCommand_next;
U32        pLog_txt;
U32        pLog_txt_end;
U8         command_src;      // 0 - nothing, 1 - console, 2 - telnet
U8         command_complete;
U8         command_escape;
U32        command_phase;
U8         flash_changed;

U32        default_addr;
U32        default_v1;
U32        default_v2;
        
U8         LED1_blink;
U8         LED1_timer;

U32        ex_ram_buf[1];   


FILE       * fi;
FILE       * fo;

//-----------------------------------------------------------------------------
// Global array variables-+
//-----------------------------------------------------------------------------

//U8   lcd_SB[24][8];

char Log_txt     [LOG_SZ];

char Command_cgi [CMD_SZ];

//U32  FlashPage   [PAGE_SZ/4]; // Flash page buffer = 1024 bytes

char       html_buf[HTMLBUF_SZ];
U32        phtml_buf;




extern U8 A_B[2][9];

extern U8 CH_N[5][9];



//U8 FSUK_KOMANDA[12];
//U8 FSUK_DATA[12];


/*--------------------------- get_button ------------------------------------*/

U8 get_button (void) {
   /* Read ARM Digital Input */
   U32 val ;
	
//	val = 0x55;
  val = (IO1PIN >> 19);
	val = val & 0x3f;
	
	
}

U16 get_button_1 (void) {			  // прием квитанций
  /* Read ARM Digital Input */
  U32 val ;
   
    memcpy(&val,&SEYSM_DATA[2],1); 
	
	if ((m_time_st & 0x0001) == 0x0001) {
			val = val;																			// kvit4 имитация квитанции приема данных
	}
			else val = val & 0xEF;
	
			
	
 return (val);		

}



U16 get_button_2 (void) {			  // прием квитанций
  // Read ARM Digital Input //
  U32 val ;
   
    memcpy(&val,&SEYSM_DATA[3],1); 
			val = val;
	switch (PCState){
  
  	case '4':	  // если идет вывешивание, проверяю квитанции
		
									if (spisok[mark][2] !=  1) {      			    // для трехкомпонентных сейсмометров
		
											if ((val & 0x07) == 0x07){				      // если вывешивание закончено 
															m_time_st = 0;							    // обнуляю обратный отсчет
															m_time = 0;
											}
									}
											else {														      // однокомпонентный
														if ((val & 0x04) == 0x04){				// если вывешивание закончено 
																m_time_st = 0;								// обнуляю обратный отсчет
																m_time = 0;
														}	
												}
	
  		break;
												
  	case '2':			//	  Разаретировать датчики
									if (spisok[mark][2] !=  1) {      			    // для трехкомпонентных сейсмометров
		
											if ((val & 0x38) == 0x38){				      // если разарретирование закончено 
															m_time_st = 0;							    // обнуляю обратный отсчет
															m_time = 0;
												
												
											}
									}
											else {														      // однокомпонентный
														if ((val & 0x20) == 0x20){				// если разарретирование закончено 
																m_time_st = 0;								// обнуляю обратный отсчет
																m_time = 0;
														}	
												}
  		break;
												
		case '1':			//	  Аретировать датчики
									if (spisok[mark][2] !=  1) {      			    // для трехкомпонентных сейсмометров
		
											if ((val & 0x38) == 0x00){				      // если арретирование закончено 
															m_time_st = 0;							    // обнуляю обратный отсчет
															m_time = 0;
												
											}
									}
											else {														      // однокомпонентный
														if ((val & 0x20) == 0x00){				// если арретирование закончено 
																m_time_st = 0;								// обнуляю обратный отсчет
																m_time = 0;
														}	
												}
  		break;									
		
  	default:
			
  		break;
  }
	

 return (val);		

}


/*--------------------------- LED_out ---------------------------------------*/

void LED_out (U32 val) {

   if (val & 1) {
      IOCLR0 = 0x00000800;                   /* Turn LED On  (P0.11 = 0)      */
		  SETBIT(flag1,ZAPROS_ON);							// Послать запросы в сейсмодатчики
		  n_sb =0;
		  n_datchik = 0;
			cykl = 0;
   }
   else {
      IOSET0 = 0x00000800;                   /* Turn LED Off (P0.11 = 1)      */
   }
}

void set_name(void){

		  txt[7]= lcd_text[0][0];
		  txt[6]= lcd_text[0][1];
		  txt[5]= lcd_text[0][2];
		  txt[4]= lcd_text[0][3];
		  txt[3]= lcd_text[0][4];
		  txt[2]= lcd_text[0][5];
		  txt[1]= lcd_text[0][6];
		  txt[0]= lcd_text[0][7];
	
			 memcpy(&FlashPage_BB[1],&txt[0],4); 			// Имя станции
			 memcpy(&FlashPage_BB[2],&txt[4],4);
			 
	//		 memmove(&request_frame[20],&txt[0],8); 

}




//-----------------------------------------------------------------------------
// Set timeout (ms)
//-----------------------------------------------------------------------------
//
void set_timeout(U32 time)
{
//T0MR0 = time*(PCLK/1000);                   // 1mSec
//T0TC  = 0;

//T0MCR = 4;                                  // Stop on MR0
//T0TCR = 1;                                  // Timer0 Enable
data_1ms=0x7D1;
}

//-----------------------------------------------------------------------------
// timeout_expired
//-----------------------------------------------------------------------------

//U32 timeout_expired(void) { return( !(T0TCR & 1)); }

//-----------------------------------------------------------------------------
// wait_ms
//-----------------------------------------------------------------------------

void wait_ms(U32 ms)
{
set_timeout(ms);
//while(!timeout_expired());
while((data_1ms--)!=0);
}


//-----------------------------------------------------------------------------
// Timer poll
//-----------------------------------------------------------------------------

void Timer_Poll (void) {
// System tick timer running in poll mode

if (T1IR & 1)
  {
  // Timer 1 interrupt rq pending, clear pending interrupt
  T1IR = 1;
		
//		if (++T1_st == 2){
	//		    T1_st = 0;
			
									if (HIDER == __TRUE){																	    // если стоит флаг выдачи заголовка
										if(st_hider != 3){
											Driver_Output_Enable();																// VD9  драйвер RS-485 на передачу данных

											sendchar (HIDER_UART3[st_hider] );
														++st_hider;																			// передаю два байта с паузой 200 мс
																																						// и 200 мс до начала подачи команды "IMC"
										}
												else{
													HIDER = __FALSE;																  // и снимаю флаг заголовка
												}
									}
				
									if (CHECKBIT(flag1,SLEP)){									// Флаг готовности принятых данных
										  slep();
										  CLEARBIT(flag1,SLEP);
									}
	//							}
  // Timer tick every 100 ms
  timer_tick();

  }
}




/////////////////// Обработчик прерывания RTC ///////////////////////
//void RTC_Isr(void) __irq{
void RTC_Poll (void){

	   if (ILR != 0){			   // Проверка флага прерывания RTC
	
//    		 CCR     = 2;			           //сброс счетчика тактов. STOP  RTC
 			 ILR = 3;					   // Очистить прерывание
			 
			 SETBIT(flag1,PPS);
			 		
 			VICVectAddr = 0;              // reset VIC
	   }
}



//	   
//////////////////// Обработчик прерываний от EINT1   //////////////////////////////
//                      вход синхронизации 1Гц        //
//                                                    //
//                                                    //

void EINT1_Isr(void) __irq  {  //for external interrupt 1
 
  

   
	EXTINT = 0x02;                // Clear the peripheral interrupt flag
	VICVectAddr = 0;              // reset VIC


}
//------------------------------------------------------------------------
 




////////////////////// Обработчик прерываний PWM /////////////////////////////////
//		формирует синхронизацию	 для АЦП      		                //////////////
//		 			                    		                    //////////////
//
//
static void PWM_ISR(void)__irq
{
//   IO1SET |= 0x00020000;
   PWMIR = 0xFF;
 

 //   IO1CLR |= 0x00020000;
    VICVectAddr = 0;
}



///////////////// Обработчик прерывания по TIMER 0 //////////////////////
//
//		 По прерыванию идёт чтение данных из АЦП
//
static void TIMER0_Isr(void)__irq{
	 T0IR = 0xFF;			//Очистил флаг прерывания

 VICVectAddr = 0;              // reset VIC

 VICIntEnClr |= 0x10;       // Disable interrupt T0
}





//////////////////////// Обработчик прерывания по UART1 ////////////////////
//			 
//
//static void UART1_ISR(void)__irq{

 //		VICVectAddr = 0; // Update VIC priorities 
//}

//void UART3_RX_IRQHandler() {    														//обработчик прерывания от сесмометра	
/*
static void UART1_Isr(void)__irq{	
U8 symbol;
		
		VICVectAddr = 0; // Update VIC priorities 
	
//			symbol = SER_GetChar ();                    			// ?????? ??????? ???? ????????? ? RIS
			symbol = getkey ();  
//			NT_UART3 -> IMSC |= ( 0 << IMSC_RXIM_Pos);          //!< Receive interrupt mask = 0 
			U1IER = 0;																						// запрещаю прерывания от RX
	
				if (CHECKBIT(flag4,UART3_OUT)){                   	// если стоит флаг передачи команды
					
		//				Driver_Output_Enable();
					
							if(++st_data_uart3 <	max_uart1){								// если передал не все 
								
											Driver_Output_Enable();									// RS485RW =0 на перередачу данных
								
	///								SER_PutChar (DATA_UART3[st_data_uart3]);
								    sendchar (DATA_UART1[st_data_uart3]);
							}
										else CLEARBIT(flag4,UART3_OUT);  					// передача команды закончена
				}
				
									
											if(symbol=='$'){		                					// выделяю начало строки сообщения
												if (receive_start_3 == 0){									// в приходящем пакете может быть код '$', поэтому
																																		// проверяю заголовок только в начале пакета
												
													
													CRC = 0;
													receive_start_3 = 1;
													UART_2_in_CRC = 0;
													SEYSM_DATA[st_adr_serial_3_in]=symbol;
													
													CRC = CRC ^ symbol;
													
													st_adr_serial_3_in++;

													goto UART3_1;
												}
											}
	
																if(receive_start_3==1){
						
																			SEYSM_DATA[st_adr_serial_3_in]=symbol;             // принимаю очередной символ
						
																				if (++st_adr_serial_3_in == N_status +1 ){
																												
																								receive_start_3=0;
																								st_adr_serial_3_in = 0;
																
																								if (symbol == CRC){								  // проверяю CRC
																						    SETBIT(flag1,PREPARE);							// Флаг готовности принятых данных
																									
																									
																									
																								}
																				}
																				
																						CRC = CRC ^ symbol;
								
																}
		
UART3_1:		;;
																
//	LED_Off(2);															
	//					NT_UART3->ICR |= (1 << ICR_RXIC_Pos );                   //!< Receive interrupt clear //	
	
}


*/




//--------------------------------------------------------------------------------
/*----------------------------------------------------------------------------
  ??? RS-485 ?????????? ??????? ?? ????????
 *----------------------------------------------------------------------------*/
void Driver_Output_Enable(void){
U32 i = 3000;

///			NT_GPIOF->DATAOUT |= RS485RW;      							// RS485RW =0 ?? ???????? ??????
	
	while ( --i != 0);    // 3000 = 120 mks  ?????? ?????????? ??????? ???????????? 
												// ????????, 
}

 
//-----------------------------------------------------------------------------------------------------

void check_up_flags(void){
	extern   U8 *spisok_parametr;
	int i;
		
 //================================== ОБМЕН с метеостанци ей 	UART3 =====================
  	if (CHECKBIT(flag4,UART3_TX)){   						// Если стоит флаг начинаю передавать команду в сейсмометр
			if (HIDER == __FALSE){										// команда пойдет если закончил передавать 
							
									m_time = m_time_st;
									st_data_uart3 = 0;
									st_adr_serial_3_in = 0;
				 
									Driver_Output_Enable();																	// драйвер на передачу
									SETBIT(flag4,UART3_OUT);
				 
			//					SER_PutChar (DATA_UART3[st_data_uart3] );									// передаю байт команды
									sendchar(DATA_UART1[st_data_uart3] );	
				
								  CLEARBIT(flag4,UART3_TX);	 // очистить флаг
				}
			}
	
											if (U1LSR & 0x20){									// если передал байт 			
																													// RS485RW =0 на прием данных
												U1IER = 1;												// РАзрешаю прерывания от RX
											}
			

		if (CHECKBIT(flag1,PPS)){
			
			for(i = 0; i<11; i++)
{
//	printf("%c\n", spisok_parametr[i]);
	sendchar(spisok_parametr[i]);
	
}
		//	*spisok_parametr= NULL;
			
	
			if(m_time != 0){ 
				  	if(--m_time_st == 0){
						     m_time_st = m_time = 0;
						
					}
					 
				  }
			
			if(	clb_time != 0){
				if(--clb_time == 0){
					clb_time = 11;
				}
				
			}
	
					ZPR = __FALSE;										// ОЧИСТИТЬ ФЛАГ
					
				
			
		}
	}		
		





void Init_Dev(void) {
//  void *adr_port_t;


VPBDIV = 1;


// UART0 --> Console
U0LCR = 0x83;                          // 8 bits, no Parity, 1 Stop bit
U0DLL = 0x20;                          // 115200 Baud Rate 58.9824 MHz VPB Clock
U0LCR = 0x03;                          // DLAB = 0


// UART1 --> СПА
//U1LCR = 0x8B;                          // 8 bits, Odd Parity, 1 Stop bit		GEOS
//U1LCR = 0x87;                          // 8 bits, NO Parity, 2 Stop bit
U1LCR = 0x83;                            // 8 bits, no Parity, 1 Stop bit		SPA
//U1DLL = 0x60;  						   // 38400  Baud Rate 58.9824 MHz  VPB Clock
//U1DLM = 0x00;
//U1DLL = 0x00;							// 4800  Baud Rate 58.9824 MHz  VPB Clock
//U1DLM = 0x03;
	U1DLL = 0x40;  				// 57600  Baud Rate 58.9824 MHz  VPB Clock
	U1DLM = 0x00;
//U1LCR = 0x0B;                          // DLAB = 0		Odd Parity	1 Stop bit        GEOS
//U1LCR = 0x07;                          // DLAB = 0		NO Parity	2 Stop bit
U1LCR = 0x03;                            // DLAB = 0	no Parity					  SPA
U1IER = 0x01;



		// UART1 interrupt is an IRQ interrupt 
	VICIntSelect &=~0x80;
	VICVectAddr3 = (unsigned int) & UART1_Isr;
	VICIntEnable |=0x80;		 //Enable UART1 interrupt
  	VICVectCntl3 =0x27;
	
 //VICIntEnClr |= 0x80;       // Disable interrupt UART1



// Timer 1 reload to 100ms

T1TCR = 1;
T1MCR = 3;
T1MR0 = TCNT - 1; // Timer 1 Period 


PINSEL0 = 0x000555C5;

PINSEL1 = 0x004002A8;


//PINSEL2 = 0x0D006914;  // CS3 (P3.24 as gpio), P1_25:16 a GPIO	16BIT
PINSEL2 = 0x0D006924;  // CS3 (P3.24 as gpio), P1_25:16 a GPIO
IO0DIR  = 0x7110EC80;  // E,R_W,RS,TD4,TD3,TD2,LIGHT_LCD,D4-D7,TXD0
IO0SET  = 0x7110E480;

IO1DIR  = 0x020F0003;  // PULL_PIN_P1, CS0, OE
//IO3DIR  = 0x30700000;
IO1CLR |= 0x000F0000;

// P3.24 --> SD_CS
IO3DIR |= 0x01000000;
IO3SET |= 0x01000000;




IODIR3 |= B_28; 
IOSET3  = B_28;
IODIR3 |= B_29; 
IOSET3  = B_29;
//simulate_fofo = 0;

PCONP = 0x00001F3E;

/*	  EXTERNAL INTERRUPT  */
    VPBDIV = 0;
	EXTPOLAR = 0;		                         //  interrupt on falling edge
	VPBDIV = 2;                                  // additional step see errata

	VPBDIV = 0;
	EXTMODE = 0x02;                              // EINT1 is (falling) edge-sensitive
///	EXTMODE = 0x00;
	VPBDIV = 2;	

	VPBDIV = 0x01;                               // additional step see errata
                                                     // VPB clock = CPU clock
	VICVectAddr0 = (unsigned int) & EINT1_Isr;
	EXTINT = 0x02;                               // Clear the peripheral interrupt flag
	VICVectCntl0 = 0x2F;                         // Channel1 on Source#15 ... enabled
 
 
 //==================================================================================
 //  Частота дискретизации формируется на PWM
 //==================================================================================
  // PWM interrupt is an IRQ interrupt 
  VICIntSelect &= ~0x100;
  // Enable PWM interrupt 
  VICIntEnable = 0x100;		   
  // Use slot 0 for PWM interrupt 
  VICVectCntl1 = 0x28;
  // Set the address of ISR for slot 1 
  VICVectAddr1 = (unsigned int)PWM_ISR;

  PWMPR = 3;
 
//  PWMMR0 = 14745600/AD_rate;
 
  PWMMCR = 0x03;
  PWMPCR = 0;
  PWMTCR = 2; 

  


// ---------------------// Конфигурация часов //-------------------------
   PREINT  = 1799;	    // Установка делителя частоты 	 1799 - 1C
   PREFRAC = 0;	    //  для pclk = 60МГц				 1795 - 0.998C



   ILR = 3;				// Очистка регистра прерываний
   AMR = 255; 			// Очистка регистра маски будильника

   YEAR    = 2012;//2011;
   MONTH   = 2;//0;
   DOM     = 29;//0;
   HOUR    = 23;//0;
   MIN     = 57;//0;
   SEC     = 59;//0;
   DOY	   = 60;
   DOW     = 0;

   CCR     = 2;			  //сброс счетчика тактов  RTC
   CCR 	   = 1;
  // CCR     = 0x11;

 

  CIIR = 0x01;			  // Разрешил прерывание от каждой секунды
  ILR = 0x03;
  __enable_irq(); // глобально разрешаем прерывания 
 	  			
 /* Timer RTC interrupt is an IRQ interrupt */
//  VICIntSelect &= ~0x2000;
  /* Enable timer RTC interrupt */
//  VICIntEnable |= 0x2000;
  /* Use slot 3 for timer RTC interrupt */
//  VICVectCntl3 = 0x2D;	   //0x2D
  /* Set the address of ISR for slot 1 */
//  VICVectAddr3 = (unsigned int) &RTC_Isr;


 //===================================================================================
 //              Установки таймера Т0 
 //			использую вход P0.22 как вход прерывания от DRDY АЦП.
 //
  T0CCR = 0x06;

//	 T0MCR = 0x80;		// настройки для использования выхода таймера
//	 T0EMR = 0x300;		// для синхронизации АЦП   
//	 T0MR2 = 2;			// ВАРИАНТ УВЕЛИЧИВАЕТ	ШУМ НА ВЫХОДЕ АЦП НА 6 дБ
//	 T0TCR = 1;         // Timer0 Enable

 /* Timer T0 interrupt is an IRQ interrupt */
  VICIntSelect &= ~0x10;
  /* Enable timer T0 interrupt */
//  VICIntEnable |= 0x10;
  /* Use slot 2 for timer T0 interrupt */
  VICVectCntl2 = 0x24;	   //
  /* Set the address of ISR for slot 3 */
  VICVectAddr2 = (unsigned int) &TIMER0_Isr;
 
//===================================================================================

//  ADCR  = 0x0020FF01;	 // АЦП 1 канал AIN0 230 кГц  Термостат

 //===================================================================================

  //SPIInit();
	
	CRC = 0;
//	T1_st = 0;
}
