


//#include <LPC21XX.h>
#include <string.h>
#include "..\APP\EXTERNALS.h"

  // STATUS registr//
 /*
  Bits 7-4 ID3, ID2, ID1, ID0 Factory Programmed Identification Bits (Read Only)

	Bit 3 ORDER: Data Output Bit Order
	0 = Most Significant Bit First (default)
	1 = Least Significant Bit First

	Bit 2 ACAL: Auto-Calibration
	0 = Auto-Calibration Disabled (default)
	1 = Auto-Calibration Enabled

	Bit 1 BUFEN: Analog Input Buffer Enable
	0 = Buffer Disabled (default)
	1 = Buffer Enabled

	Bit 0 DRDY: Data Ready (Read Only)
 */
    
  #define ORDER	8
  #define ACAL	4	    
  #define BUFEN	2
  #define DRDY	1

  
 // MUX registr	//

 /*   
	Bits 7-4 PSEL3, PSEL2, PSEL1, PSEL0: Positive Input Channel (AINP) Select
	0000 = AIN0 (default)
	0001 = AIN1
	0010 = AIN2 (ADS1256 only)
	0011 = AIN3 (ADS1256 only)
	0100 = AIN4 (ADS1256 only)
	0101 = AIN5 (ADS1256 only)
	0110 = AIN6 (ADS1256 only)
	0111 = AIN7 (ADS1256 only)
	1xxx = AINCOM (when PSEL3 = 1, PSEL2, PSEL1, PSEL0 are “don’t care”)
	NOTE: When using an ADS1255 make sure to only select the available inputs.
	Bits 3-0 NSEL3, NSEL2, NSEL1, NSEL0: Negative Input Channel (AINN)Select
	0000 = AIN0
	0001 = AIN1 (default)
	0010 = AIN2 (ADS1256 only)
	0011 = AIN3 (ADS1256 only)
	0100 = AIN4 (ADS1256 only)
	0101 = AIN5 (ADS1256 only)
	0110 = AIN6 (ADS1256 only)
	0111 = AIN7 (ADS1256 only)
	1xxx = AINCOM (when NSEL3 = 1, NSEL2, NSEL1, NSEL0 are “don’t care”)
 */  
 // ADCON registr //
 /*
	Bit 7 Reserved, always 0 (Read Only)
	Bits 6-5 CLK1, CLK0: D0/CLKOUT Clock Out Rate Setting
	00 = Clock Out OFF
	01 = Clock Out Frequency = fCLKIN (default)
	10 = Clock Out Frequency = fCLKIN/2
	11 = Clock Out Frequency = fCLKIN/4

	Bits 4-2 SDCS1, SCDS0: Sensor Detect Current Sources
	00 = Sensor Detect OFF (default)
	01 = Sensor Detect Current = 0.5мA
	10 = Sensor Detect Current = 2мA
	11 = Sensor Detect Current = 10мA

	Bits 2-0   PGA2, PGA1, PGA0: Programmable Gain Amplifier Setting
	000 = 1 (default)
	001 = 2
	010 = 4
	011 = 8
	100 = 16
	101 = 32
	110 = 64
	111 = 64
			 */
  // DRATE registr //
  /*
    Bits 7-0 DR[7: 0]: Data Rate Setting(1)
	0xF0 = 30,000SPS (default)
	0xE0 = 15,000SPS
	0xD0 = 7,500SPS
	0xC0 = 3,750SPS
	0xB0 = 2,000SPS
	0xA1 = 1,000SPS
	0x92 = 500SPS
	0x82 = 100SPS
	0x72 = 60SPS
	0x63 = 50SPS
	0x53 = 30SPS
	0x43 = 25SPS
	0x33 = 15SPS
	0x23 = 10SPS
	0x13 = 5SPS
	0x03 = 2.5SPS
(1) for fCLKIN = 7.68MHz. Data rates scale linearly with fCLKIN.
	*/

	 // GPIO registr//
	 /*
	Bit 7 DIR3, Digital I/O Direction for Digital I/O Pin D3 (used on ADS1256 only)
	0 = D3 is an output
	1 = D3 is an input (default)
	Bit 6 DIR2, Digital I/O Direction for Digital I/O Pin D2 (used on ADS1256 only)
	0 = D2 is an output
	1 = D2 is an input (default)
	Bit 5 DIR1, Digital I/O Direction for Digital I/O Pin D1
	0 = D1 is an output
	1 = D1 is an input (default)
	Bit 4 DIR0, Digital I/O Direction for Digital I/O Pin D0/CLKOUT
	0 = D0/CLKOUT is an output (default)
	1 = D0/CLKOUT is an input
	Bits 3-0 DI0[3:0]: Status of Digital I/O Pins D3, D2, D1, D0/CLKOUT

	*/
   #define SYNC    0xFC;
   #define WAKEAP  0x00;
   #define SELFCAL 0xF0;
   #define SYSCAL  0xF3;
   #define RDATA   0x01;
   #define STANDBY 0xFD;

 //	   Частота выдачи   Частота АЦП    Время записи   Объём памяти на 1 канал
 //	   
 //	   40				120			   1			  120
 //	   40				120			   5			  600
 //	   40				120			   10			  1200
 //
 //	   100				300			   1			  300
 //	   100				300			   5			  1500
 //	   100				300			   10			  3000
 //
 //	   200				600			   1			  600
 //	   200				600			   5			  3000
 //	   200				600			   10			  6000
 //
 //	   300				900			   1			  900
 //	   300				900			   5			  4500
 //	   300				900			   10			  9000
 
 

U8 *out_udp_adr;

S32 DATA_REG[3];

U8 servis_frame[10000];
U8 asc_servis_frame[50000];
U8 rep_servis_frame[50000];

S32 data_X_1[6000];
S32 data_Y_1[6000];
S32 data_Z_1[6000];
S32 data_X_2[6000];
S32 data_Y_2[6000];
S32 data_Z_2[6000];

S32 data_X[2000];
S32 data_Y[2000];
S32 data_Z[2000];

S32* paket_adr_X;
S32* paket_adr_Y;
S32* paket_adr_Z;

S32* out_paket_adr_X;
S32* out_paket_adr_Y;
S32* out_paket_adr_Z;

S32 USTIR_D;

U32 delta_time_write;
 
U8 TEMP_REG[4], COMMAND_REG[6], data_radi, ADCON, DRATE, GPIO, blok;

float  FILTR_REG[3];





void wait_time(void)			  // задержка между командой и чтением данных ~10 мкс
{
  unsigned int delay =0;
		while (delay != 80){
			 delay ++;

		}
	  
}

void write(U8 blok) 
{
	    adr_buf = &COMMAND_REG[0];
  		IO0CLR |= 0x0000E000;		 // Запись в каналы X,Y,Z
						   	
	 	spi_send_0 (blok);

		IO0SET |= 0x0000E000;		 // Закрыть каналы X,Y,Z

}



 ///////// установка режима работы АЦП	//////////////////
void  config_ad(void)
 {
// 	 ADCON = 0x00;	 // 0X00	  0x20 РАЗРЕШЕН ВЫХОД SCLK

//	 DRATE = 0xC0;   // 3840 Hz 
//	 DRATE = 0xB0;   // 1920 Hz 
//	 DRATE = 0xA1;   // 960 Hz 
//	 DRATE = 0x92;   // 480 Hz 
//	 DRATE = 0x82;   // 104 Hz

	 GPIO  = 0xC2;	  // D1, D0 - ВЫХОДЫ; 1, 0 - основной режим работы АЦП
					  //				  0, 0 - режим калибровки 1 
 					  //				  1, 1 - режим калибровки 2

   

				  // Запись конфигурации в АЦП 
	 COMMAND_REG[0] = 0x52;
	 COMMAND_REG[1] = 0x02;
	 COMMAND_REG[2] = ADCON;
	 COMMAND_REG[3] = DRATE;
	 COMMAND_REG[4] = GPIO;
	 COMMAND_REG[5] = STANDBY;
	
	write(6);	

 }

/////////////////// Синхронизация каналов АЦП /////////////////////
void sync_ad(void)
{
	 COMMAND_REG[0] = SYNC;
	 COMMAND_REG[1] = WAKEAP;

	  write(2);

}

//////////////////////  Самокалибровка АЦП ///////////////////////
void selfcal(void)
{
	 COMMAND_REG[0] = SELFCAL;

	 write(1);


}

//////////////////////  Системная калибровка 0 АЦП ///////////////////////
void syscal(void)
{
	 COMMAND_REG[0] = SYSCAL;

	 write(1);


}


//////////////////////  Задание режима калибровки   //////////////////////////
void num_cal(void)
{
	 COMMAND_REG[0] = 0x54;
	 COMMAND_REG[1] = 0x00;
  	 COMMAND_REG[2] = GPIO;

	 write(3);
}

 /////////////////// начать преобразование АЦП //////////////////
 void begin_ad(void)
 {   
	IO1SET |= 0x00010000;	

	     COMMAND_REG[0] = WAKEAP;
//		 adr_buf = &COMMAND_REG[0];

		 write(1);
 	IO1CLR |= 0x00010000;
  
 }



 ////////////////// Читать данные из АЦП /////////////////////////

 void read_ad(void)
 {	  unsigned char n, m = 2;
//	  U32 temp;
	  signed int temp;
//	  void *adr_port;
//	  U32* paket_adr_X;
//	  U32* paket_adr_Y;
//	  U32* paket_adr_Z;

	   COMMAND_REG[0] = RDATA;
	   COMMAND_REG[1] =	STANDBY;

	for (n = 0; n < 3; n++){

	   adr_buf = &COMMAND_REG[0];

	IO0CLR |= (0x00002000 << n );		//  чтение данных из АЦП канал n
		  spi_send_0 (1);				//  команда чтение из АЦП

		  wait_time();				    // задержка между командой и чтением данных

	adr_buf = &TEMP_REG[m];	   		   
		  spi_resiv (3);				//  чтение данных из АЦП

	
	adr_buf = &COMMAND_REG[1];
		  spi_send_0 (1);					            //  команда STENDBY АЦП

	IO0SET |= (0x00002000 << n );		                // Закрыть канал n

				temp = 0;
 			  	memmove (&temp,&TEMP_REG[0], 3);
			  
	//			temp = (~temp) & 0x00FFFFFF;   // Инверсия входного сигнала

				if (TEMP_REG[2] & 0x80) temp |=0xFF000000;

				DATA_REG [n]= temp ;	 
   
	}

  

//	 if (CHECKBIT(flag,SUCAL_ON)){		  // После системной калибровки	-
			 
//		if (priznak == 0) goto m4;	 	  // Для РМГД выход без записи в кадр
//			n_data_kadr +=3; 			  // Для РСС прибавляю пропущенный отсчет
//	 }									  // и записываю в кадр

	 
     //переписываю данные по каналам. Запись начинается с конца массива

					DATA_REG[2]	= DATA_REG[1]= DATA_REG[0];
	 						
	 		  *((paket_adr_X-delta_time_write) - n_data) = DATA_REG[0];
			  *((paket_adr_Y-delta_time_write) - n_data) = DATA_REG[1];
			  *((paket_adr_Z-delta_time_write) - n_data) = DATA_REG[2];
		 			
		            // Для вывешивания
		   if (CHECKBIT(flag,USTIR)) {
			  USTIR_D = USTIR_D + DATA_REG[ustir_chen];		  // Расчитываю среднее
			  		                                          //		смещениe

				   if (n_data == (AD_rate-1)){		      //		по каналам
			   			USTIR_D = USTIR_D/(AD_rate-1); 
						USTIR_D = USTIR_D >> 8;		
				 		memcpy(&FSUK_KOMANDA[2],&USTIR_D,2);  // Передаю смещение в ФСУК
						USTIR_D = 0;
		     	   }
		   }
 // m4:
 }
					   
