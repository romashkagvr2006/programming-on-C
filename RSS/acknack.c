
#include <RTL.h>
#include "..\APP\EXTERNALS.h"
#include <string.h>


U8 st_ack;
U8 number_ack;
U8 acknack_buf[80];
U32 n_ack;
unsigned long long highest_number;
unsigned long long adres_h;
unsigned long long adres_l;
	  /*
void acknack(void){
U8 ack_temp[8];
U8 ack_adr;
 

	  ack_adr = (n_ack * 16) - 1;
		  ack_temp[0] = acknack_buf[ack_adr];
		  ack_temp[1] = acknack_buf[ack_adr-1];
		  ack_temp[2] = acknack_buf[ack_adr-2];
		  ack_temp[3] = acknack_buf[ack_adr-3];
		  ack_temp[4] = acknack_buf[ack_adr-4];
		  ack_temp[5] = acknack_buf[ack_adr-5];
		  ack_temp[6] = acknack_buf[ack_adr-6];
		  ack_temp[7] = acknack_buf[ack_adr-7];

		  memcpy(&adres_h,&ack_temp[0],8);

		  ack_temp[0] = acknack_buf[ack_adr-8];
		  ack_temp[1] = acknack_buf[ack_adr-9];
		  ack_temp[2] = acknack_buf[ack_adr-10];
		  ack_temp[3] = acknack_buf[ack_adr-11];
		  ack_temp[4] = acknack_buf[ack_adr-12];
		  ack_temp[5] = acknack_buf[ack_adr-13];
		  ack_temp[6] = acknack_buf[ack_adr-14];
		  ack_temp[7] = acknack_buf[ack_adr-15];

		  memcpy(&adres_l,&ack_temp[0],8);

//		  FlashPage[11]= highest_number;
//		  FlashPage[12]= adres_h;
//		  FlashPage[13]= adres_l;

		  ack_adr = (transmit_max - (highest_number - adres_h));	 // Последний потеряный кадр из st_asc_frame

		   if(	(sequence_number - highest_number) == 1){
				  ack_adr =	transmit_max;
			 }

		  number_ack = (adres_h - adres_l) + 1;		 // Сколько потеряных кадров из 10

		  for (st_ack = 0; st_ack < number_ack; st_ack++){ 

 memcpy(&rep_servis_frame[st_ack*size_of_send_data],&asc_servis_frame[ack_adr*size_of_send_data],size_of_send_data);
					 ack_adr--;				// Переписываю из резервного буфера в буфер повторной выдачи
		  }
			  st_ack = 0;

}

	 */
	   /*
void get_rep_frame (void){	// Переписываю потерянный фрагмент в выходной буфер

 memcpy(&(*(out_udp_adr)),&rep_servis_frame[st_ack*size_of_send_data],size_of_send_data);

			   st_ack ++;
			   number_ack--;
			   b_count=0;
		 SETBIT(flag1,SEND);			   //  Разрешение на передачу

}		 */
