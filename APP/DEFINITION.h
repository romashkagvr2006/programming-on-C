#include <LPC22XX.H>

#define VERSION        "METEO_TEST_1"

//#define DEBUG_OUTPUT_ENABLE

// Device definition

#define	USE_RSS_RMGD
//#define USE_KIT
//#define USE_SIMULATOR

// Internal ROM bounds
#define ROM_CODE_START 0x00000000
#define ROM_CODE_END   0x0001BFFF // 112 k

//                     0x0001C000
//                     0x0001FFFF // 16 k NOT USED

#define ROM_DISK_START 0x00020000
#define ROM_DISK_END   0x0003BFFF // 112 k

#define ROM_DATA_START 0x0003C000 // 16 k = 2 x 8 k
#define ROM_DATA_END   0x0003FFFF // 0 .. 256 k

// Extended RAM bounds
#define RAM_AREA       0x81000000
#define RAM_SIZE       1024*1024
#define RAM_TOP        0x810FFFFF
#define MAX_BOOT_SIZE  0x0003C000
#define LOG_TXT_EX     0x810F0000 // 64 kb for variables 

#ifdef USE_SIMULATOR
  #define VAR_SECTOR     0x8003C000
#else
  #define VAR_SECTOR     0x0003C000
#endif

// Clocks
#define SYSCLK         4*14745600      // SYSCLK frequency in Hz
#define PCLK           SYSCLK		   
#define BAUDRATE       115200          // Baud Rate for UART0,UART1
#define TCLK           10              // Timer Clock rate 10 Hz
#define TCNT           (SYSCLK/TCLK) // Timer Counts

// Types
#define T_NOTHING      0
#define T_U32          1
#define T_FLOAT        2
#define T_CHAR         3

// Sizes
#define HTMLBUF_SZ     128   // HTML buffer size
#define PAGE_SZ        1024  // Flash page Size
#define LOG_SZ         128   // Log file size   (char) 
#define LOG_EX_SZ      128  // Log extended file size (char) 
#define CMD_SZ         128   // CMD line size   (char) 

// Command source
#define AUTORUN_SRC	   1
#define CONSOLE_SRC	   2
#define TELNET_SRC	   3
#define HTTP_SRC       4
#define TFTP_SRC       5

// ASCII
#define DEL            0x7F
#define BACKSPACE      0x08
#define CR             0x0D
#define LF             0x0A
#define ESC            0x1B

// MAC used by DM9000
/*
#define _MAC1          0x1E
#define _MAC2          0x30
#define _MAC3          0x6C
#define _MAC4          0xA2
#define _MAC5          0x45
#define _MAC6          0x5E
*/
// File handlers
#define ISTTY          0x8004        // TTY Files 

#define COMMAND_TXT    0x8004        // File "commang.txt"
#define LOG_TXT        0x8005        // File "log.txt"
#define SETTINGS_HTM   0x8006        // File "settings.htm"
#define SETTINGS_BIN   0x8007        // File "settings.bin"
#define FIFO_HTM       0x8008        // File "fifo.htm"
#define FIFO_BIN       0x8009        // File "fifo.bin"
#define RAM_HTM        0x800C        // File "ram.htm"
#define RAM_BIN        0x800D        // File "ram.bin"
#define BOOT_HEX       0x800E        // File "boot.hex"
#define BOOT_ARM       0x800F        // File "boot.arm"

// COMMON settings
#define SIGNATURE_VAL  0x5555AAAA

#define SIGNATURE	   FlashPage[0]  // Сигнатура 
#define STATUS         FlashPage[1]  // Биты ошибок и событий
#define LAST_SETTING   FlashPage[2]  // Последняя ячейка таблицы 0..255
//#define DEV_NUMBER     FlashPage[3]  // Заводской номер прибора
//#define DEV_TYPE       FlashPage[4]  // Тип прибора (СУПИ91 --> 91)
#define DATA_START     FlashPage[5]  // Начало массива fifo/flash/ram
#define DATA_LENGTH    FlashPage[6]  // Длина массива  fifo/flash/ram
#define MAC_LEAST      FlashPage[7]  // MAC адрес 0..3 байты
#define MAC_MOST       FlashPage[8]  // MAC адрес 4..5 байты
//#define IP_ADDR        FlashPage[9]  // IP  адрес
#define IP_ADDR        FlashPage[21]  // IP  адрес
#define TCP_TIMEOUT    FlashPage[10] // TCP тайм-аут 1000 мс

// 11 .. 34  Device specific

// 35 .. 222 Reserved

#define CODE_CHECK     FlashPage[223]// Code check sum

#define AUTO_RUN       256 - (CMD_SZ/4) // 224 .. 255 --> AUTO COMMAND_CGI 

// Errors & Events
#define ER_BAD_COMMAND   0x00000001 // Invalid command
#define ER_BAD_PARAMETER 0x00000002 // Invalid parameter
#define ER_BAD_HEX_FILE  0x00000010 // Bad boot hex file
#define EV_DATA_READY    0x80000000 // Data ready
		
// BIT definition
#define B_00  0x00000001
#define B_01  0x00000002
#define B_02  0x00000004
#define B_03  0x00000008

#define B_04  0x00000010
#define B_05  0x00000020
#define B_06  0x00000040
#define B_07  0x00000080

#define B_08  0x00000100
#define B_09  0x00000200
#define B_10  0x00000400
#define B_11  0x00000800

#define B_12  0x00001000
#define B_13  0x00002000
#define B_14  0x00004000
#define B_15  0x00008000

#define B_16  0x00010000
#define B_17  0x00020000
#define B_18  0x00040000
#define B_19  0x00080000

#define B_20  0x00100000
#define B_21  0x00200000
#define B_22  0x00400000
#define B_23  0x00800000

#define B_24  0x01000000
#define B_25  0x02000000
#define B_26  0x04000000
#define B_27  0x08000000

#define B_28  0x10000000
#define B_29  0x20000000
#define B_30  0x40000000
#define B_31  0x80000000


	   


#ifdef USE_RSS_RMGD
//-----------------------------------------------------------------------------
// USE_RSS_RMGD USE_RSS_RMGD USE_RSS_RMGD USE_RSS_RMGD USE_RSS_RMGD 
//-----------------------------------------------------------------------------
//   <h>Remote IP Address
//   ====================
//
//     <o>IP1: Address byte 1 <0-255>
//     <i> Default: 192
#define IP1            10

//     <o>IP2: Address byte 2 <0-255>
//     <i> Default: 168
#define IP2            0

//     <o>IP3: Address byte 3 <0-255>
//     <i> Default: 0
#define IP3            0

//     <o>IP4: Address byte 4 <0-255>
//     <i> Default: 100
#define IP4            7

//   <o>Remote Port <1-65535>
//   <i> Do not set number of port too small,
//   <i> maybe it is already used.
//   <i> Default: 1001
//#define PORT_NUM       8500




#define UxLSR    U0LSR                  // UART0
#define UxTHR    U0THR
#define UxRBR    U0RBR

#define SxSPCR   S1SPCR	                // SPI1 --> SD
#define SxSPSR   S1SPSR
#define SxSPDR   S1SPDR
#define SxSPCCR	 S1SPCCR


#define SETBIT(x,y)  (x |= (y))
#define CLEARBIT(x,y)  (x &= (~y))
#define CHECKBIT(x,y)	 (x &(y))

#define	SUCAL 		128
#define	STOP   		64
#define SUCAL_ON	32
#define RESET  		16			    //flag
#define GPS_INT    	8
#define ACKNACK		4	    
#define ISP	   		2
#define USTIR  		1

#define	NMEA 		128
#define GPS	        64
#define FILTR	    32
#define SEND	   	16
#define PREPARE	   	8				//flag1
#define SLEP     	4
#define PPS   		2
#define ZAPROS_ON	1

#define METEO	       64
#define IPD	        32
#define TF	        16
#define GLOBAL_ON	8
#define CALC		4
#define AMPL		2				//
#define GPS_UART   	1			    //flag2

#define UART3_TX			32     // flag4
#define UART3_OUT			16

#define MAX 4900

#define LocM   localm[NETIF_ETH]
#define	DECIM          3	 // коэффициент прореживания после АЦП

#define SET_CS_SD    IOSET3 = B_24	    // P3.24 --> CS SD
#define CLR_CS_SD    IOCLR3 = B_24

#define ON_DISK_LED  IOSET0 = B_10      // P0.10 --> LCD_LIGHT;
#define OFF_DISK_LED IOCLR0 = B_10

#define ON_LED1      IOSET0 = B_10
#define OFF_LED1     IOCLR0 = B_10      // P0.10 --> LCD_LIGHT;

#endif  // USE_RSS_RMGD 

