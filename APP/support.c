#include <LPC22xx.h>
#include <stdio.h>
#include <RTL.h>
#include "..\APP\EXTERNALS.h"
#include <File_Config.h>

//------------------------------------------------------
//  Calculate check sum 0x00000000 .. 0x0001BFFF (112 k) 
//------------------------------------------------------
U32 get_code_check(void) {
U32 sum;
U32 i;
U32 * ram;

sum = 0; ram = (U32*) (0x00000000);
for(i = 0; i < (0x0001C000/4); i++) sum += ram[i];
return(sum);
}

//--------------------------------
//  Dump frame 
//--------------------------------

void dump_frame(unsigned char rw, char* buffer, unsigned int buffer_length) {
unsigned int  i;
unsigned char j;
unsigned char k;
unsigned char text[17];

// Print the number of bytes received/sended.      
if(rw != 0x80)
  {
  if(rw) printf("\nReceived "); else printf("\nSended ");
  printf("%i bytes", buffer_length);
  }         

// Print each byte to the UART0 terminal
i=0; j=0;
while(1)
  {
  // Print ASCII and create a new row every 16 bytes
  if(j==0x00)
    {
	if(i) { k=0; while(text[k]) putchar(text[k++]); }
    if(rw == 0x80)
	  {
      if(i<buffer_length) printf("\n%08X - ", buffer + i); else break;
	  }
	else
	  {
      if(i<buffer_length) printf("\n%04X - ", i); else break;
      }
	}

  if(i<buffer_length)
    {
    // Prepare ASCII string
    text[j]=buffer[i]; text[j+1]=0;
    if( (text[j]<32) || (text[j]>126) ) text[j]='.'; 

    // Print the byte
	printf("%02X ", buffer[i]); 
    }
  else printf("   ");

  i++;
  j= i & 0x000F;

  if((j & 0x07) == 0x00) putchar(' ');
  }

printf("\n"); fflush (stdout);

}

//-----------------------------------------------------------------------------
// Write byte to extended RAM
//-----------------------------------------------------------------------------
//
void wr_ex_ram(U32 addr,U8 b) {
ex_ram_buf[0] = *(U32*)(addr&0xFFFFFFFC);
*(U8*)((U8*)ex_ram_buf + (addr & 0x00000003)) = b;
*(U32*)(addr & 0xFFFFFFFC) = ex_ram_buf[0];
}

//-----------------------------------------------------------------------------
// Read byte from extended RAM
//-----------------------------------------------------------------------------
//
U8 rd_ex_ram(U32 addr) {
ex_ram_buf[0] = *(U32*)(addr&0xFFFFFFFC);
return(*(U8*)( (U8*)ex_ram_buf + (addr & 0x00000003)) );
}
 /*
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

  // Timer tick every 100 ms
  timer_tick();


  }
}

   */
	/*
//----------------------------------------------------------------------------
//      SPI Driver Functions
//----------------------------------------------------------------------------
//  Required functions for SPI driver module:
//   - void spi_init ()
//   - U8   spi_send (U8 outb)
//   - void spi_hi_speed (BOOL on)
//---------------------------------------------------------------------------

void spi_hi_speed (BOOL on) {
// Set a SPI clock speed to desired value

if (on == __TRUE)
  {
// Max. 20 MBit used for Data Transfer
  SxSPCCR = 8;   // SCK = PCLK/8 = 14745600/8 = 1_843_200  Hz
  }
else
  {
// Max. 400 kBit used in Card Initialization
  SxSPCCR = 37;  // SCK = PCLK/37 = 14745600/37 = 398_530 Hz
  }
}
//--------------------------- spi_ss ----------------------------------------//

void spi_ss (U32 ss) {
   // Enable/Disable SPI Chip Select //

   if (ss) {
      // SSEL is GPIO, output set to high. //
      IO3SET = 1<<24;
   } 
   else {
      // SSEL is GPIO, output set to low. //
      IO3CLR = 1<<24;
   }
}

U8 spi_send (U8 outb) {

// Write and Read a byte on SPI interface
U8 inb;



SxSPDR = outb;
while ((SxSPSR & 0x80) == 0);
inb = SxSPDR;



return (inb);

}

void spi_init (void) {
// Initialize and enable the SSP Interface module
U32 i;

// SSEL is GPIO, output set to high
// IODIR0  |= 1<<20; // P0.20 (SSEL1) --> out
// IOSET0   = 1<<20; // P0.20 (SSEL1) --> High

// Enable SPI in Master Mode, CPOL=1, CPHA=1 (Clock low-active)
SxSPCR  = 0x38;     // CPL0 = 1 , CPHA = 1 , MSTR = 1 , LSBF = 0
spi_hi_speed (__FALSE);

// Send SPI Command with card not selected at 400 KBit
for (i = 0; i < 16; i++)
  {
  SxSPDR = 0xFF;
  while ((SxSPSR & 0x80) == 0);
  }
wait_ms(1);
}

//----------------------------------------------------------------------------
//      Restore SPI Driver for SD card
//----------------------------------------------------------------------------
void restore_spi_SD(void) {
SxSPCR  = 0x38;     // CPL0 = 1 , CPHA = 1 , MSTR = 1 , LSBF = 0

// Max. 20 MBit used for Data Transfer
SxSPCCR = 8;        // SCK = PCLK/8 = 14745600/8 = 1_843_200  Hz

}
			  */
//------------------------------------------------------------------------------
//   Send char 
//------------------------------------------------------------------------------

int sendchar (int ch)  {                 // Write character to Serial Port

if (ch == '\n')
  {
  while (!(UxLSR & 0x20));
  UxTHR = 13;                            // output CR
  }

while (!(UxLSR & 0x20));
return (UxTHR = ch);
}
			
//------------------------------------------------------------------------------
//   Get key 
//------------------------------------------------------------------------------

int getkey (void)  {                     // Read character from Serial Port
while (!(UxLSR & 0x01));
return (UxRBR);
}

//------------------------------------------------------------------------------
//   Init Console 
//------------------------------------------------------------------------------
	/*
void Init_Console(void) {
printf("\n%s Version "VERSION"",dev_name);
printf(" Code check "); 
if(CODE_CHECK == get_code_check()) printf("OK");
else                               printf("ERROR!"); 
printf(" (Type 'H' for help)"); 
fflush (stdout);
///process_cmd_start(AUTORUN_SRC, (char*)(FlashPage + AUTO_RUN));
}
	  */
//------------------------------------------------------------------------------
//  Main Console
//------------------------------------------------------------------------------
	  /*
void Main_Console(void) {
U8 c;

if(!(UxLSR & 0x01)) return;

c=getkey();

if(command_complete == 0)
  {
  if( (c == 'x') || (c == 'X') ) command_escape = 1;
  return;
  }

switch (c)
  {
  case BACKSPACE:
  case DEL:
  if (pCommand_cgi == 0) break;
  pCommand_cgi--;                // decrement count
  sendchar(0x08);                // echo backspace
  sendchar(' ');
  sendchar(0x08);
  return;
    
  case CR:
  Command_cgi[pCommand_cgi++] = 0;
///  process_cmd_start(CONSOLE_SRC,Command_cgi);
  return;
      
  default:
  if(pCommand_cgi >= CMD_SZ - 1) { Command_cgi[0] = 0; break;	} // Ignore and clear command_cgi
  sendchar(c);                       // echo
  Command_cgi[pCommand_cgi++] = c;   // store character and increment line pointer
  return;
  }
}
	*/
