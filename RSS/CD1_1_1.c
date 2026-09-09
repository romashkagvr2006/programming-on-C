
#include "..\APP\EXTERNALS.h"
#include <string.h>


//		Структура кадров записана в
//      обратной последовательностит для упрощения перевода 
//  выходных данных в формат выдачи IEEE, считывание из памяти производиться с конца.
  
U8   lcd_text[15][8+1] = {"TVISTER",  // Имя станции по умолчанию
						  "",		  // Частота калибровки
						  "8.420E-6",	  // ЦНРК емкостной калибровочный 
						  "8.420E-6",
						  "8.420E-6",

						  "6.080E-6",	  // ЦНРК резистивный калибровочный 
						  "6.080E-6",
						  "6.080E-6",

						  "1.340E-6",	 // ЦНРК измерительный  
						  "1.340E-6",	 
						  "1.340E-6",	   

						  "2.680E-6",	 // ЦНРК регистратора
						  "2.680E-6",
						  "2.680E-6",
						  ""};	 // Амплитуда калибровки
                          

  

//===============Frame Trailer table 2.4 ==========
U8 trailer_frame[16]={1,2,3,4,5,6,7,8, 0,0,0,0, 0,0,0,0}; 					   // 16 байт
//0-7 unsigned long long comm_verif;//=0x1234567812345678;			   //контрольная сумма	IEEE
//8-11 auth_size;//=0;						   //0				IEEE
//12-15 auth_key;//=0;						   //0					IEEE


 //============= Connection Request Frame table 2.5 ==============
U8 request_frame [32]={0x36,0x21, 5,0,0,0xA, 0x34,0x21, 2,0,16,0xA, 0,'P','C','T',
				0,'C','D','N', 0,0,0,'T','S','I','V','T', 3,0, 1,0 }; // 32 байт
//0-1 second_port;// =8502;
//2-5 second_IP_addres;//;
//6-7 port;//=8500;
//8-11 IP_addres;//;						      
//12-15 servis_type[4];// ={'T','C','P',0};
//16-19 station_type[4];//={'N','D','C',0};
//20-27 station_name[8];//={'T','E','S','T','1',0,0,0};			 	  
//28-29 minor_version;// =3 ;
//30-31 major_version;// =1;


  //============== Frame Header table 2.3 ===================
U8 header_frame[36]={0,0,0,0, 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,'R','E', 'T','S','E','T',
						33,0,0,0, 1,0,0,0}	;	// 36 байт
//0-3 series;// =0;
unsigned long long sequence_number=0;//=1 ;
//12-19 frame_destination [8];// ={0,0,0,0,0,0,0,0};
//20-27 frame_creator [8];//={'T','E','S','T','E','R',0,0};
//28-31 trailer_offset;//=68 ;
//32-35 frame_type;//=1;



   


// ============== Channel Subfrme 1 table 2.10 ==================
//-------------------------------------------------

const U8 Ch_1_channel_string [10]="TBSC1CH001";
//-------------------------------------------------
U8	Ch_1_0_data[4908];

/*
U32 Ch_1_chennel_lens;
U32 Ch_1_authentication_offset;
//U8 Ch_1_channel_description [24];         //0, 0, 
//U8 Ch_1_time_stamp [20];
U32 Ch_1_subframe_time_length;
U32 Ch_1_sampls;
U32 Ch_1_channel_status_size;				 
//U8 Ch_1_channel_status_data[28];            //  28 байта
U32 Ch_1_data_size;
//U32 channel_data [];			            // Результаты преобразований 400 байт max.
U32 Ch_1_subframe_count=0;
U32 Ch_1_authentication_key_identifier=0;
U32	Ch_1_authentication_size =0;								 
//U8 authentication_value[];	            // не используется
*/
U8 status_data[28]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
18,19,20,21,22,23,24,25,26,27,28};


 // ============== Channel Subfrme 2 ==================
 //-----------------------------------------------

const U8 Ch_2_channel_string [10]="TBSC1CH101";
//-----------------------------------------------
U8	Ch_2_0_data[4908];

/*	
U32 Ch_2_chennel_lens;
U32 Ch_2_authentication_offset;
//U8 Ch_2_channel_description [24];
//U8 Ch_2_time_stamp [20];
U32 Ch_2_subframe_time_length;
U32 Ch_2_sampls;
U32 Ch_2_channel_status_size;
//U8 Ch_2_channel_status_data[];
U32 Ch_2_data_size;
//U32 channel_data [];			             // Результаты преобразований.
U32 Ch_2_subframe_count=0;
U32 Ch_2_authentication_key_identifier=0;
U32	Ch_2_authentication_size=0;	
//U8 authentication_value[];

*/

 // ============== Channel Subfrme 3 ==================
//---------------------------------------------------

const U8 Ch_3_channel_string [10]="TBSC1CH201";
//---------------------------------------------------

U8	Ch_3_0_data[4908];

/*
U32 Ch_3_chennel_lens;
U32 Ch_3_authentication_offset;
//U8 Ch_3_channel_description [24];       //0, 0, 
//U8 Ch_3_time_stamp [20];
U32 Ch_3_subframe_time_length;
U32 Ch_3_sampls;
U32 Ch_3_channel_status_size;
//U8 Ch_3_channel_status_data[];
U32 Ch_3_data_size;
//U32 channel_data [];			          // Результаты преобразований.
U32 Ch_3_subframe_count=0;
U32 Ch_3_authentication_key_identifier=0;
U32	Ch_3_authentication_size=0;
//U8 authentication_value[];
*/




// ============== Subframe Header table 2.9 ===============
U8 sub_header_frame [32]={ 10,0,0,0, 1,2,3,4,5,6,7,8,9,10,11,12,
						 13,14,15,16,17,18,19,20,232,3,0,0, 3,0,0,0}; 
							
//U8 channel_string [10]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,
//                         27,28,29,30};
//U32 channel_string_count;				// 10

//U8 nominal_time [20]= {"2011011 01:01:50.000"};					
//U32 frame_time_length;					// 1000 ms
//U32 number_of_channels;					// 3


U8 time [20]= "2011011 01:01:50.000";




//=================================================================
void plase_datakadr(void){	 // Запись кадра данных
 	void *aaaa;
//	void *bbbb;
//	void *cccc;

 U8 *adr_serv;
 U16 i;
 
// U32 temp;

///	  for (i=0;i<data_rate;i++){		 // Прореживаю выходные данные

///			 data_X[i]	=  *(out_paket_adr_X +i*5);
///			 data_Y[i]	=  *(out_paket_adr_Y +i*5);
///			 data_X[i]	=  *(out_paket_adr_Z +i*5);
///	 	 }


	 			aaaa = &data_X[0];
				adr_serv = aaaa; 	 		 				 
	memcpy(&Ch_1_0_data[4812-size],&(*adr_serv),size);   // Переписываю данные из канала
 
				aaaa = &data_Y[0];
				adr_serv = aaaa;
    memcpy(&Ch_2_0_data[4812-size],&(*adr_serv),size);	 // Переписываю данные из канала

			   	aaaa = &data_Z[0];
				adr_serv = aaaa;
    memcpy(&Ch_3_0_data[4812-size],&(*adr_serv),size);	 // Переписываю данные из канала

   /*
				aaaa = out_paket_adr_X;
				adr_serv = aaaa; 	 		 				 
	memcpy(&Ch_1_0_data[4812-size],&(*adr_serv),size); // Переписываю данные из канала
 
				aaaa = out_paket_adr_Y;
				adr_serv = aaaa;
    memcpy(&Ch_2_0_data[4812-size],&(*adr_serv),size);	 // Переписываю данные из канала

			   	aaaa = out_paket_adr_Z;
				adr_serv = aaaa;
    memcpy(&Ch_3_0_data[4812-size],&(*adr_serv),size);	// Переписываю данные из канала
	 */


					aaaa=&Ch_1_0_data [4907];
			 	    adr_serv = aaaa; 

			  for(i=0;i<(size+108);i++){						  // Кадр данных
			 	 servis_frame[i+70+10*number_of_chenal] = *(adr_serv-i);
			 }


		  memmove(&servis_frame[70+10*number_of_chenal+32],&time [0],20);                 // время

		  memmove(&servis_frame[70+10*number_of_chenal+64],&status_data[0],28);

			 if (number_of_chenal == 3){
//	/*
		  			aaaa=&Ch_2_0_data [4907];
			 	    adr_serv = aaaa; 

			  for(i=0;i<(size+108);i++){						  // Кадр данных Y
			 	 servis_frame[i+100+(size+108)] = *(adr_serv-i);
			 }


		  memmove(&servis_frame[132+(size+108)],&time [0],20);       // время

		  memmove(&servis_frame[164+(size+108)],&status_data[0],28);
	
		 		   aaaa=&Ch_3_0_data [4907];
			 	    adr_serv = aaaa; 

			  for(i=0;i<(size+108);i++){						  // Кадр данных Z
			 	 servis_frame[i+100+(size+108)+(size+108)] = *(adr_serv-i);
			 }


		  memmove(&servis_frame[132+(size+108)+(size+108)],&time [0],20);   // время

		  memmove(&servis_frame[164+(size+108)+(size+108)],&status_data[0],28);

	   //*/
		   }
}

//===================================================================
void plase_subheader(void){	 //Запись подзаголовка данных
	void *aaaa;
 U8 *adr_serv;
 U8 i;
 		 
				   aaaa=&sub_header_frame [31];
			 	   adr_serv = aaaa;
		
			 for(i=0;i<32;i++){							         // Подзаголовок
				 servis_frame[i+36] = *(adr_serv-i);
			 }

		memmove(&servis_frame[44],&time [0],20);                 // время
		memmove(&servis_frame[68],&Ch_1_channel_string [0],10);  // channel_string
			 
		servis_frame[78] = servis_frame[79] = 0;  //78,79 = 0

				if (number_of_chenal ==3 ){												 
					memmove(&servis_frame[78],&Ch_2_channel_string [0],10); 
					memmove(&servis_frame[88],&Ch_3_channel_string [0],10); 
					servis_frame[98] = servis_frame[99] = 0;  //98,99 = 0
				 }
		
}




//=========================================================================
void plase_header(void){	// Запись заголовка

void *aaaa;
 U8 *adr_serv;
 U8 i;
 		 
				   aaaa=&header_frame[35];
			 	   adr_serv = aaaa;
		
			 for(i=0;i<36;i++){						  	     // Заголовок
				 servis_frame[i] = *(adr_serv-i);
			 }
				

	  }
//=============================================================================
void plase_kadr(void){	  // Запись кадра ЗАПРОС СВЯЗИ

void *aaaa;
 U8 *adr_serv;
 U8 i;
 				   								
					aaaa=&request_frame [31];
			 	    adr_serv = aaaa;
		
			 for(i=0;i<32;i++){							      // Кадр
				 servis_frame[i+36] = *(adr_serv-i);	    
			 }

}
//=============================================================================
void plase_trailer(void){		// Запись трейлера

void *aaaa;
 U8 *adr_serv;
 U8 i;
 U16 nn=0;

	   switch(header_frame[32])
  {							   // Смещение трейлера	в кадре данных

  case 1   :	  nn = 32;			// Запрос связи
									  
			break;

  case 5:	//	  nn=  552;		          // Передача кадра данных
			//	  nn = 108+32+10*number_of_chenal+2+size*number_of_chenal;	   //1 канал
				  nn = 32+2+(108+10+size)*number_of_chenal;
			//	  nn = 108+32+32+size;	                                       //3 канала

  		    break;
   }
					aaaa=&trailer_frame[15];				  // трейлер
			 	    adr_serv = aaaa;
		
			 for(i=0;i<16;i++){
					 servis_frame[i+36+nn] = *(adr_serv-i);
			 }
			 
	SETBIT(flag1,PAKET);	// Пакет готов к расчёту CRC64 и передаче
}


////////////////////  Connection Request Frame  ////////////////////////////////////	
void make_request(void){	 // Формирую кадр запрос установки связи
 U32 temp;
 /*U8 txt[8];


		  txt[7]= lcd_text[0][0];
		  txt[6]= lcd_text[0][1];
		  txt[5]= lcd_text[0][2];
		  txt[4]= lcd_text[0][3];
		  txt[3]= lcd_text[0][4];
		  txt[2]= lcd_text[0][5];
		  txt[1]= lcd_text[0][6];
		  txt[0]= lcd_text[0][7];
	 */
		  temp = 1;
		  memmove(&header_frame[32],&temp,4);  // тип кадра 1

		  temp = 68;
		  memmove(&header_frame[28],&temp,4);  // трейлер оффсет 68
 		  
//		  memmove(&request_frame[20],&txt[0],8);
   
		  temp = IP_ADDR;					   // IP адрес
		  memmove(&request_frame [8],&temp,4);

		  temp = PORT_NUM;					   // PORT_NUM
		  memmove(&request_frame [6],&temp,2);

		  plase_header();
		  plase_kadr();
		  plase_trailer();


 
}
///////////////////// Формирую кадр данных /////////////////////////////////////////
void make_data_kadr(void){	
U32 temp;


		  temp = 5;
		  memmove(&header_frame[32],&temp,4);       // тип кадра 5	   .0

//		  memmove(&header_frame[20],&lcd_text[0],8);

		  sequence_number++;
		  memmove(&header_frame[4],&sequence_number,8);
   	
	//	  temp = 36+32+10*number_of_chenal+2+108+size*number_of_chenal;	 // 1 канал
		  temp = 36+32+2+(10+108+size)*number_of_chenal;
	//	  temp = 36+32+30+2+108+size;		   					         // 3 канала
		  memmove(&header_frame[28],&temp,4);       // трейлер оффсет ??

		  temp = number_of_chenal;					// число каналов
		  memmove(&sub_header_frame [28],&temp,4);  
	
		  temp = 1000*time_write;
		  memmove(&sub_header_frame [24],&temp,4);  // время записи

		  temp = 10*number_of_chenal;				// 10 байт на один канал
		  memmove(&sub_header_frame [0],&temp,4);   // channel_string_count 

		  plase_header();			  //36
		  plase_subheader();		  //32
		  plase_datakadr();			  //508	  4908
		  plase_trailer();

		  		
	      b_count=0;
	 

		
}

