//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <LPC22XX.H>
#include <stdio.h> 
#include "..\APP\DM9000.H" 
#include <Net_Config.h>
#include "..\APP\EXTERNALS.h"


//extern U8 own_hw_adr[];

int        DM9000_VendorID;
int        DM9000_ProductID;
int        DM9000_IO_mode;




//#define PORT_DAT (*((volatile unsigned long *) 0x82000004))
//#define PORT_REG (*((volatile unsigned long *) 0x82000000))
#define PORT_DAT (*((U16 *) 0x82000004))
#define PORT_REG (*((U16 *) 0x82000000))

//#define IOWAIT      (IOPIN3 & 1)

//-----------------------------------------------------------------------------
// Small delay
//-----------------------------------------------------------------------------
void delay(void) { volatile int t; t = 2; while(t--); } // t = 10 --> 1.47 us
 //-----------------------------------------------------------------------------
// Write Command to NIC
//-----------------------------------------------------------------------------


void write_nicreg(U8 addr, U8 val)
{
//  delay();
   PORT_REG = addr;

//  delay();
   PORT_DAT = val;
}

//--------------------------------------------------------------------------------
// Read from NIC
//--------------------------------------------------------------------------------
int read_nicreg(U8 addr)
{
  
//  delay();  
  PORT_REG = addr;
  
//  delay(); 
  return (PORT_DAT);
  
}

//--------------------------------------------------------------------------------
// Read data port
//--------------------------------------------------------------------------------
int read_data(void)
{

//  delay(); 
   return (PORT_DAT);
  
}

//--------------------------------------------------------------------------------
// Write data port
//--------------------------------------------------------------------------------
void write_data(U16 dat)
{
//  delay();
   PORT_DAT = dat;
}

//--------------------------------------------------------------------------------
// Write data port
//--------------------------------------------------------------------------------
void write_reg(U8 reg)
{
//  delay(); 
  PORT_REG = reg;
}

//-----------------------------------------------------------------------------
// Write Command to PHY
//-----------------------------------------------------------------------------

void PHY_write(U16 addr, U16 val)
{
  write_nicreg(DM9000_EPCR,0x0a);					       // Set EEPROM & PHY Control Reg to write
  write_nicreg(DM9000_EPAR,((addr & 0x3f) | DM9000_PHY));  // Set PHY Address Reg to PHY Address
  write_nicreg(DM9000_EPDRH,(val >> 8));	               // write high_byte of PHY data
  write_nicreg(DM9000_EPDRL,(val));			               // write low_byte of PHY data
  write_nicreg(DM9000_EPCR,0x00);					       // Clear EEPCR
}

//-----------------------------------------------------------------------------
// DM9000_Init
//-----------------------------------------------------------------------------

void init_ethernet (void) {
  
 // capture = 0;

  //1. If the internal PHY is required, the following steps are to active the internal PHY:
  // The default status of the DM9000 is to power down the internal PHY by setting the GPIO0.
  // Since the internal PHY have been powered down, the wakeup procedure will be needed to
  // enable the DM9000.

  write_nicreg(DM9000_GPCR, 0x07);    // Power PHY set the GPR to output

  write_nicreg(DM9000_GPR,  0x06);	  // Clear the GPIO lines (Led's off)

  //2. Program NCR register. Choose normal mode by setting NCR (reg_00h) bit[2:1] = 00h. The
  // system designer can choose the network operation such as setting internal/external PHY,
  // enable wakeup event or choose the full-duplex mode. Please refer to the DM9000 datasheet
  // ch.6.1 about NCR register setting.
  // Reset DM9000 (twice)
  
  write_nicreg(DM9000_NCR, 0x03);	// Reset
  wait_ms(1);
  write_nicreg(DM9000_NCR, 0x00);	// Normal mode

  write_nicreg(DM9000_NCR, 0x03);
  wait_ms(1);
  write_nicreg(DM9000_NCR, 0x00);

  //3. Clear TX status by reading NSR register (reg_01h). Bit[2:3] and bit[5] will be automatically
  // cleared by reading or writing 1. Please refer to the DM9000 datasheet ch.6.2 about NSR
  // register setting.
  
  read_nicreg(DM9000_NSR);
 
  //5. Set Node address 6 bytes from in physical address register (reg_10h~15h).
  write_nicreg(DM9000_MAC_REG,  own_hw_adr[0]);
  write_nicreg(DM9000_MAC_REG+1,own_hw_adr[1]);
  write_nicreg(DM9000_MAC_REG+2,own_hw_adr[2]);
  write_nicreg(DM9000_MAC_REG+3,own_hw_adr[3]);
  write_nicreg(DM9000_MAC_REG+4,own_hw_adr[4]);
  write_nicreg(DM9000_MAC_REG+5,own_hw_adr[5]);

  //6. Set Hash table 8 bytes from multicast address register (reg_16h~1Dh).
  write_nicreg(DM9000_MLC_REG,  0xff);
  write_nicreg(DM9000_MLC_REG+1,0xff);
  write_nicreg(DM9000_MLC_REG+2,0xff);
  write_nicreg(DM9000_MLC_REG+3,0xff);
  write_nicreg(DM9000_MLC_REG+4,0xff);
  write_nicreg(DM9000_MLC_REG+5,0xff);
  write_nicreg(DM9000_MLC_REG+6,0xff);
  write_nicreg(DM9000_MLC_REG+7,0xff);

  //7. reset Internal PHY if desired
  //	PHY_write(DM9000_BMCR, 0x8000);	// PHY reset
  //	 _wait_ms(1000);
  //	PHY_write(DM9000_BMCR, 0x1200);	// Auto negotiation
  //	 _wait_ms(1000);

  //8. Set IMR register (reg_FFh) bit[7]=1 to enable the SRAM read/write pointer which is the
  // automatic return function of the memory R/W address pointer; also set the receive int mask.

  write_nicreg(DM9000_IMR, 0x81);

  //9. Depend on OS and DDK of the system to handle NIC interrupts.
  // Not applicable since the DM9000 is polled

  //10. Program IMR register (reg_FFh) bit[1:0] to enable the TX/RX interrupt. Before doing this,
  // the system designer needs to register the interrupt handler routine. For example, if the driver
  // needs to generate the interrupt after a package is transmitted, the interrupt mask register IMR
  // bit[1]=1 will be set. If the interrupt is generated by the DM9000 after receiving a packet, IMR
  // bit[0] should be set to 1.
  // Not applicable since the DM9000 is polled

  //11. Program RXCR register to enable RX. The RX function is enabled by setting the RX control
  // register (reg_05h) bit[0]=1. The choice of the other bits bit[6:0] depends on the system design.
  // Please refer to the DM9000 datasheet ch.6.6 about RXCR register setting.

  write_nicreg(DM9000_RXCR, 0x31);	// Only MAC-packets and RX enable - no multicast packets

  //12. NIC is being activated now.
  // while (1)
  //      write_nicreg(DM9000_MAC_REG,  uip_ethaddr.addr[0]);


  //13. Check Vendor ID is Davicom (0x0A46)
  //while (1) {
  //  temp1 = read_nicreg(DM9000_VID);
  //}
  //temp2 = read_nicreg(DM9000_VID+1);

  DM9000_VendorID  = read_nicreg(DM9000_VID) + (read_nicreg(DM9000_VID+1) << 8);
  DM9000_ProductID = read_nicreg(DM9000_PID) + (read_nicreg(DM9000_PID+1) << 8);
  DM9000_IO_mode   = read_nicreg(DM9000_ISR);

  return;
}

//-----------------------------------------------------------------------------
// DM9000_Send
//-----------------------------------------------------------------------------

void send_frame (OS_FRAME *frame) {


U16 i;
U16  n;
U16 *dp;
U16  len;

//IOSET0 = 0x00000400; // P0.10 --> LED;

dp  = (U16 *)&frame->data[0];
len =  frame->length;

//if(capture) dump_frame(0,(char *)dp, len);

write_reg(DM9000_MWCMD);                  // set write autoincrement

n =(len +1)/2;


for (i = 0; i < n; i++) write_data(dp[i]);


while (read_nicreg(DM9000_TCR) & 0x01);   // wait transmit complete

write_nicreg(DM9000_TXPLH, (len>>8) & 0xFF);
write_nicreg(DM9000_TXPLL, len & 0xFF);

write_nicreg(DM9000_TCR, 1);		      // start the transmission

//IOCLR0 = 0x00000400;

}

//-----------------------------------------------------------------------------
// DM9000_Receive
//-----------------------------------------------------------------------------

void poll_ethernet (void) {

OS_FRAME *frame;

U16       RxLen;
U16       *dp;
U16  n;
U16  i;



if( (read_nicreg(DM9000_MRCMDX) & 0xff) != 0x01 ) return;

write_reg(DM9000_MRCMD); 	                       // Set read autoincrement


RxLen = (read_data()) & 0x000003ff;
RxLen = read_data() ; 

n = (RxLen+1)/2;


frame = alloc_mem (n*2);

dp = (U16 *)&frame->data[0];

for (i = 0; i < n; i++) dp[i] = read_data();

write_nicreg(DM9000_ISR, 0x01);                        // Clear RX_ready

//check_frame(1,(char *)dp, RxLen);		 // Проверяю содержимое принятого кадра

//if(capture) dump_frame(1,(char *)dp, RxLen);

put_in_queue (frame);

}

