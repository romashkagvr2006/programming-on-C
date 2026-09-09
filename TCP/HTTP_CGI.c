/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    HTTP_CGI.C
 *      Purpose: HTTP Server CGI Module
 *      Rev.:    V4.22
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <LPC21XX.h>
#include <Net_Config.h>
#include <stdio.h>
#include <string.h>
#include "..\APP\EXTERNALS.h"
//#include "..\RSS\RSS.h"

// Conditional compilation - only compile if HTTP is enabled
#if HTTP_ENABLE

/*
struct {
  U32  FlashPage_FF;
  U8   lcd_SB[24][8];
  }SB_param ;
*/
U16 CHEN_num = 0x0F;



#define SETBIT(x,y)  (x |= (y))
#define LED_YELLOW (1<<11)
#define UART3_TX			32     // flag4

extern U8 flag4;
extern U8 N_status;

extern  U8 DATA_UART1[8];
U32 max_uart1;
U8 spisok[8][6];

U8 A_B[2][9]= {
	"A",
	"B"
};

U8 CH_N[5][9] = {
	"1",
	"2",
	"3",
	"4",
	"5"
};

U8 tip_A[4][9] = {
	"ТБСЦ5",
	"ТБСЦ6",
	"ТБСЦ7",
	"ТБСЦ8"
};

U8 sost_A[2][9] = {
	"Зажат",
	"Разжат",
	
};

U8 KP_A[2][9] = {"2000", "20000"};

//U8 color;
//U8 stroka;
U8 mark;


U8  spisok_ch[12] ={1, 2, 3, 4, 5, 6};
U8  spisok_loc[6] ={1, 2, 3, 4, 5, 6};
float  f_clb;//[8] ={1.01, 2.34, 3.31, 0.05, 5.0, 6.0, 3.31, 0.05};
float  out_amp_s[6] ={10.2, 2.2, 13.2, 4.2, 5.2, 6.2};
U8  faza[6] ={1, 2, 3, 4, 5, 6};
float  kp[6] ={0.99994, 0.687023, 0.707004, 1.023456, 1.456380, 1.405394};
float  kp_db[6] ={-1.5123, -20.5789, -30.55638, 4.51426, 5.512563, 6.123565};
float  sample_6[6] ={1.61, 2.16, 3.26, 4.116, 5.6, 6.6};
float  cnrk[6] ={1.73, 12.7, 3.37, 14.7, 5.7, 6.7};
float  sample_8[6] ={1.8, 2.8, 3.8, 4.8, 5.8, 6.8};
float  sample_9[6] ={1.9, 2.9, 3.9, 4.9, 5.9, 6.9};

extern U32 file_data_count;
U32 file_data_count_1;

/*
float NAK_X;
float NAK_Y;
float NAK_S;

float OTKL_X;
float OTKL_Y;
float OTKL_Z;
*/


extern U8 PickState;
extern  U8 PickStateQ;
extern  U8 PiState;
extern  U8 PiStateS;
extern  U8 PaState;
  U8 P2State;
  U8 P3State;
extern  U8 ParState;
extern  U8 ParamState;
  U8 P2ramState;
  U8 P3ramState;
extern  U8 PState;
  U8 PSt2te;
  U8 PSt3te;
extern  U8 PSDtate;
extern  U8 PCState;
extern  U8 PAState;
extern  U8 PCLState;
extern  U8 PSWtate;
extern  U8 PSUtate;
extern  U8 PSZtate;
 extern U8 PBState;
 
 BOOL  HIDER;
 
 U16 m_time_st = 25;
 
 /* Local functions */
static void dot_format (U32 val, char *sp);

/* ---------------------------------------------------------------------------
 * The HTTP server provides a small scripting language.
 *
 * The script language is simple and works as follows. Each script line starts
 * with a command character, either "i", "t", "c", "#" or ".".
 *   "i" - command tells the script interpreter to "include" a file from the
 *         virtual file system and output it to the web browser.
 *   "t" - command should be followed by a line of text that is to be output
 *         to the browser.
 *   "c" - command is used to call one of the C functions from the this file.
 *         It may be followed by the line of text. This text is passed to
 *         'cgi_func()' as a pointer to environment variable.
 *   "#' - command is a comment line and is ignored (the "#" denotes a comment)
 *   "." - denotes the last script line.
 *
 * --------------------------------------------------------------------------*/

/* http_demo.c */
extern U16 AD_in (U32 ch);
extern U8  get_button (void);

/* at_System.c */
extern  LOCALM localm[];
#define LocM   localm[NETIF_ETH]

/* Net_Config.c */
extern struct tcp_cfg   tcp_config;

// Define http_cfg structure when HTTP is disabled to avoid linker errors
#if !HTTP_ENABLE
struct http_cfg {
  U8  EnAuth;
  U8  Passw[32];
};
#endif

#if HTTP_ENABLE

#define tcp_NumSocks    tcp_config.NumSocks
#define tcp_socket      tcp_config.Scb
#define http_EnAuth     http_config.EnAuth
#define http_auth_passw http_config.Passw
#else
// Define local http_config when HTTP is disabled
struct http_cfg http_config = {
  0,  // EnAuth = 0 (disabled)
  ""  // Passw = empty string
};
#endif

BOOL  DATCHIK;

// Define all extern variables when HTTP is disabled to avoid linker errors
#if !HTTP_ENABLE
// External variables from other modules
U8 flag4;
U8 N_status;
U8 DATA_UART1[8];
U32 file_data_count;
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
U8 PAState;
U8 PCLState;
U8 PSWtate;
U8 PSUtate;
U8 PSZtate;
U8 PBState;


// Define LOCALM structure
typedef struct {
  U8 dummy[4];  // Placeholder structure
} LOCALM;
LOCALM localm[1];
BOOL LEDrun = 0;
void LED_out(U32 val) {}
BOOL LCDupdate = 0;
U8 lcd_text[23][8+1];
float UGOL_X = 0;
float UGOL_Y = 0;
float UGOL_Z = 0;
#endif

extern BOOL LEDrun;
// LED_out function - empty implementation when HTTP is disabled
#if !HTTP_ENABLE
void LED_out(U32 val) {}
#endif
extern BOOL LCDupdate;
// lcd_text array - empty implementation when HTTP is disabled
#if !HTTP_ENABLE
U8 lcd_text[23][8+1];
#endif
//extern U8   lcd_SB[24][8];

/* Local variables. */
static U8 P2;
static char const state[][9] = {
  "FREE",
  "CLOSED",
  "LISTEN",
  "SYN_REC",
  "SYN_SENT",
  "FINW1",
  "FINW2",
  "CLOSING",
  "LAST_ACK",
  "TWAIT",
  "CONNECT"};

/* My structure of CGI status U32 variable. This variable is private for */
/* each HTTP Session and is not altered by HTTP Server. It is only set to  */
/* zero when the cgi_func() is called for the first time.                  */
typedef struct {
  U16 xcnt;
  U16 unused;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)



extern float  UGOL_X;
extern float  UGOL_Y;
extern float  UGOL_Z;




/*----------------------------------------------------------------------------
 * HTTP Server Common Gateway Interface Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- cgi_process_var -------------------------------*/

void cgi_process_var (U8 *qs) {
  /* This function is called by HTTP server to process the Querry_String   */
  /* for the CGI Form GET method. It is called on SUBMIT from the browser. */
  /*.The Querry_String.is SPACE terminated.                                */
  U8 *var;
  int s[6];

  var = (U8 *)alloc_mem (40);
  do {
    /* Loop through all the parameters. */
    qs = http_get_var (qs, var, 40);
    /* Check the returned string, 'qs' now points to the next. */
    if (var[0] != 0) {
      /* Returned string is non 0-length. */
      if (str_scomp (var, "ip=") == __TRUE) {
        /* My IP address parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.IpAdr[0]   = s[0];
        LocM.IpAdr[1]   = s[1];
        LocM.IpAdr[2]   = s[2];
        LocM.IpAdr[3]   = s[3];
      }
      else if (str_scomp (var, "msk=") == __TRUE) {
        /* MAC address. */
          sscanf ((const char *)&var[4], "%X.%X.%X.%X.%X.%X",&s[0],&s[1],&s[2],&s[3],&s[4],&s[5]);
        	own_hw_adr[0] = s[0];
        	own_hw_adr[1] = s[1];
        	own_hw_adr[2] = s[2];
        	own_hw_adr[3] = s[3];
		      own_hw_adr[4] = s[4];
        	own_hw_adr[5] = s[5];
      }
      else if (str_scomp (var, "gw=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.DefGW[0]   = s[0];
        LocM.DefGW[1]   = s[1];
        LocM.DefGW[2]   = s[2];
        LocM.DefGW[3]   = s[3];
      }
      else if (str_scomp (var, "pdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.PriDNS[0]  = s[0];
        LocM.PriDNS[1]  = s[1];
        LocM.PriDNS[2]  = s[2];
        LocM.PriDNS[3]  = s[3];
      }
      else if (str_scomp (var, "sdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.SecDNS[0]  = s[0];
        LocM.SecDNS[1]  = s[1];
        LocM.SecDNS[2]  = s[2];
        LocM.SecDNS[3]  = s[3];
      }
    }
		
		// Командная строка
	  if (str_scomp (var, "cmd=") == __TRUE)
		   {
           process_cmd_start(HTTP_SRC,(char *)(var + 4));
           }
		
		
  }while (qs);
  free_mem ((OS_FRAME *)var);
}


/*--------------------------- cgi_process_data ------------------------------*/

void cgi_process_data (U8 code, U8 *dat, U16 len) {
  /* This function is called by HTTP server to process the returned Data    */
  /* for the CGI Form POST method. It is called on SUBMIT from the browser. */
  /* Parameters:                                                            */
  /*   code  - callback context code                                        */
  /*           0 = www-url-encoded form data                                */
  /*           1 = filename for file upload (0-terminated string)           */
  /*           2 = file upload raw data                                     */
  /*           3 = end of file upload (file close requested)                */
  /*           4 = any xml encoded POST data (single or last stream)        */
  /*           5 = the same as 4, but with more xml data to follow          */
  /*               Use http_get_content_type() to check the content type    */  
  /*   dat   - pointer to POST received data                                */
  /*   len   - received data length                                         */
  U8 passw[12],retyped[12];
  U8 *var,stpassw;
BOOL do_format;
BOOL do_apdat;
U32 j;	
	
	
	
	
  switch (code) {
    case 0:
      /* Url encoded form data received. */
      break;

    default:
      /* Ignore all other codes. */
      return;
  }

  P2 = 0;
  LEDrun = __TRUE;
  if (len == 0) {
    /* No data or all items (radio, checkbox) are off. */
    LED_out (P2);
    return;
  }
  stpassw = 0;
  var = (U8 *)alloc_mem (40);
  do {
    /* Parse all returned parameters. */
    dat = http_get_var (dat, var, 40);
    if (var[0] != 0) {
			
			if (str_scomp (var, "aclb=") == __TRUE) {         // Задать амплитуду калибровки
               	str_copy (lcd_text[14], var+5);

			    a_clb = atof (lcd_text[14]);
			    f_clb = atof (lcd_text[1]);
				
//				  ka_clb = a_clb * 0.1f;
				
 //    				set_clb_f();
      		}
 
      else if (str_scomp (var, "fclb=") == __TRUE) {     // Задать частоту калибровки
               	str_copy (lcd_text[1], var+5);
	
	   		}	 
				 
			 else if (str_scomp (var, "PICK4=") == __TRUE) {	 // Выбор вида калибровки
            PCLState = *(var+6);

			}	 
			
			
			
			
			else if (str_scomp (var, "PICK7=") == __TRUE) {	 // Выбор команды
            PAState = *(var+6);
				
				switch (PAState) {
				 case '1':				// Группа А
									HIDER_UART3[1] = 'A';

					 break;
				 case '2':				// Группа B
									HIDER_UART3[1] = 'B';

					 break;
			 }
			}
			
			
			else if (str_scomp (var, "PICK8=") == __TRUE) {	 // Выбор команды
            PBState = *(var+6);
				
				switch (PBState) {
				 case '1':				
									HIDER_UART3[2] = '1';

					 break;
				 case '2':				
									HIDER_UART3[2] = '2';

					 break;
				  case '3':				
									HIDER_UART3[2] = '3';

					 break;
				 case '4':				
									HIDER_UART3[2] = '4';

					 break;
				 case '5':				
									HIDER_UART3[2] = '5';			// ТБСЦ5, ТБСЦ7,ТБСЦ8 может быть 1 штука в одной группе

					 break;
			 }	
				
	
										mark = 0;
							while (spisok[mark][0] != ((PAState & 0x0F) - 1)){				 // Вычисляю адрес строки в которой буду
										mark++;
							}
										while (spisok[mark][1] != ((PBState & 0x0F) - 1)){   // делать подсветку
										mark++;
										}
			 
		 }
			
			
			 else if (str_scomp (var, "PICK3=") == __TRUE) {	 // Выбор команды
            PCState = *(var+6);
									
						
			   switch (PCState) {
				 case '2':
         				  	    			//	  Разаретировать датчики
										DATA_UART1[0] = 'R';
										DATA_UART1[1]	= 'V';
										DATA_UART1[2] = 'D';
										DATA_UART1[3] = 0x0D;  //  VK
				 
										SEYSM_DATA[3] &= 0xC7;
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 20;
				//						mark = 0;
         		 break;
				 case '1':
         				  	    			//	  Арретировать датчики
										DATA_UART1[0] = 'A';
										DATA_UART1[1]	= 'V';
										DATA_UART1[2] = 'D';
				 						DATA_UART1[3] = 0x0D;  //  VK
				 
										SEYSM_DATA[3] &= 0xC7;
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 30;
			//							mark = 0;
         		 break;
				 case '4':
         				  					//	  Вывесить датчики
										DATA_UART1[0] = 'V';
										DATA_UART1[1]	= 'D';
										DATA_UART1[2] = 'V';
				 						DATA_UART1[3] = 0x0D;  //  VK
				 
										SEYSM_DATA[3] &= 0xF8;
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 160;
				//						mark = 0;
         		 break;
				 case '3':
         				  	    			//	  Ориентировать датчики по вертикали 
										DATA_UART1[0] = 'O';
										DATA_UART1[1]	= 'V';
										DATA_UART1[2] = 'D';
				 						DATA_UART1[3] = 0x0D;  //  VK
				 
						//				SEYSM_DATA[2] = 0;
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 10;
				//						mark = 0;
         		 break;
				 case '5':
         				  	    			//	  Проверка воды в скважине
										DATA_UART1[0] = 'D';
										DATA_UART1[1]	= 'N';
										DATA_UART1[2] = 'V';
				 						DATA_UART1[3] = 0x0D;  //  VK
				 
						//				SEYSM_DATA[2] = 0;
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 10;
			//							mark = 0;
         		 break;
				 case '6':
         				  	    			//	  Показать углы наклона сейсмометра
										DATA_UART1[0] = 'D';
										DATA_UART1[1]	= 'I';
										DATA_UART1[2] = 'R';
				 						DATA_UART1[3] = 0x0D;  //  VK
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 4;
			//							mark = 0;
         		 break;
					   
				 case '7':
         				  	    			//	  Подключить калибровочный вход
										DATA_UART1[0] = 'C';
										DATA_UART1[1]	= 'L';
										DATA_UART1[2] = 'B';
										DATA_UART1[3] = 'O';
										DATA_UART1[4]	= 'N';
										DATA_UART1[5] = 0x0D;  //  VK
				 
				//						SEYSM_DATA[3] = 0;
				 
										N_status = 41;
										max_uart1 = 6;
										m_time_st = 2;
					//					mark = 0;
         		 break;
				 case '8':
         				  	    			//	  Отключить калибровочный вход
										DATA_UART1[0] = 'C';
										DATA_UART1[1]	= 'L';
										DATA_UART1[2] = 'B';
										DATA_UART1[3] = 'O';
										DATA_UART1[4]	= 'F';
										DATA_UART1[5] = 'F';
				 						DATA_UART1[6] = 0x0D;  //  VK
				 
										N_status = 41;
										max_uart1 = 7;
										m_time_st = 2;
					//					mark = 0;
         		 break;
				 case '9':
         				  	    			//	  Перейти в ждущий режим
										DATA_UART1[0] = 'S';
										DATA_UART1[1]	= 'L';
										DATA_UART1[2] = 'P';
				 						DATA_UART1[3] = 0x0D;  //  VK
				 
										max_uart1 = 4;
										m_time_st = 2;
				 
										mark = 9;					// убираю подсветку строки
				 
										DATCHIK = __FALSE;							//ОЧИЩАЮ флаг занятости сейсмоприемника
				 
         		 break;
				 case 'a':														//	  Подключить сейсмоприемник
					 
								if (DATCHIK == __FALSE){     //	  Защита от одновременного подключения нескольких сейсометров 
         				  	    			
				 

					   
										DATCHIK = __TRUE;							//ставлю флаг занятости сейсмоприемника
									
										HIDER = 	__TRUE;							// флаг выдачи заголовка в RS-485
		 
										DATA_UART1[0] = 'I';
										DATA_UART1[1]	= 'M';
										DATA_UART1[2] = 'K';
				 						DATA_UART1[3] = 0x0D;  //  VK
									
			//							SEYSM_DATA[3] = 0;
									
										N_status = 11;
										st_data_uart3 = 0;
										max_uart1 = 4;
										m_time_st = 2;
									  st_hider = 0;
			//							mark = 0;
								}
         		 break;
							
					case 'b':																				//	  Общий запрос всех подключенных сейсмоприемников
										SETBIT(flag1,ZAPROS_ON);							// Послать запросы в сейсмодатчики
										n_sb =0;
										n_datchik = 0;
										cykl = 0;
					
										SEYSM_DATA[2] &= 0xEF;
					
										m_time_st = 10;
										mark = 9;					// убираю подсветку строки
							break;	
					
					case 'c':																			// Контроль периода маятника
										DATA_UART1[0] = 'K';
										DATA_UART1[1]	= 'P';
										DATA_UART1[2] = 'M';
				 						DATA_UART1[3] = 0x0D;  //  VK
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 40;
				//						mark = 0;
					   break;
					
					case 'f':																			// Изменить период маятника
										DATA_UART3[0] = 'I';
										DATA_UART3[1]	= 'P';
										DATA_UART3[2] = 'M';
				 						DATA_UART3[3] = 0x0D;  //  VK
				 
										N_status  = 41;
										max_uart1 = 4;
										m_time_st = 60;
				//						mark = 0;
					   break;
					
					case 'd':																			// Установить коэффициент передачи
										DATA_UART3[0] = 'U';
										DATA_UART3[1]	= 'K';
										DATA_UART3[2] = 'P';
				 						DATA_UART3[3] = 0x0D;  //  VK
				 
										N_status = 41;
										max_uart1 = 4;
										m_time_st = 2;
				//						mark = 0;
					   break;
				 }
								
								if (!(CHECKBIT(flag1,ZAPROS_ON))){  //ставлю флаг передачи на любую команду кроме общего запроса
									
									    SEYSM_DATA[2] &= 0xEF;
											SETBIT(flag4,UART3_TX);       //Установил флаг начала передачи команды в СЕЙСМОМЕТР
								}
 			}
			
			
			
			
			
      /* Parameter found, returned string is non 0-length. */
      else if (str_scomp (var, "led0=on") == __TRUE) {
        P2 |= 0x01;
      }
      else if (str_scomp (var, "led1=on") == __TRUE) {
        P2 |= 0x02;
      }
      else if (str_scomp (var, "led2=on") == __TRUE) {
        P2 |= 0x04;
      }
      else if (str_scomp (var, "led3=on") == __TRUE) {
        P2 |= 0x08;
      }
      else if (str_scomp (var, "led4=on") == __TRUE) {
        P2 |= 0x10;
      }
      else if (str_scomp (var, "led5=on") == __TRUE) {
        P2 |= 0x20;
      }
      else if (str_scomp (var, "led6=on") == __TRUE) {
        P2 |= 0x40;
      }
      else if (str_scomp (var, "led7=on") == __TRUE) {
        P2 |= 0x80;
      }
      else if (str_scomp (var, "ctrl=Browser") == __TRUE) {
        LEDrun = __FALSE;
      }
			
			else if (str_scomp (var, "kpa1=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[0], var+5);
								
	   		}	
			else if (str_scomp (var, "kpb1=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[1], var+5);
								
	   		}
			else if (str_scomp (var, "kpc1=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[2], var+5);
								
	   		}	
			else if (str_scomp (var, "kpd1=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[3], var+5);
								
	   		}			
			
			else if (str_scomp (var, "rca1=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[0], var+5);
								
	   		}	
			else if (str_scomp (var, "rcb1=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[1], var+5);
								
	   		}
			else if (str_scomp (var, "rcc1=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[2], var+5);
								
	   		}	
			else if (str_scomp (var, "rcd1=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[3], var+5);
								
	   		}			
				
			else if (str_scomp (var, "tka1=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[0], var+5);
							  
	   		}	
			else if (str_scomp (var, "tkb1=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[1], var+5);
								
	   		}
			else if (str_scomp (var, "tkc1=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[2], var+5);
								
	   		}	
			else if (str_scomp (var, "tkd1=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[3], var+5);
								
	   		}	

			else if (str_scomp (var, "kpa2=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[4], var+5);
	
	   		}	
			else if (str_scomp (var, "kpb2=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[5], var+5);
	
	   		}
			else if (str_scomp (var, "kpc2=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[6], var+5);
	
	   		}	
			else if (str_scomp (var, "kpd2=") == __TRUE) {     // Коэффициент передачи датчика
               	str_copy (SB_param.lcd_KP[7], var+5);
	
	   		}			
				
			else if (str_scomp (var, "rca2=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[4], var+5);
	
	   		}	
			else if (str_scomp (var, "rcb2=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[5], var+5);
	
	   		}
			else if (str_scomp (var, "rcc2=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[6], var+5);
	
	   		}	
			else if (str_scomp (var, "rcd2=") == __TRUE) {     // Сопротивление калибровочного резистора
               	str_copy (SB_param.lcd_RR[7], var+5);
	
	   		}			
				
			else if (str_scomp (var, "tka2=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[4], var+5);
	
	   		}	
			else if (str_scomp (var, "tkb2=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[5], var+5);
	
	   		}
			else if (str_scomp (var, "tkc2=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[6], var+5);
	
	   		}	
			else if (str_scomp (var, "tkd2=") == __TRUE) {     // Постоянная времени
               	str_copy (SB_param.lcd_GG[7], var+5);
	
	   		}		
			

					
	    if (str_scomp (var, "lcd1=") == __TRUE) {            // Задать имя станции
				
				for(j = 0; j < 9; j++){
											lcd_text[0][j] = 0;
									}
				
               	str_copy (lcd_text[0], var+5);
				set_name();
//				sektor_num = 2;
      		}
			
					
			
			else if (str_scomp (var, "lcdA=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[15][j] = 0;
									}
				
               	str_copy (lcd_text[15], var+5);
//				set_name();
//				sektor_num = 2;
      		}
					
			else if (str_scomp (var, "lcdB=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[16][j] = 0;
									}
				
               	str_copy (lcd_text[16], var+5);
//				set_name();
//				sektor_num = 2;
      		}		
					
			else if (str_scomp (var, "lcdC=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[17][j] = 0;
									}
				
               	str_copy (lcd_text[17], var+5);
//				set_name();
//				sektor_num = 2;
      		}
					
			else if (str_scomp (var, "lcdD=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[18][j] = 0;
									}
				
               	str_copy (lcd_text[18], var+5);
//				set_name();
//				sektor_num = 2;
      		}				
			
			else if (str_scomp (var, "lcdE=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[19][j] = 0;
									}
				
               	str_copy (lcd_text[19], var+5);
//				set_name();
//				sektor_num = 2;
      		}
					
			else if (str_scomp (var, "lcdE=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[20][j] = 0;
									}
				
               	str_copy (lcd_text[20], var+5);
//				set_name();
//				sektor_num = 2;
      		}		
					
			else if (str_scomp (var, "lcdG=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[21][j] = 0;
									}
				
               	str_copy (lcd_text[21], var+5);
//				set_name();
//				sektor_num = 2;
      		}
					
			else if (str_scomp (var, "lcdH=") == __TRUE) {            // Задать имя канала
				
				for(j = 0; j < 5; j++){
											lcd_text[22][j] = 0;
									}
				
               	str_copy (lcd_text[22], var+5);
//				set_name();
//				sektor_num = 2;
      		}						
					
					
					
					
					
					
					
					
					
			
			if (str_scomp (var, "lcd2=") == __TRUE) {            // Задать размер кольцевого буфера
               	str_copy (lcd_text[4], var+5);
				        memcpy(&FlashPage_BB[7],&lcd_text[4],4); 
//				set_time_bufer();
//				sektor_num = 2;
      		}
			
					
					else if (str_scomp (var, "PARA1=") == __TRUE) {	 // Выбор времени накопления 
            ParState = *(var+6);
					
						FlashPage_BB[3] &= 0xFFFFFF00;	
						FlashPage_BB[3] |= ParState;	
			//			FlashPage_C[3] &= 0xFFFFFF00;	
			//			FlashPage_C[3] |= ParState;
			
/////						set_time_mem();
							
//						sektor_num = 2;	
 			}
				//----------------------------------- ПЛАТА А ------------------------------------------------	
			
			 else if (str_scomp (var, "PARA3=") == __TRUE) {	 // Выбор режима фильтрации
            PaState = *(var+6);
															
						FlashPage_BB[3] &=  0xFFFF00FF;	  
						FlashPage_BB[3] |= (PaState << 8);
					 
//						sektor_num = 2;
			}
		
	  else if (str_scomp (var, "PARA2=") == __TRUE) {	 // Выбор частоты дискретизации
            ParamState = *(var+6);
						
						FlashPage_BB[3] &=  0xFF00FFFF;	
						FlashPage_BB[3] |=	(ParamState << 16);
			
//			      set_data_parametr();
			  //    set_data_rate();
			
//					  sektor_num = 2;	

 			}
				
	  else if (str_scomp (var, "PARA4=") == __TRUE) {	 // Выбор коэффициента усиления АЦП
            PState = *(var+6);
					
						FlashPage_BB[3] &=  0x00FFFFFF;	  
						FlashPage_BB[3] |= (PState << 24);
			
//						sektor_num = 2;
			}
		
//----------------------------------- ПЛАТА В ------------------------------------------------		
			
		 else if (str_scomp (var, "PIRA3=") == __TRUE) {	 // Выбор режима фильтрации
            P2State = *(var+6);
															
						FlashPage_BB[5] &=  0xFFFF00FF;	  
						FlashPage_BB[5] |= (P2State << 8);
					 
//						sektor_num = 2;
			}
		
	  else if (str_scomp (var, "PIRA2=") == __TRUE) {	 // Выбор частоты дискретизации
            P2ramState = *(var+6);
						
						FlashPage_BB[5] &=  0xFF00FFFF;	
						FlashPage_BB[5] |=	(P2ramState << 16);
			
//			      set_data_parametr();
//			      set_data_rate();
			
//					  sektor_num = 2;	

 			}
			
	  else if (str_scomp (var, "PIRA4=") == __TRUE) {	 // Выбор коэффициента усиления АЦП
            PSt2te = *(var+6);
					
						FlashPage_BB[5] &=  0x00FFFFFF;	  
						FlashPage_BB[5] |= (PSt2te << 24);
			
//						sektor_num = 2;
			}	
			
      else if (str_scomp (var, "pw=") == __TRUE) {
        /* Change password. */
        str_copy (passw, var+3);
        stpassw |= 1;
      }
      else if (str_scomp (var, "pw2=") == __TRUE) {
        /* Retyped password. */
        str_copy (retyped, var+4);
        stpassw |= 2;
      }
			
			else if (str_scomp (var, "apdat=yes") == __TRUE) {	 // Форматировать SD-карту
	//					if (CHECKBIT(flag,STOP)){
								do_apdat = __TRUE;
	//					}
					}
 
    }
  }while (dat);
  free_mem ((OS_FRAME *)var);
  LED_out (P2);

  if (stpassw == 0x03) {
    len = strlen ((const char *)passw);
    if (mem_comp (passw, retyped, len) == __TRUE) {
      /* OK, both entered passwords the same, change it. */
      str_copy (http_auth_passw, passw);
    }
  }
	
	if (do_apdat == __TRUE) {				// записать значения в память eeprom
      IO0CLR = LED_YELLOW;
   }
	/*
	if (do_format == __TRUE) {
      if (finit("N0:") != 1) {
         // Return value 1 - SD Card is missing. //
  //       fformat ((const char *)label);
						fformat	("N0: /LOW") ;         // Может делать низкоуровневое форматирование 
																						 // если раскомментировать
      }
   }
	*/
	
}


/*--------------------------- cgi_func --------------------------------------*/

U16 cgi_func (U8 *env, U8 *buf, U16 buflen, U32 *pcgi) {
  /* This function is called by HTTP server script interpreter to make a    */
  /* formated output for 'stdout'. It returns the number of bytes written   */
  /* to the output buffer. Hi-bit of return value (len is or-ed with 0x8000)*/
  /* is a repeat flag for the system script interpreter. If this bit is set */
  /* to 1, the system will call the 'cgi_func()' again for the same script  */
  /* line with parameter 'pcgi' pointing to a 4-byte buffer. This buffer    */
  /* can be used for storing different status variables for this function.  */
  /* It is set to 0 by HTTP Server on first call and is not altered by      */
  /* HTTP server for repeated calls. This function should NEVER write more  */
  /* than 'buflen' bytes to the buffer.                                     */
  /* Parameters:                                                            */
  /*   env    - environment variable string                                 */
  /*   buf    - HTTP transmit buffer                                        */
  /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
  /*   pcgi   - pointer to session local buffer used for repeated loops     */
  /*            This is a U32 variable - size is 4 bytes. Value is:         */
  /*            - on 1st call = 0                                           */
  /*            - 2nd call    = as set by this function on first call       */

  //const char mask[] = "*.*";
	char *mask;
  static FINFO info;
  char temp[16];
  U32 len = 0;
	U16 id;
  U16 i;
  U8  c;
	
	
	if(env[0] == 'A') pLog_txt = 0;

len = 0;
for(i = 0; i < 64; i++)
  {
  c = get_log_char();/*
  if(c == 13  ) c = get_log_char();
  if(c == 0   ) break;
  if(c == '\n')
    {
	buf[len++] = '<';
	buf[len++] = 'b';
	buf[len++] = 'r';
	buf[len++] = '>';
	}
  else
  if(c == ' ' )
    {
	buf[len++] = '&';
	buf[len++] = 'n';
	buf[len++] = 'b';
	buf[len++] = 's';
	buf[len++] = 'p';
	buf[len++] = ';';
	}
  else */buf[len++] = c;
  }

	
	
	
	
  switch (env[0]) {
    /* Analyze the environment string. It is the script 'c' line starting */
    /* at position 2. What you write to the script file is returned here. */
    case 'a' :
      /* Network parameters - file 'network.cgi' */
      switch (env[2]) {
        case 'i':
          /* Write the local IP address. The format string is included */
          /* in environment string of the script line.                 */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.IpAdr[0],
                        LocM.IpAdr[1],LocM.IpAdr[2],LocM.IpAdr[3]);
          break;
        case 'm':
          /* Write local MAC address. */
		     len = sprintf((char *)buf,(const char *)&env[4],own_hw_adr[0],
                        own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],
						            own_hw_adr[4],own_hw_adr[5]);
          break;
        case 'g':
          /* Write default gateway address. */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.DefGW[0],
                        LocM.DefGW[1],LocM.DefGW[2],LocM.DefGW[3]);
          break;
        case 'p':
          /* Write primary DNS server address. */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.PriDNS[0],
                        LocM.PriDNS[1],LocM.PriDNS[2],LocM.PriDNS[3]);
          break;
        case 's':
          /* Write secondary DNS server address. */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.SecDNS[0],
                        LocM.SecDNS[1],LocM.SecDNS[2],LocM.SecDNS[3]);
          break;
      }
      break;
			
			case 'b':
      /* LED CheckBoxes */
      id = env[2] - '0';
      if (id > 4) {
        id = 0;
      }
      id = 1 << id;
 
			len = sprintf((char *)buf,(const char *)&env[4],(CHEN_num & id) ? "checked" : "");
      break;
			
			case 'v':
       /* LED CheckBoxes */
      id = env[2] - '0';
      if (id > 4) {
        id = 0;
      }
      id = 1 << id + 4;
 
			len = sprintf((char *)buf,(const char *)&env[4],(CHEN_num & id) ? "checked" : "");
			
	  
	case 'n':
		switch (env[2]) {
			case 'c':
         				 							
						if(file_data_count < n_sb){
	/*						
							a1 = spisok[file_data_count][0];
							a2 = spisok[file_data_count][1];
							a3 = spisok[file_data_count][2];
							a4 = spisok[file_data_count][3];
							a5 = spisok[file_data_count][4];
							a6 = spisok[file_data_count][5];
			*/
            dot_format (info.size, temp);
							
					if (file_data_count == mark)	{								// Выделяю зеленым цветом датчик с которым работаю
						len += (U32)sprintf (buf + len,"<tr align=center><td bgcolor=#aaffcc>%s</td>"						// Группа
  //          len += sprintf ((char *)buf,"<tr align=center><td bgcolor=#aaffcc>%s</td>"						// Группа
																				"<td align=center bgcolor=#aaffcc>%s</td>"								// Канал
																			  "<td align=center bgcolor=#aaffcc>%s</td>"								// тип
																				"<td align=center bgcolor=#aaffcc>%s</td>"								// КП
																				"<td align=center bgcolor=#aaffcc>%s</td>"			       		// состояние
                                        "<td align=center bgcolor=#aaffcc>%6.2f</td></tr>\r\n",		// наклон корпуса
 
				A_B[spisok[file_data_count][0]], CH_N[spisok[file_data_count][1]],
        tip_A[spisok[file_data_count][2]],KP_A[spisok[file_data_count][3]],
				sost_A[spisok[file_data_count][4]], naklon[file_data_count]); 
					}
					
					else {
						 len += (U32)sprintf (buf + len,"<tr align=center><td>%s</td>"						// Группа
	//					 len += sprintf ((char *)buf,"<tr align=center><td>%s</td>"						// Группа
																				"<td align=center>%s</td>"								// Канал
																			  "<td align=center>%s</td>"			          // тип
																				"<td align=center>%s</td>"								// КП
																				"<td align=center>%s</td>"			          // состояние
                                        "<td align=center>%6.2f</td></tr>\r\n",		// наклон корпуса
 
				A_B[spisok[file_data_count][0]], CH_N[spisok[file_data_count][1]],
        tip_A[spisok[file_data_count][2]],KP_A[spisok[file_data_count][3]],
				sost_A[spisok[file_data_count][4]], naklon[file_data_count]); 
					 }
					
            // Hi bit is a repeat flag. //
						file_data_count ++;
						IO0SET = LED_YELLOW;
	
            len |= 0x8000;
         }			
         break;
				 
				 case 'b':
									if(file_data_count < 4){
			
            dot_format (info.size, temp);
										
										
            len += sprintf ((char *)buf,"<tr align=center><td>%s</td>"								// канал
                                        "<td align=center>%g</td>"											//  Кп НЧ
																				"<td align=center>%g</td>"			                //  Кп ВЧ
		                                    "<td>%g</td></tr>\r\n",		                      //  ЦНРК
														
  /*      spisok_ch[file_data_count],spisok_loc[file_data_count], */
						lcd_text[file_data_count + 15],
				 kp[file_data_count], kp_db[file_data_count],  cnrk[file_data_count] );
							  							
            // Hi bit is a repeat flag. //
						file_data_count ++;
						IO0SET = LED_YELLOW;
	
            len |= 0x8000;
					}	
			   break;
			 }
		 break;
			 
		case 'c':
      // GPS status - file 'tcp.cgi' //
		 len += sprintf((char *)(buf+len),"<tr align=\"center\">");
		 switch (env[2]) {
		case 'j':
			   if (CHECKBIT(flag2,GPS_UART)){
					 
		//			 if ((clb_time == 0) & (m_time_st ==0)){		// запрос координат делаю когда нет калибровки и не работаю с датчиком
					 
	//										komanda[2] = 'P';							  // ЗАПРОС КООРДИНАТ					
	//										SETBIT(flag2,COMMAND);		      // Ставлю флаг наличия команды на передачу
	//				 }
					 
								//			status_data[0][1] = status_data[1][1] = status_data[2][1] = status_data[3][1] =
								//			status_data[4][1] = status_data[5][1] = status_data[6][1] = status_data[7][1] |=0x01; // прием данных от GPS есть 
					 
			   len = sprintf((char *)buf,(const char *)&env[4],"есть" );
			   }
						else  {		//status_data[0][1] = status_data[1][1] = status_data[2][1] = status_data[3][1] =
							       // status_data[4][1] = status_data[5][1] = status_data[6][1] = status_data[7][1] &=0xFE;  // приема данных от GPS нет 
									len = sprintf((char *)buf,(const char *)&env[4],"нет" );
							}
		  break;

        case 'i':
          /* Write the GPS_Quality. The format string is included */
          /* in environment string of the script line.                 */
	 
	//			 if(GPS_rej ==1){				   // Если работает GPS
		
												//  status_data[0][1] = status_data[1][1] = status_data[2][1] = status_data[3][1] =
									//				status_data[4][1] = status_data[5][1] = status_data[6][1] = status_data[7][1] |=0x02;
					 
   //       		len = sprintf((char *)buf,(const char *)&env[4],"есть" );      // привязка есть 
	//	   }

		
	//								else {// status_data[0][1] = status_data[1][1] = status_data[2][1] = status_data[3][1] =
										     //status_data[4][1] = status_data[5][1] = status_data[6][1] = status_data[7][1] &=0xFD;
										
	//									len = sprintf((char *)buf,(const char *)&env[4],"нет" );   //   привязки нет 
	//								}
	            
          break;									  
        case 'm':
          /* Write n_Satellites. */
		//											status_data[0][2] = status_data[1][2] = status_data[2][2] = status_data[3][2] = 
		//											status_data[4][2] = status_data[5][2] = status_data[6][2] = status_data[7][2] = n_Satellites;
				
//		  len = sprintf((char *)buf,(const char *)&env[4],n_Satellites );
                        
          break;
        case 'g':
		  /* Write Date. */
          len = sprintf((char *)buf,(const char *)&env[4],DOM,MONTH,YEAR);
                        

          break;									  
        case 'p':
		  /* Write Time. */
          len = sprintf((char *)buf,(const char *)&env[4],HOUR,MIN,SEC);
		  
                        
          break;
				 case 'w':
		  /* Write Date. */
  //        len = sprintf((char *)buf,(const char *)&env[4],GPS_sh);
                        

          break;									  
        case 'q':
		  /* Write Time. */
   //       len = sprintf((char *)buf,(const char *)&env[4],GPS_dg);
		  
                        
          break;
				
				
		case 's':
		  /* Write Time. */
          len = sprintf((char *)buf,(const char *)&env[4],clb_time);	// Время калибровки

		  break;
		  case 't':
		  // Write Time. //
          len = sprintf((char *)buf,(const char *)&env[4],m_time_st);	// Время механических команд

		  break;		
		  }
	   break;	 
			 
			 
		case 'E':
      
      switch (env[2]) {
				
		case '1':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[0]);	// Ввод имени станции 
          break;
		
		case 'A':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[15]);	// Ввод имени канала 
          break;
		case 'B':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[16]);	// Ввод имени канала 
          break;
		case 'C':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[17]);	// Ввод имени канала 
          break;
		case 'D':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[18]);	// Ввод имени канала 
          break;
		
		case 'E':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[19]);	// Ввод имени канала
          break;
		case 'F':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[20]);	// Ввод имени канала
          break;
		case 'G':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[21]);	// Ввод имени канала 
          break;
		case 'H':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[22]);	// Ввод имени канала 
          break;
		
		
		case 'h':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[4]);	// Ввод размера кольцевого буфера 
          break;		
     case '2':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[1]); // Частота калибровки
          break;
		case '9':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[14]);// Амплитуда калибровки
          break;
		
		case 'c':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[0]); // Коэффициент преобразования
          break;
		case 'd':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[1]); // Коэффициент преобразования
          break;
		case 'e':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[2]); // Коэффициент преобразования
          break;
		case 'f':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[3]); // Коэффициент преобразования
          break;
		case '3':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[0]); // Сопротивление калибровочного резистора
          break;
		case '4':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[1]); // Сопротивление калибровочного резистора
          break;
		case '5':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[2]); // Сопротивление калибровочного резистора
          break;
		case '6':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[3]); // Сопротивление калибровочного резистора
          break;
		case '7':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[0]); // Постоянная времени катушки
          break;
		case '8':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[1]); // Постоянная времени катушки
          break;
		case 'a':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[2]); // Постоянная времени катушки
          break;
		case 'b':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[3]); // Постоянная времени катушки
          break;
		
	

		
	
      }
      break;	 
			
			case 'M':
      
      switch (env[2]) {
				
				case 'A':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[15]); // Имя канала
          break;
				case 'B':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[16]); // Имя канала
          break;
				case 'C':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[17]); // Имя канала
          break;
				case 'D':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[18]); // Имя канала
          break;
				case 'E':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[19]); // Имя канала
          break;
				case 'F':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[20]); // Имя канала
          break;
				case 'G':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[21]); // Имя канала
          break;
				case 'H':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[22]); // Имя канала
          break;
    
		case 'c':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[4]); // Коэффициент преобразования
          break;
		case 'd':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[5]); // Коэффициент преобразования
          break;
		case 'e':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[6]); // Коэффициент преобразования
          break;
		case 'f':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_KP[7]); // Коэффициент преобразования
          break;
		case '3':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[4]); // Сопротивление калибровочного резистора
          break;
		case '4':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[5]); // Сопротивление калибровочного резистора
          break;
		case '5':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[6]); // Сопротивление калибровочного резистора
          break;
		case '6':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_RR[7]); // Сопротивление калибровочного резистора
          break;
		case '7':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[4]); // Постоянная времени катушки
          break;
		case '8':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[5]); // Постоянная времени катушки
          break;
		case 'a':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[6]); // Постоянная времени катушки
          break;
		case 'b':
          len = sprintf((char *)buf,(const char *)&env[4],SB_param.lcd_GG[7]); // Постоянная времени катушки
          break;
			
	
      }
      break;	 
			 
			 
				  case 'e':
      // NAND Flash size //
///		 len += sprintf((char *)(buf+len),"<tr align=\"center\">");
///		 switch (env[2]) {
///					case 'g':
		  /* Write Date. */
 //         len = sprintf((char *)buf,(const char *)&env[4],ffree("N0:"));
///      	}
			break;
/*	
case 'b':
      // LED control - file 'led.cgi' //
      if (env[2] == 'c') {
        // Select Control //
        len = sprintf((char *)buf,(const char *)&env[4],LEDrun ? "" : "selected",
                                                        LEDrun ? "selected" : "");
        break;
      }
      // LED CheckBoxes //
      id = env[2] - '0';
      if (id > 7) {
        id = 0;
      }
      id = 1 << id;
      len = sprintf((char *)buf,(const char *)&env[4],(P2 & id) ? "checked" : "");
      break;					
*/
  
	


 // ============ Мех команды ===============
     case 'g':
	   
      // AD Input CH1- file 'ad.cgi' 
      switch (env[2]) {
        case '1':
//						adv = AD_in (1);
	          len = sprintf((char *)buf,(const char *)&env[4],(float)NAK_X);
          break;
                
      	}
	  
      break;

   case 'h':
	  
      // AD Input CH2- file 'ad.cgi' 
      switch (env[2]) {
        case '1':
//					adv = AD_in (2);	
          len = sprintf((char *)buf,(const char *)&env[4],(float)NAK_Y);
          break;
                
		  }
      
      break;
 
	case 'f':
      // AD Input CH3- file 'ad.cgi' 
      switch (env[2]) {
        case '1':   
//					adv = AD_in (3);
          len = sprintf((char *)buf,(const char *)&env[4],(float)NAK_S);
          break;
                
      }
      break;
			
			

	case 'j':
      /* AD Input - file 'ad.cgi' */
      switch (env[2]) {
        case '1':
 //         adv = SD_in (1);
          len = sprintf((char *)buf,(const char *)&env[4],(float)OTKL_X);
          break;
        
        
      }
      break;
			
		case 'k':
	  
      // AD Input CH2- file 'ad.cgi' 
      switch (env[2]) {
        case '1':
//					adv = SD_in (2);
		      len = sprintf((char *)buf,(const char *)&env[4],(float)OTKL_Y);
          break;
        
        
		  }
      
      break;
  
	case 'l':
      // AD Input CH3- file 'ad.cgi' 
      switch (env[2]) {
        case '1':
//   				adv = SD_in (3);
          len = sprintf((char *)buf,(const char *)&env[4],(float)OTKL_Z);
          break;
        
        
      }
      break;	
			
	case 'u':
      // AD Input CH3- file 'battons.cgi' 
      switch (env[2]) {
        case '1':
          len = sprintf((char *)buf,(const char *)&env[4],(float)Temperatura);
          break;
        
        
      }
      break;




    case 'L' :   //Механические команды	и калибровка
      	   if(env[1] =='1')
   {
               
               // Механические команды //
             len = sprintf((char *)buf,(const char *)&env[2],(PCState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
	   }
		 
				 
			   if(env[1] =='2')
			   {
               
               // Выбор вида калибровки //
               len = sprintf((char *)buf,(const char *)&env[2],(PCLState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
            
				 
				 if(env[1] =='3')
			   {
               
               // Выбор группы //
               len = sprintf((char *)buf,(const char *)&env[2],(PAState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
				 if(env[1] =='4')
			   {
               
               // Выбор канала //
               len = sprintf((char *)buf,(const char *)&env[2],(PBState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
             break;

	case 'P' :   //скорость передачи GPS
        	   if(env[1] =='1')
			   {
               len = sprintf((char *)buf,(const char *)&env[2],(PickState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
               break;


	case 'R' :   //протокол передачи GPS
        	   if(env[1] =='1')
			   {
               len = sprintf((char *)buf,(const char *)&env[2],(PiState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
               break;
	case 'Q' :   // Чётность
        	   if(env[1] =='1')
			   {
               len = sprintf((char *)buf,(const char *)&env[2],(PickStateQ == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
               break;


	case 'S' :   //Стоповые биты 
        	   if(env[1] =='1')
			   {
               len = sprintf((char *)buf,(const char *)&env[2],(PiStateS == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
               break;





   case 'D' :   //частота дискретизации АЦП
        	   if(env[1] =='1')
			   {
               len = sprintf((char *)buf,(const char *)&env[2],(ParamState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
	
  //             break;
						if(env[1] =='2')
			   {
               len = sprintf((char *)buf,(const char *)&env[2],(P2ramState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
	
 //              break;
						if(env[1] =='3')
			   {
               len = sprintf((char *)buf,(const char *)&env[2],(P3ramState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
	
               break;		 

   case 'N' :   //время накопления АЦП
        	   if(env[1] =='1')
			   {
               
               len = sprintf((char *)buf,(const char *)&env[2],(ParState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
               break;


   case 'F' :   //фильтрация АЦП
        	   if(env[1] =='1')
			   {
               
               len = sprintf((char *)buf,(const char *)&env[2],(PaState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
  //             break;
				 if(env[1] =='2')
			   {
               
               len = sprintf((char *)buf,(const char *)&env[2],(P2State == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
 //              break;
				 if(env[1] =='3')
			   {
               
               len = sprintf((char *)buf,(const char *)&env[2],(P3State == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
               break;

   case 'K' :   //Коэффициент усиления АЦП
        	   if(env[1] =='1')
			   {
               
               len = sprintf((char *)buf,(const char *)&env[2],(PState == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
 //              break;
				  if(env[1] =='2')
			   {
               
               len = sprintf((char *)buf,(const char *)&env[2],(PSt2te == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
//               break;
				  if(env[1] =='3')
			   {
               
               len = sprintf((char *)buf,(const char *)&env[2],(PSt3te == env[2])? "selected = Yes" : "");	  //output selected dropdown option
			   }
               break;
				 
				 
// ==================== Калибровка =====================
	
	case 's':
	  // 3 - xml file 'cl.cgx' //
           len = sprintf((char *)buf,(const char *)&env[1],clb_time);
      break;
				 
// =================== Механика ========================
	case 't':
	  //  - xml file 'ad.cgx' //
           len = sprintf((char *)buf,(const char *)&env[1],m_time_st);
      break;
	
	 case 'y':
      // Button state - xml file 'battons.cgx'  Опрос входов контактных датчиков
	  	   len = sprintf((char *)buf,"<checkbox><id>button%c</id><on>%s</on></checkbox>",
                    env[1],(get_button () & (1 << (env[1]-'0'))) ? "true" : "false");
				
	  break;
	
///*
    case 'x':
      // AD Input1 - xml file 'ad.cgx' 
 				
									len = sprintf((char *)buf,(const char *)&env[1],(float)NAK_X);   
																																			 
	    break;
		
		case 'q':
	  // AD Input2 - xml file 'ad.cgx' 
												
									len = sprintf((char *)buf,(const char *)&env[1],(float)NAK_Y);
      break;
 
		case 'z':
	  // AD Input3 - xml file 'ad.cgx' 
						
									len = sprintf((char *)buf,(const char *)&env[1],(float)NAK_S);
      break;

	case 'i':
      // AD Input1 - xml file 'ad.cgx' 
 					
									len = sprintf((char *)buf,(const char *)&env[1],(float)OTKL_X);
	  break;
	case 'o':
	  // AD Input2 - xml file 'ad.cgx' 
						
									len = sprintf((char *)buf,(const char *)&env[1],(float)OTKL_Y);
      break;
 
	case 'p':
	  // AD Input3 - xml file 'ad.cgx' 
							
									len = sprintf((char *)buf,(const char *)&env[1],(float)OTKL_Z);
      break;
	
	case 'W':
	  // AD Input3 - xml file 'battons.cgx' 
							
									len = sprintf((char *)buf,(const char *)&env[1],(float)Temperatura);
      break;
	
	
	
	case 'r':
      // Button state - xml file 'ad.cgx' //
	 
      len = sprintf((char *)buf,"<checkbox><id>kvit%c</id><on>%s</on></checkbox>",
                    env[1],(get_button_1 () & (1 << (env[1]-'0'))) ? "true" : "false");
      break;
			
	case 'm':
      // Button state - xml file 'ad.cgx' //
	 
      len = sprintf((char *)buf,"<checkbox><id>butt%c</id><on>%s</on></checkbox>",
                    env[1],(get_button_2 () & (1 << (env[1]-'0'))) ? "true" : "false");
      break;	
	  
  }
  return ((U16)len);
}
/*----------------------------------------------------------------------------
 *        Print size in dotted fomat
 *---------------------------------------------------------------------------*/
 ///*
static void dot_format (U32 val, char *sp) {

   if (val >= (U32)1e9) {
      sp += sprintf (sp,"%d.",val/(U32)1e9);
      val %= (U32)1e9;
      sp += sprintf (sp,"%03d.",val/(U32)1e6);
      val %= (U32)1e6;
      sprintf (sp,"%03d.%03d",val/1000,val%1000);
      return;
   }
   if (val >= (U32)1e6) {
      sp += sprintf (sp,"%d.",val/(U32)1e6);
      val %= (U32)1e6;
      sprintf (sp,"%03d.%03d",val/1000,val%1000);
      return;
   }
   if (val >= 1000) {
      sprintf (sp,"%d.%03d",val/1000,val%1000);
      return;
   }
   sprintf (sp,"%d",val);
}

	 // */
#endif

 /*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/


