#include <LPC22XX.h>
#include "..\APP\EXTERNALS.h"



unsigned char *adr_buf, *adr_ram;

 void SPIInit()
{
    S0SPCR  = 0x28;           // SPI0 Данные меняются по переднему, записываются по заднему фронту
    S0SPCCR = 36;//40;        // SPI0 1,4745 МГц для АЦП  Baud Rate @ 60MHz VPB Clock 
      

    S1SPCR  = 0x28;           // SPI1 Данные записываются по заднему фронту
    S1SPCCR = 8;              // SPI1 7.5 МГц для ФСУК,  
	      
}


        /* Write  a byte on SPI0 interface. */
void spi_send_0 (unsigned char n_bait)
{
  unsigned char a;
 	 for (a=0; a<n_bait; a++){
              S0SPDR =  *(adr_buf + a); 
		while ((S0SPSR & 0x80) == 0);
         }
             
}
      /*  Read a byte on SPI0 interface. */
void spi_resiv (unsigned char n_bait)
{   
   unsigned char a;
 	 for (a=0; a<n_bait; a++){
 	      S0SPDR = 0;
                while ((S0SPSR & 0x80) == 0);
                     *(adr_buf - a) = S0SPDR;
	 }
         
}


    /* Write a date on SPI1 interface. */
void spi1_send (void)
{
  unsigned char a;

//  IO0CLR |= 0x00000400;			//  запись данных в ФСУК
	   
//	 S1SPDR =  FSUK_KOMANDA[0];
//		 	while ((S1SPSR & 0x80) == 0); 

//  IO0SET |= 0x00000400;			// Конец записи

//	 FSUK_KOMANDA[0]=5;

 	 for (a=0; a<12; a++){

		  IO0CLR |= 0x00000400;			//  запись данных в ФСУК     SSEL НАДО ВЫДАВАТЬ НА 

      //        S1SPDR =  *(adr_ram + a);        // передача команды   КАЖДЫЙ БАЙТ ИНАЧЕ
			  S1SPDR =FSUK_KOMANDA[a];
			    while ((S1SPSR & 0x80) == 0);
			  FSUK_DATA[a] = S1SPDR;	       // приём данных

		  IO0SET |= 0x00000400;			// Конец записи		         ИСКАЖАЕТСЯ ПРИЁМ
      }
//     IO0SET |= 0x00000400;			// Конец записи

}

