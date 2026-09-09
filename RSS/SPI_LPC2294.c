/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    SPI_LPC2294.C
 *      Purpose: Serial Peripheral Interface Driver for NXP LPC2294
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <File_Config.h>
                
#include <LPC22XX.H>         /* LPC22xx definitions                  */
/*----------------------------------------------------------------------------
  SPI Driver instance definition
   spi0_drv: First SPI driver
   spi1_drv: Second SPI driver
 *---------------------------------------------------------------------------*/

#define __DRV_ID  spi0_drv
#define __PCLK    58982400

/* SPI Driver Interface functions */
static BOOL Init (void);
static BOOL UnInit (void);
static U8   Send (U8 outb);
static BOOL SendBuf (U8 *buf, U32 sz);
static BOOL RecBuf (U8 *buf, U32 sz);
static BOOL BusSpeed (U32 kbaud);
static BOOL SetSS (U32 ss);
static U32  CheckMedia (void);        /* Optional function for SD card check */

/* SPI Device Driver Control Block */
SPI_DRV __DRV_ID = {
  Init,
  UnInit,
  Send,
  SendBuf,
  RecBuf,
  BusSpeed,
  SetSS,
  CheckMedia                          /* Can be NULL if not existing         */
};


/* SSPSR - bit definitions. */
#define TFE     0x01
#define TNF     0x02
#define RNE     0x04
#define RFF     0x08
#define BSY     0x10

/*--------------------------- Init ------------------------------------------*/

static BOOL Init (void) {
  /* Initialize and enable the SPI Interface module. */
	PCONP = 0x0021FFBE;
  /* SSEL is GPIO, output set to high. */
  IODIR0 |= 1<<20;
  IOSET0  = 1<<20;
  /* SCK1, MISO1, MOSI1 are SPI pins. */
  PINSEL1 = (PINSEL1 & ~0x000003FC) | 0x000002A8;

  /* Enable SPI in Master Mode, CPOL=0, CPHA=0. */
///  SSPCR0  = 0x0007;
///  SSPCR1  = 0x0002;
///  SSPCPSR = 0xFE;
	
	 S1SPCR = 0x20;
 //  S1SPCCR = 37;	  // 400 kbit
   S1SPCCR = 8;	      // SPI1 7.5 ÌÃö 
	
	
	
  return (__TRUE);
}


/*--------------------------- UnInit ----------------------------------------*/

static BOOL UnInit (void) {
  /* Return SPI interface to default state. */

  IODIR0  &= ~(1<<20);
  PINSEL1 &= ~0x000003FC;
///  SSPCR1  = 0x0000;
///  SSPCR0  = 0x0000;
 /// SSPCPSR = 0x00;
  return (__TRUE);
}


/*--------------------------- Send ------------------------------------------*/

static U8 Send (U8 outb) {
  /* Send and Receive a byte on SPI interface. */

  S1SPDR = outb;
  /* Wait if RNE cleared, Rx FIFO is empty. */
///	  while (!(SSPSR & RNE));
  while ((S1SPSR & 0x80) == 0);
  return (S1SPDR);
}


/*--------------------------- SendBuf ---------------------------------------*/

static BOOL SendBuf (U8 *buf, U32 sz) {
  /* Send buffer to SPI interface. */
  U32 i;

  for (i = 0; i < sz; i++) {
    S1SPDR = buf[i];
    /* Wait if Tx FIFO is full. */
 ///   while (!(SSPSR & TNF));
		while ((S1SPSR & 0x80) == 0);
    S1SPDR;
  }
  /* Wait until Tx finished, drain Rx FIFO. */
 /// while (SSPSR & (BSY | RNE)) {
///	while ((S1SPSR & 0x80) == 0){	
///    S1SPDR;
///  }
  return (__TRUE);
}


/*--------------------------- RecBuf ----------------------------------------*/

static BOOL RecBuf (U8 *buf, U32 sz) {
  /* Receive SPI data to buffer. */
  U32 i;

  for (i = 0; i < sz; i++) {
    S1SPDR = 0xFF;
    /* Wait while Rx FIFO is empty. */
 ///   while (!(SSPSR & RNE));
		while ((S1SPSR & 0x80) == 0);
    buf[i] = S1SPDR;
  }
  return (__TRUE);
}


/*--------------------------- BusSpeed --------------------------------------*/

static BOOL BusSpeed (U32 kbaud) {
  /* Set an SPI clock to required baud rate. */
  U32 div;

  div = (__PCLK/1000 + kbaud - 1) / kbaud;
  if (div == 0)   div = 0x02;
  if (div & 1)    div++;
  if (div > 0xFE) div = 0xFE;
 // SSPCPSR = div;
	S1SPCCR = 8;								// SPI1 7.5 ÌÃö
//	S1SPCCR = div;
  return (__TRUE);
}


/*--------------------------- SetSS -----------------------------------------*/

static BOOL SetSS (U32 ss) {
  /* Enable/Disable SPI Chip Select (drive it high or low). */

  if (ss) {
    /* SSEL is GPIO, output set to high. */
    IOSET3 = 1<<24;
  } 
  else {
    /* SSEL is GPIO, output set to low. */
    IOCLR3 = 1<<24;
  }
  return (__TRUE);
}


/*--------------------------- CheckMedia ------------------------------------*/

static U32 CheckMedia (void) {
  /* Read CardDetect and WriteProtect SD card socket pins. */
  U32 stat = 0;
 
#if 0
  if (!(IOPIN0 & 0x04)) {
    /* Card is inserted (CD=0). */
    stat |= M_INSERTED;
  } 
  if ((IOPIN0 & 0x20)) {
    /* Write Protect switch is active (WP=1). */
    stat |= M_PROTECTED;
  }
#else
  /* When CD,WP signals are not connected. */
  stat = M_INSERTED;
#endif
  return (stat);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
