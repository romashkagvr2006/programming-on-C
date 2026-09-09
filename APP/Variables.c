#include <stdio.h>
#include <string.h>
//#include "..\INC\File_Config.h"
#include <RTL.h>
#include "..\APP\EXTERNALS.h"
#include <File_Config.h>

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------



U32        file_data_count;

// Variables from EXTERNALS.h
float Temperatura = 0.0f;
float NAK_X = 0.0f;
float NAK_Y = 0.0f;
float NAK_S = 0.0f;
U16 clb_time = 0;

// DM9000 Ethernet controller variables
int DM9000_VendorID = 0;
int DM9000_ProductID = 0;
int DM9000_IO_mode = 0;

// Additional variables from EXTERNALS.h
float OTKL_X = 0.0f;
float OTKL_Y = 0.0f;
float OTKL_Z = 0.0f;
float PERIOD = 0.0f;
U8 n_sb = 0;
U32 st_ZAPROS_ON = 0;
BOOL ZPR = __FALSE;
U8 flag1 = 0;
U8 flag2 = 0;
U8 flag4 = 0;
U8 m_time = 0;
U32 st_data_uart3 = 0;
U32 st_adr_serial_3_in = 0;
U8 receive_start_3 = 0;
U8 UART_2_in_CRC = 0;
U16 mark_s = 0;
U32 timeout = 0;
U8 LED1_blink = 0;


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
// Global array variables
//-----------------------------------------------------------------------------

char Log_txt     [LOG_SZ];

char Command_cgi [CMD_SZ];

//U32  FlashPage   [PAGE_SZ/4]; // Flash page buffer = 1024 bytes

char       html_buf[HTMLBUF_SZ];
U32        phtml_buf;

//-----------------------------------------------------------------------------
// Global constants
//-----------------------------------------------------------------------------

const char short_help[] = 
{
"Выберите раздел <Справка>\n"
//"Write : W=ram S=settings L=fifo\n"

//"G    = Start\n"
//"M    = device reset\n"
//"O    = device test\n"
//"P    = RAM test\n"
//"V    = capture\n"
//"X    = Stop\n"
//"Y    = Sys info\n"
//"Z    = Repeat...\n"
};

const char html_settings_head[] = 
{
"<html><head>"
"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\">"
"<title>SETTINGS.HTM</title>"
"</head><body><font face=\"Courier New\">"
"<table border=\"1\" cellspacing=\"1\" width=\"90%\">"
"<tr><td>Индекс</td><td>Значение</td></tr>"
};
  
const char html_fifo_head[] = 
{
"<html><head>"
"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\">"
"<title>FIFO.HTM (СКПФ)</title>"
"</head><body><font face=\"Courier New\">"
"<table border=\"1\" cellspacing=\"1\" width=\"90%\">"
"<tr><td>Канал</td><td>Частота, Гц</td><td>Амплитуда, квант</td><td>Фаза, град</td><td>Отн. Кп</td><td>Кп, дБ</td><td>ЦНРК канала</td></tr>"
};

const char html_ram_head[] = 
{
"<html><head>"
"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\">"
"<title>RAM.HTM</title>"
"</head><body><font face=\"Courier New\">"
"<table border=\"1\" cellspacing=\"1\" width=\"90%\">"

};

const char html_table_tail[] = 
{
"</table></font></body></html>"
};

//---------------------------------
// File system debug      
//---------------------------------

#ifdef USE_SIMULATOR

void fs_debug(void) {
U32 * p = (U32*)(VAR_SECTOR);
U8  * b = (U8*) (0x80000000);

memset(b, 0x40000, 0xFF);
p[0]   = 0x55555555;
p[256] = 0x55555555;
}

#endif

//---------------------------------
// Find last signature in sector 17      
//---------------------------------
U32 * find_signature(void) {

U32  p = VAR_SECTOR + 8192;

do
  {
  p-=1024;
  if( (*(U32*)p ) == SIGNATURE_VAL) return((U32 *)p);
  }
while(p != VAR_SECTOR);

return(0);
}

//---------------------------------
// Compare variables      
//---------------------------------
U32 var_comp( U32 * addr ) {
U32   i;

for(i = 0; i < PAGE_SZ/4; i++)
if(FlashPage[i] != addr[i]) return(0); // FlashPage != Flash

return(1);
}

//---------------------------------
// Save variables to FLASH      
//---------------------------------
void var_save(void) {
U32 * p;
U32   i;

p = find_signature();

if(p == 0)
  {
  fs_EraseSector (VAR_SECTOR);
  fs_ProgramPage (VAR_SECTOR, 1024, (U8*)FlashPage);
  return;
  }

if(var_comp(p)) return; // No write if variables not changed

if((U32)p == (VAR_SECTOR + 8192 - PAGE_SZ))
  {
  fs_EraseSector (VAR_SECTOR);
  p = (U32*)VAR_SECTOR;
  }
else p+=PAGE_SZ/4;

for(i = 0; i < PAGE_SZ/4; i++)
   {
   if(p[i] != 0xFFFFFFFF) { fs_EraseSector (VAR_SECTOR); break; }
   }

fs_ProgramPage ((U32)p, 1024, (U8*)FlashPage);
}

//---------------------------------
// Init file system and variables      
//---------------------------------

void Init_VAR(void) {

U32 * p;

// Init stored variables

#ifdef USE_SIMULATOR
fs_debug();
#endif

p = find_signature();

if(p == 0)
  {
  memset(FlashPage, 0, PAGE_SZ);

  SIGNATURE    = SIGNATURE_VAL;
  STATUS       = 0;
  CODE_CHECK   = 0;

//  Init_Var_Dev();
  var_save();
  }
else
  {
  memcpy(FlashPage, p, PAGE_SZ);
  }

// Init non stored variables
	/*
//capture          = 0;
DM9000_VendorID  = 0;
DM9000_ProductID = 0;
DM9000_IO_mode   = 0;

pCommand_cgi     = 0;
pCommand_next    = 0;
pLog_txt         = 0;
pLog_txt_end     = 0;

command_complete = 1;
command_src      = 0;
command_phase    = 0;
command_escape   = 0;
flash_changed    = 0;

default_v1       = 0;
default_v2       = 0;
default_addr     = 0;

LED1_blink       = 0;
LED1_timer       = 0;

phtml_buf        = 0;
html_buf[0]      = 0;
 

		   */
}
