


///////////////////// Запись общей информации про каналы ///////////////////////
///////////////////// Конфигурация параметров устройства ///////////////////////

#include "..\APP\EXTERNALS.h"
#include <string.h>

//#define MAX 4900




//   массивы формируются в обратной последовательностит для упрощения перевода 
//  выходных данных в формат выдачи IEEE, считывание из памяти производиться с конца.

void init_info(void){

// U16 i;
 U32 temp;

//	   ==================/////// Канал CH0 //////====================

//		  i=1;

 //		temp = 504;
		temp = 104+size;
	    memmove(&Ch_1_0_data [4904],&temp,4);  // chennel_lens, без учёта первых 4 байт
//	    temp = 500;
		temp -= 4;
	    memmove(&Ch_1_0_data [4900],&temp,4);  // authentication_offset

		Ch_1_0_data [MAX- 1] = 0;                // 1 authentication 0=OFF;1=ON
		Ch_1_0_data [MAX- 2] = 0;				// 2 transformation
		Ch_1_0_data [MAX- 3] = 0;				// 3 sensor type
		Ch_1_0_data [MAX- 4] = 0;				// 4 option flag

		Ch_1_0_data [MAX- 5] = 'T';
		Ch_1_0_data [MAX- 6] = 'B';
		Ch_1_0_data [MAX- 7] = 'S';			    // 5-9 site name
		Ch_1_0_data [MAX- 8] = 'C';
		Ch_1_0_data [MAX- 9] = '1';

		Ch_1_0_data [MAX- 10] = 'C';				//10-12	  channel name
		Ch_1_0_data [MAX- 11] = 'H';
		Ch_1_0_data [MAX- 12] = '0';

		Ch_1_0_data [MAX- 13] = '0';				// 13-14	location name
		Ch_1_0_data [MAX- 14] = '1';

		Ch_1_0_data [MAX- 15] = 's';	//i			// 15, 16 data format 
		Ch_1_0_data [MAX- 16] = '4';

		Ch_1_0_data [MAX- 17] = 0;			    // 17-20	calibration factor
		Ch_1_0_data [MAX- 18] = 0;
		Ch_1_0_data [MAX- 19] = 0;			    
		Ch_1_0_data [MAX- 20] = 0;

		Ch_1_0_data [MAX- 21] = 0;			   // 21-24	  calibration period
		Ch_1_0_data [MAX- 22] = 0;			    
		Ch_1_0_data [MAX- 23] = 0;								    
		Ch_1_0_data [MAX- 24] = 0;

				/////////	 20 байт ВРЕМЯ ASCII

		temp = 1000*time_write;				  // subframe_time_length
	    memmove(&Ch_1_0_data [4852],&temp,4); 
	//	temp = 100;						      // sampls
		temp =data_rate * time_write;		  // с учетом времени записи
	    memmove(&Ch_1_0_data [4848],&temp,4); 
	 	temp = 28;						      // channel_status_size
	    memmove(&Ch_1_0_data [4844],&temp,4);
											 
			   //////////	 28 байта произвольные данные

		temp = size;						      // data_size
	    memmove(&Ch_1_0_data [4812],&temp,4);

			   /////////     4800 байт данные

		temp = 0;						  		// subframe_count
	    memmove(&Ch_1_0_data [4812-size-4],&temp,4); 
		temp = 0;						  		// authentication_key_identifier
	    memmove(&Ch_1_0_data [4812-size-8],&temp,4); 
		temp = 0;						  		// authentication_size
	    memmove(&Ch_1_0_data [4812-size-12],&temp,4);
		
//	    ===============/////// Канал CH1 //////=================

//		   i=1;

 //		temp = 504;
		temp = 104+size;
	    memmove(&Ch_2_0_data [4904],&temp,4);  // chennel_lens, без учёта первых 4 байт
//	    temp = 500;
		temp -= 4;
	    memmove(&Ch_2_0_data [4900],&temp,4);  // authentication_offset

		Ch_2_0_data [MAX- 1] = 0;                // 1 authentication 0=OFF;1=ON
		Ch_2_0_data [MAX- 2] = 0;				// 2 transformation
		Ch_2_0_data [MAX- 3] = 0;				// 3 sensor type
		Ch_2_0_data [MAX- 4] = 0;				// 4 option flag

		Ch_2_0_data [MAX- 5] = 'T';
		Ch_2_0_data [MAX- 6] = 'B';
		Ch_2_0_data [MAX- 7] = 'S';			    // 5-9 site name
		Ch_2_0_data [MAX- 8] = 'C';
		Ch_2_0_data [MAX- 9] = '1';

		Ch_2_0_data [MAX- 10] = 'C';				//10-12	  channel name
		Ch_2_0_data [MAX- 11] = 'H';
		Ch_2_0_data [MAX- 12] = '1';

		Ch_2_0_data [MAX- 13] = '0';				// 13-14	location name
		Ch_2_0_data [MAX- 14] = '1';

		Ch_2_0_data [MAX- 15] = 's';	//i			// 15, 16 data format 
		Ch_2_0_data [MAX- 16] = '4';

		Ch_2_0_data [MAX- 17] = 0;			    // 17-20	calibration factor
		Ch_2_0_data [MAX- 18] = 0;
		Ch_2_0_data [MAX- 19] = 0;			    
		Ch_2_0_data [MAX- 20] = 0;

		Ch_2_0_data [MAX- 21] = 0;			   // 21-24		calibration period
		Ch_2_0_data [MAX- 22] = 0;			    
		Ch_2_0_data [MAX- 23] = 0;								    
		Ch_2_0_data [MAX- 24] = 0;

				/////////	 20 байт ВРЕМЯ ASCII

		temp = 1000*time_write;				  // subframe_time_length
	    memmove(&Ch_2_0_data [4852],&temp,4); 
	//	temp = 100;						      // sampls
		temp =data_rate * time_write;		  // с учетом времени записи
	    memmove(&Ch_2_0_data [4848],&temp,4); 
	 	temp = 28;						      // channel_status_size
	    memmove(&Ch_2_0_data [4844],&temp,4);
											 
			   //////////	 28 байта произвольные данные

		temp = size;						      // data_size
	    memmove(&Ch_2_0_data [4812],&temp,4);

			   /////////     4800 байт данные

		temp = 0;						  		// subframe_count
	    memmove(&Ch_2_0_data [4812-size-4],&temp,4); 
		temp = 0;						  		// authentication_key_identifier
	    memmove(&Ch_2_0_data [4812-size-8],&temp,4); 
		temp = 0;						  		// authentication_size
	    memmove(&Ch_2_0_data [4812-size-12],&temp,4);

//		================/////// Канал CH2 //////======================

//		  i=1;

 //		temp = 504;
		temp = 104+size;
	    memmove(&Ch_3_0_data [4904],&temp,4);  // chennel_lens, без учёта первых 4 байт
//	    temp = 500;
		temp -= 4;
	    memmove(&Ch_3_0_data [4900],&temp,4);  // authentication_offset

		Ch_3_0_data [MAX- 1] = 0;                // 1 authentication 0=OFF;1=ON
		Ch_3_0_data [MAX- 2] = 0;				// 2 transformation
		Ch_3_0_data [MAX- 3] = 0;				// 3 sensor type
		Ch_3_0_data [MAX- 4] = 0;				// 4 option flag 1-калибровка

		Ch_3_0_data [MAX- 5] = 'T';
		Ch_3_0_data [MAX- 6] = 'B';
		Ch_3_0_data [MAX- 7] = 'S';			    // 5-9 site name
		Ch_3_0_data [MAX- 8] = 'C';
		Ch_3_0_data [MAX- 9] = '1';

		Ch_3_0_data [MAX- 10] = 'C';				//10-12	  channel name
		Ch_3_0_data [MAX- 11] = 'H';
		Ch_3_0_data [MAX- 12] = '2';

		Ch_3_0_data [MAX- 13] = '0';				// 13-14	location name
		Ch_3_0_data [MAX- 14] = '1';

		Ch_3_0_data [MAX- 15] = 's';	//i			// 15, 16 data format 
		Ch_3_0_data [MAX- 16] = '4';

		Ch_3_0_data [MAX- 17] = 0;			    // 17-20
		Ch_3_0_data [MAX- 18] = 0;			   // калибровочный фактор
		Ch_3_0_data [MAX- 19] = 0;			    
		Ch_3_0_data [MAX- 20] = 0;

		Ch_3_0_data [MAX- 21] = 0;			   // 21-24
		Ch_3_0_data [MAX- 22] = 0;			   // калибровочный период
		Ch_3_0_data [MAX- 23] = 0;								    
		Ch_3_0_data [MAX- 24] = 0;

				/////////	 20 байт ВРЕМЯ ASCII

		temp = 1000*time_write;				  // subframe_time_length
	    memmove(&Ch_3_0_data [4852],&temp,4); 
//		temp = 100;						      // sampls
		temp =data_rate * time_write;		  // с учетом времени записи
	    memmove(&Ch_3_0_data [4848],&temp,4); 
	 	temp = 28;						      // channel_status_size
	    memmove(&Ch_3_0_data [4844],&temp,4);
											 
			   //////////	 28 байта произвольные данные

		temp = size;						      // data_size
	    memmove(&Ch_3_0_data [4812],&temp,4);

			   /////////     4800 байт данные

		temp = 0;						  		// subframe_count
	    memmove(&Ch_3_0_data [4812-size-4],&temp,4); 
		temp = 0;						  		// authentication_key_identifier
	    memmove(&Ch_3_0_data [4812-size-8],&temp,4); 
		temp = 0;						  		// authentication_size
	    memmove(&Ch_3_0_data [4812-size-12],&temp,4);

		

}
