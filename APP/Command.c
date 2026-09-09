
#include <LPC22XX.H>
#include <Net_Config.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "..\APP\EXTERNALS.h"


//----------------
// Pass delimitor 
//----------------
void pass_delimitor(U32 * p) { 
char c;

while(*p < CMD_SZ)
  {
  c = Command_cgi[*p];
  if( (c == ',') || (c == ' ') ) (*p)++; else return;
  }
}

//-------------
// Put log char 
//-------------
void put_log_char(char ch) {

if(command_src == CONSOLE_SRC)
  {
  if(ch == '\n') { putchar(13); putchar(10); }
  else             putchar(ch);
  }

if(ch == '\n')
  {
  if(pLog_txt_end < LOG_SZ)    Log_txt   [pLog_txt_end++] = 13;
  else
    {
///    if(pLog_txt_end < LOG_EX_SZ) wr_ex_ram(LOG_TXT_EX + (pLog_txt_end++) , 13);
    }
  }

if(pLog_txt_end < LOG_SZ)    { Log_txt   [pLog_txt_end++] = ch; return; }
///if(pLog_txt_end < LOG_EX_SZ) { wr_ex_ram(LOG_TXT_EX + (pLog_txt_end++) , ch); return; }

}

//-------------
// Get log char 
//-------------
char get_log_char(void) {

if(pLog_txt >= pLog_txt_end) return(0);

if(pLog_txt < LOG_SZ)    return(Log_txt   [pLog_txt++]);
//if(pLog_txt < LOG_EX_SZ) return(rd_ex_ram(LOG_TXT_EX + (pLog_txt++)));

return(0);
}

//-----------
// Print log 
//-----------
void print_log(char * txt, char tp, void * v) { 
char str[64];
U32  i;

i = 0; 
  if(tp)
  {
  if(tp == T_U32)     sprintf(str, txt,   *(U32*)v);
  if(tp == T_FLOAT)   sprintf(str, txt, *(float*)v);
  if(tp == T_CHAR)    sprintf(str, txt, *(char *)v);
  while(str[i]) { put_log_char(str[i]); i++; }
  }
else
  {
  while(txt[i]) { put_log_char(txt[i]); i++; }
  }

if(command_src == CONSOLE_SRC) fflush (stdout);
}

//---------------------
// Print capture state      
//---------------------
void print_capture_state(void) {
//print_log("Capture     : ", 0, 0); 
//if(capture) print_log("enabled\n", 0,0);
//else        print_log("disabled\n",0,0); 
}

//---------------------
// Print check code      
//---------------------
void print_check_code(void) {
print_log("Code check  : ", 0, 0); 
///if(CODE_CHECK == get_code_check()) print_log("ok\n", 0,0);
//else                               print_log("ERROR!\n",0,0); 
}

//---------------------
// Print system info      
//---------------------

void print_sys_info(void){
U32 u;

print_log("Version     : "VERSION"\n", 0, 0); 
//print_check_code();
//print_capture_state();


//u = own_hw_adr[0]; print_log("MAC         : %02X-",T_U32, &u);
//u = own_hw_adr[1]; print_log("%02X-", T_U32, &u);
//u = own_hw_adr[2]; print_log("%02X-", T_U32, &u);
//u = own_hw_adr[3]; print_log("%02X-", T_U32, &u);
//u = own_hw_adr[4]; print_log("%02X-", T_U32, &u);
//u = own_hw_adr[5]; print_log("%02X\n",T_U32, &u);

//u = localm[0].IpAdr[0]; print_log("Local IP    : %u.",T_U32, &u);
//u = localm[0].IpAdr[1]; print_log("%u.",T_U32, &u);
//u = localm[0].IpAdr[2]; print_log("%u.",T_U32, &u);
//u = localm[0].IpAdr[3]; print_log("%u\n",T_U32, &u);

//print_log("DM9000_VID  : %08X\n",T_U32, &DM9000_VendorID);
//print_log("DM9000_PID  : %08X\n",T_U32, &DM9000_ProductID);

//print_log("Command src : ", 0, 0); 
//if(command_src == CONSOLE_SRC) print_log("COM\n",    0,0);
//if(command_src == AUTORUN_SRC) print_log("AUTORUN\n",0,0);
//if(command_src == TELNET_SRC)  print_log("TELNET\n", 0,0);
//if(command_src == HTTP_SRC)    print_log("HTTP\n",   0,0);
//if(command_src == TFTP_SRC)    print_log("TFTP\n",   0,0);
}

//----------------------
// Process command stop 
//----------------------

void process_cmd_stop(void) {

char   c;

command_complete = 1;
command_phase    = 0;
command_escape   = 0;
Command_cgi[0]   = 0;
pCommand_cgi     = 0;

///if(flash_changed) { var_save(); flash_changed = 0; }

if(command_src != CONSOLE_SRC)
  {
  pLog_txt = 0; while(1) { c = get_log_char(); if(c == 0) break; putchar(c); };
  }
printf("\nCOM>"); fflush (stdout);
}

//-----------------------
// Process command start 
//-----------------------

void process_cmd_start(U8 src, char * buf) {
U8 i;

command_src = src;

printf("\n");

if( (strlen(buf) >= CMD_SZ) || (buf[0] == 0) )
  {
  process_cmd_stop();
  return;
  }

if(command_complete == 0)
  {
  if( (buf[0] == 'x') || (buf[0] == 'X') ) {  command_escape = 1; }
  return;
  }

if( (command_src == AUTORUN_SRC)||
    (command_src == TELNET_SRC)	||
    (command_src == HTTP_SRC)
  )
  strcpy(Command_cgi,buf);

if(command_src == TFTP_SRC)
  {
  for(i = 0; i < CMD_SZ; i++)
    {
	if( (buf[i] == 13) || (buf[i] == 0 ) ) { Command_cgi[i] = 0; break; }
	Command_cgi[i] = buf[i];
    }
  }

command_escape   = 0;
command_complete = 0;
command_phase    = 0;

pLog_txt_end     = 0;

pCommand_cgi     = 0;
pass_delimitor(&pCommand_cgi); 
pCommand_next    = pCommand_cgi + 1;

if(command_src == AUTORUN_SRC) printf("AUTORUN>");
if(command_src == TELNET_SRC)  printf("TELNET>");
if(command_src == HTTP_SRC)	   printf("HTTP>");
if(command_src == TFTP_SRC)	   printf("TFTP>");
if(command_src != CONSOLE_SRC) printf("%s\n", Command_cgi);
fflush (stdout);
}

//------------------------------------
// Extract parameter from Commang_cgi 
//------------------------------------
#define BAD_PARAM  1
#define NO_PARAM   2

U8 get_parameter(U8 n , U32 inf , U32 sup) {
U32 v;
U8  ch;
U8  i;
U8  c;

pass_delimitor(&pCommand_next); 

ch = Command_cgi[pCommand_next];

if( (ch < '0') || (ch > '9') )
  {
  if(n == 1)
    {
    if( (default_v1 < inf) || (default_v1 > sup) ) return(BAD_PARAM);
	}
  else
    {
    if( (default_v2 < inf) || (default_v2 > sup) ) return(BAD_PARAM);
	}

  return(NO_PARAM);
  }

ch = Command_cgi[pCommand_next + 1];

if( (ch == 'x') || (ch == 'X') ) // HEX
  {
  c = 0; pCommand_next += 2;
  for(i = 0; i < 8; i++)
    {
	ch = 0x20 | Command_cgi[pCommand_next + i];
    if( ((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) ) c++; else break;
    }

  if(c > 0) sscanf(Command_cgi + pCommand_next, "%x",&v);
  else return(BAD_PARAM);
  }
else                                                                      //DEC   
  {
  c = 0;
  for(i = 0; i < 8; i++)
    {
	ch = Command_cgi[pCommand_next  + i];
    if( (ch >= '0') && (ch <= '9') ) c++; else break;
    }
  if(c > 0)sscanf(Command_cgi + pCommand_next, "%u",&v);
  else return(BAD_PARAM);
  }
 
if( (v < inf) || (v > sup) ) return(BAD_PARAM);

pCommand_next +=  c;
if(n == 1) default_v1 = v;  else default_v2 = v;
return(0);

}

//-----------------
// Process command 
//-----------------

void Process_Command(void) {
U32 a;
U32 i;
U32 v;
U8  r, mus[4];



if(command_complete) return;

switch(Command_cgi[pCommand_cgi])
  {
  case 0   : process_cmd_stop(); return;

  case '$' :
  strcpy((char*)(FlashPage + AUTO_RUN), Command_cgi + pCommand_next);
  flash_changed = 1;
  process_cmd_stop();
  return;


//-------------------------------------------------------------------------------
//   Вывешивание
//--------------------------------------------------- 
  case 'a' :  
  case 'A' :  


	

	 print_log("Вывешивание", T_U32, &a);

   goto next;
//------------задать IP АДРЕС удаленного сервера------------------
  case 'B' :
  case 'b' :

  goto next;
 //-------------------------------------------------------------------------------
  case 'c' :  break;
  case 'C' :  break;


//   goto next;

//-----------------------------------------------------
//	Включить фильтрацию
//-----------------------------------------------------
  case 'd' :
  case 'D' :
	 	  

  goto next;
//-------------------------------------------------------------------------------
  case 'e' :  break;
  case 'E' :  break;


//   goto next;

// --------------------------------------------------
//  Установка частоты дискретизации
// --------------------------------------------------

  case 'f' :
  case 'F' :
	
  r = get_parameter(1,0,0xFFFFFFFF);
  if(r == BAD_PARAM) goto param_error;
  if(r != NO_PARAM)  default_addr = default_v1;	  // 
   
//  data_rate = default_v1;	  // Задаю частоту дискретизации


//  	 set_data_rate();

//	 Start_Dev();

			
  print_log("Частота дискретизации", T_U32, &a);


  goto next;


// ------------------------------------
//   Start measure
// ------------------------------------
  case 'g' :
  case 'G' :
  print_log("Старт\n", 0,0);
   
 

 

  goto next;


// ------------------------------------
//   Short help
// ------------------------------------
  case 'h' :
  case 'H' :
//  print_log((char *)short_help, 0, 0); 
  goto next;

// ------------------------------------
//  Отключить фильтрацию
// ------------------------------------
  case 'i' :
  case 'I' :
	 
		   

  goto next;


// ------------------------------------
//  подгонка частоты для разных кварцев	 12288 - по рассчётное значение
// ------------------------------------	 14,7456/4/12288 = 300 Гц

  case 'j' :
  case 'J' :

	
 
  goto next;

//------------------------------------------------------------
  // ------------------------------------
//    АРЕТИРОВАНИЕ / РАЗАРЕТИРОВАНИЕ
// ------------------------------------
  case 'k' : //break;		Включить электромагнит РАЗАРЕТИРОВАНИЕ
  case 'K' : //break;
  print_log("РАЗАРЕТИРОВАНИЕ\n", 0,0); 
  
//	   FSUK_KOMANDA[0]=2;		  //команда для ФСУК - РАЗАРЕТИРОВАНИЕ

	goto next;
  
  case 'l' : //break;		  // Выключить электромагнит АРЕТИРОВАНИЕ
  case 'L' : //break;
  print_log("АРЕТИРОВАНИЕ\n", 0,0); 

//	   FSUK_KOMANDA[0]=3;		  //команда для ФСУК - АРЕТИРОВАНИЕ

	goto next;

// ---------------------

// ------------------------------------
//  Reset CPU
// ------------------------------------
  case 'm' :
  case 'M' :
  print_log("Сброс\n", 0,0); 
//((void (*)(void)) (0x00000000)) ();
  ON_LED1;
  PINSEL2 = 0x006000F0;
  WDTC    = 0xFF;     // 18432000 --> Watchdog time-out interval = 5 sec
  WDMOD   = 0x03;     // Watchdog reset enable bit (Set Only)
  WDFEED  = 0xAA;
  WDFEED  = 0x55;
  while(1);

// ------------------------------------
//    ОРИЕНТАЦИЯ
// ------------------------------------
  case 'n' : //break;		 	
  case 'N' : //break;

  print_log("ОРИЕНТАЦИЯ\n", 0,0); 

//FSUK_KOMANDA[0]=1;		  //команда для ФСУК - Ориентация
 
 

  goto next;
// ------------------------------------
// СТОП
// ------------------------------------
  case 'o' :
  case 'O' :

 
 
 
	  print_log("СТОП\n", 0,0);
  goto next;

// ------------------------------------
//  RAM test
// ------------------------------------
  case 'p' : 
  case 'P' :
//  RAM_Test();
  goto next;

// ------------------------------------
//  RESET ФСУК
// ------------------------------------
  case 'q' : //break;
  case 'Q' : //break;
 
//		FSUK_KOMANDA[0]=6;		  //команда для ФСУК - RESET ФСУК

	  print_log("RESET ФСУК\n", 0,0);

  goto next;
// ------------------------------------
//   Read ram
// ------------------------------------
  case 'r' :
  case 'R' :
  r = get_parameter(1,0,0xFFFFFFFF);
  if(r == BAD_PARAM) goto param_error;
  if(r != NO_PARAM)  default_addr = default_v1;
  if(BAD_PARAM == get_parameter(2,0,256))        goto param_error;

  if(default_v2 == 0) v = 1; else v = default_v2;
  a = default_addr & 0xFFFFFFFC;
  for(i = 0; i < v; i++)
    {
	print_log("ram[%08X] = ", T_U32, &a);
    print_log("%08X\n",       T_U32, ((void *) (0x00000000 + a)) );
    a += 4;
	}

  default_addr += default_v2*4;
  goto next;

// ------------------------------------
//   Write settings
// ------------------------------------
  case 's' :
  case 'S' :	 
   
//  reset_ads ();
 
  	   

 /// if(get_parameter(1,1,AUTO_RUN-1)) goto param_error;
  while(1)
    {
	r = get_parameter(2,0,0xFFFFFFFF);
    if(r == NO_PARAM)   goto next;
    if(r == BAD_PARAM)  goto param_error;

    FlashPage[default_v1++] = default_v2;
	flash_changed           = 1; 
    }

// ------------------------------------
//   Read settings
// ------------------------------------
  case 't' :
  case 'T' :
  if(BAD_PARAM == get_parameter(1,0,AUTO_RUN-1))          goto param_error;
  if(BAD_PARAM == get_parameter(2,0,(U32)256 - AUTO_RUN)) goto param_error;

  if(default_v2 == 0) v = 1; else v = default_v2;

  for(i = default_v1; i < default_v1 + v; i++)
    {
    if(i >= AUTO_RUN) break;
	print_log("set[%3u] = ", T_U32, &i);
    print_log("%u\n",        T_U32, &FlashPage[i]);
	}

  default_v1 += default_v2;
  if(default_v1 >= AUTO_RUN) default_v1 = 0;
  goto next;
//-------------------------------------------------------------------------------
  case 'u' : // break;
  case 'U' : // break;

//	 SETBIT(flag2,IPD);		// имитатор потери данных
//	 dl = 3;
//		 test_timer = 0;

   goto next;

// ------------------------------------
//  Калибровка SIN	меньше 1 Гц		 v,0,(10 - 100) мГц
//					больше 1 Гц		 v,1,(1 - 100) Гц
// ------------------------------------
  case 'v' :// break;
  case 'V' :
	  
	  r = get_parameter(1,0,1000);
  if(r == BAD_PARAM) goto param_error;
  if(r != NO_PARAM)  default_addr = default_v1;	  // 
  
//  FSUK_KOMANDA[1]  = default_v1;
   		

  while(1)
    {
	r = get_parameter(2,0,1000);
    if(r == NO_PARAM)   goto next;
    if(r == BAD_PARAM)  goto param_error;


	memmove (&mus[0], &default_v2, 4);
 /*
		  FSUK_KOMANDA[0]=5;		  //команда для ФСУК - Произвести калибровку

		  FSUK_KOMANDA[2]	= mus[0];
		  FSUK_KOMANDA[3]	= mus[1];

		  FSUK_KOMANDA[4]	= 0;
		  FSUK_KOMANDA[5]	= 0;
		  FSUK_KOMANDA[6]	= 0;
		  FSUK_KOMANDA[7]	= 0;
		  FSUK_KOMANDA[8]	= 0;
		  FSUK_KOMANDA[9]	= 0;
		  FSUK_KOMANDA[10]	= 0;
		  FSUK_KOMANDA[11]	= 0;

 		   */


  print_log("Калибровка SIN", T_U32, &a);


  }

	  
  goto next;

// ------------------------------------
//   Write ram
// ------------------------------------
  case 'w' :
  case 'W' :
  r = get_parameter(1,0,0xFFFFFFFF);
  if(r == BAD_PARAM) goto param_error;
  if(r != NO_PARAM)  default_addr = default_v1;
  a = default_addr & 0xFFFFFFFC;
  while(1)
    {
    r = get_parameter(2,0,0xFFFFFFFF);
    if(r == NO_PARAM)   { (*(U32 *) (0x00000000 + a)) = default_v2; goto next; }
    if(r == BAD_PARAM)  goto param_error;
	(*(U32 *) (0x00000000 + a)) = default_v2;
    a += 4;
	}

// ------------------------------------
//  Print sys info
// ------------------------------------
  case 'y' :
  case 'Y' :
  print_sys_info();
  goto next;

// ------------------------------------
//  Repeat command string
// ------------------------------------
  case 'z' :
  case 'Z' :
  if(command_escape) goto esc;
  pCommand_next = 0;
  goto next;

  default  :
  print_log("Недопустимая команда '%c'\n", T_CHAR, &Command_cgi[pCommand_cgi]);
  STATUS |= ER_BAD_COMMAND;
  process_cmd_stop();
  return;
  }

next:  // Next command

  command_phase = 0;
  pCommand_cgi  = pCommand_next;
  pass_delimitor(&pCommand_cgi); 
  pCommand_next = pCommand_cgi + 1;
  return;

esc:
  
  print_log("Команда '%c' прервана\n", T_CHAR, &Command_cgi[pCommand_cgi]);
  process_cmd_stop();
  return;

param_error:

  print_log("Неверный параметр команды '%c'\n", T_CHAR, Command_cgi + pCommand_cgi);
  STATUS |= ER_BAD_PARAMETER;
  process_cmd_stop();
  return;

}
