/******************************************************************************/
/* SERIAL.C: Low Level Serial Routines                                        */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <LPC22XX.h>
#include "..\APP\EXTERNALS.h"
#include <string.h>

#define CR     0x0D

//int ch = 0;
/* implementation of putchar (also used by printf function to output data)    */
int sendchar (int ch)  {                 /* Write character to Serial Port    */
  while (!(U1LSR & 0x20));
  return (U1THR = ch);
}


int getkey (void)  {                     /* Read character from Serial Port   */

  while (!(U1LSR & 0x01));

  return (U1RBR);
}

/* Wrapper functions for compatibility */
int com_getchar(void) {
  return getkey();
}

BOOL com_putchar(U8 c) {
  return (sendchar(c) == c) ? __TRUE : __FALSE;
}

BOOL com_tx_active(void) {
  return (U1LSR & 0x20) ? __TRUE : __FALSE;
}

void init_serial(void) {
  /* Initialize UART1 */
  U1LCR = 0x83;       /* Enable DLAB, 8-bit data, no parity, 1 stop bit */
  U1DLL = 97;         /* 9600 baud @ 15MHz PCLK */
  U1DLM = 0;
  U1LCR = 0x03;       /* Disable DLAB */
  U1FCR = 0x07;       /* Enable FIFO, trigger at 14 characters */
  U1TER = 0x80;       /* Enable UART transmit */
}

