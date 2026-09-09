 
 ///////////////////////////////////////////////////////////////////////////////
 //		  ПРИЁМ ИНФОРМАЦИИ ПО ПРОТОКОЛУ NMEA ОТ GPS/ГЛОНАСС					  //
 //																			  //
 //		  Выделяю время из пакетов GGA, GLL, ZDA, RMC,						  //
 //																			  //

#include <RTL.h>
#include "..\APP\EXTERNALS.h"
#include  <stdlib.h>
#include <string.h>
#include <LPC22XX.H>


//char GPS_string[]= {"$GPGGA,004241.47,5532.8492,N,03729.0987,E,1,04,2.0,-0015,M,,,,*31"};
//char n_GPS_fild[]={7,17,27,29,40,42,44,47,51,57,59};

//char GPS_string[]= {"$GPGLL,5532.8492,N,03729.0987,E,004241.469,A*33"};
//char n_GPS_fild[]={7,17,19,30,32,43};
					 //  $GPZDA,072209.1,24,04,2012,,*5A   //
//char GPS_string[]= {"$GPZDA,172809,12,07,1996,00,00*45"};
//char n_GPS_fild[]={7,14,17,20,25,28};

//char GPS_string[]= {"$GPRMC,004241.47,A,5532.8492,N,03729.0987,E,12.5,12.6,120796,2.3,E,A*31"};
//char n_GPS_fild[]={7,17,19,29,31,42,44,49,54,61,65,67};

U8 receive_start;
U8 receive_crc;
char GPS_string[120];
char crc_string[2];
U8	crc_st;
U16 GPS_st;
U16 fild_st;
char n_GPS_fild[20];
U8 GPS_Quality;
U8 GPS_status;
U8 GPS_rej;
U8 n_Satellites;

U8 GPS_hour;
U8 GPS_min;
U8 GPS_sec;
U8 GPS_dom;
U8 GPS_month;
U16 GPS_year=12;

//===========================================================================
char getchar1 (void) 				// Read character from Serial Port 1  
{                    
  while (!(U1LSR & 0x01));
  return ( U1RBR);
}
//===========================================================================

void GPS_time (void){	   // Выделяю время из принятых пакетов	GGA, RMC, GLL, ZDA
						   //	в пакетах GSA GSV VTG нет параметров времени
						   //	  
U32 gps_temp;							  	  
char name[3];
char st_fild;
char leap;


//	 IO1SET |= 0x00020000;


if (CHECKBIT(flag1,NMEA)) {


	   memcpy(&name[0],&GPS_string[3],3);

	if (strcmp(name, "GGA") == 0){		      // GGA*****************
 ///*
			st_fild = n_GPS_fild[5];
			memcpy(&name,&GPS_string[st_fild],1);
			name[1]='\0';
			GPS_Quality = atoi(name);					  // Режим работы приемника (Статус)


			st_fild = n_GPS_fild[6];		              
			memcpy(&name,&GPS_string[st_fild],2);
			name[2]='\0';
			n_Satellites = atoi(name);
								 						  // Количество спутников

		if (GPS_Quality != 0){			 // Проверяю статус

			st_fild = n_GPS_fild[0];					  // Время UTC

			memcpy(&name,&GPS_string[st_fild],2);
			name[2]='\0';
			GPS_hour = atoi(name);

			memcpy(&name,&GPS_string[st_fild+2],2);
			name[2]='\0';
			GPS_min = atoi(name);

			memcpy(&name,&GPS_string[st_fild+4],2);
			name[2]='\0';
			GPS_sec = atoi(name);
		 }
//	*/														
	 }

	if (strcmp(name, "RMC") == 0){		   // RMC *******************
///*
			st_fild = n_GPS_fild[1];						//   Статус
			GPS_status = GPS_string[st_fild];

		if (GPS_status == 'A'){			   // Проверяю статус

		    st_fild = n_GPS_fild[0];					    //	 Время UTC
		    
			memcpy(&name,&GPS_string[st_fild],2);
			name[2]='\0';
			GPS_hour = atoi(name);

			memcpy(&name,&GPS_string[st_fild+2],2);
			name[2]='\0';
			GPS_min = atoi(name);

			memcpy(&name,&GPS_string[st_fild+4],2);
			name[2]='\0';
			GPS_sec = atoi(name);
		   			

			st_fild = n_GPS_fild[8];					   // День, месяц, год
			 memcpy(&name,&GPS_string[st_fild],2);
			 name[2]='\0';
			 GPS_dom = atoi(name);

			 						
			 memcpy(&name,&GPS_string[st_fild+2],2);	   // месяц
			 name[2]='\0';
			 GPS_month = atoi(name);

									
			 memcpy(&name,&GPS_string[st_fild+4],2);	   // год - 2 младшие цифры		 
			 name[2]='\0';
			 GPS_year = atoi(name);
		 }
//	*/   
	}											    
														    


	if (strcmp(name, "GLL") == 0){		   // GLL ****************************
///*
			st_fild = n_GPS_fild[5];						//   Статус
			GPS_status = GPS_string[st_fild];

		if (GPS_status == 'A'){			   // Проверяю статус

			st_fild = n_GPS_fild[4];					    //	 Время UTC
		     
			memcpy(&name,&GPS_string[st_fild],2);
			name[2]='\0';
			GPS_hour = atoi(name);

			memcpy(&name,&GPS_string[st_fild+2],2);
			name[2]='\0';
			GPS_min = atoi(name);

			memcpy(&name,&GPS_string[st_fild+4],2);
			name[2]='\0';
			GPS_sec = atoi(name);
		 }

//	*/		 

	}


	if (strcmp(name, "ZDA") == 0){						    // ZDA
 ///*
			st_fild = n_GPS_fild[0];					    // Время UTC

			memcpy(&name,&GPS_string[st_fild],2);
			name[2]='\0';
			GPS_hour = atoi(name);

			memcpy(&name,&GPS_string[st_fild+2],2);
			name[2]='\0';
			GPS_min = atoi(name);

			memcpy(&name,&GPS_string[st_fild+4],2);
			name[2]='\0';
			GPS_sec = atoi(name);
		     

			 st_fild = n_GPS_fild[1];					    // день
			 memcpy(&name,&GPS_string[st_fild],2);
			 name[2]='\0';
			 GPS_dom = atoi(name);

			 st_fild = n_GPS_fild[2];						// месяц
			 memcpy(&name,&GPS_string[st_fild],2);
			 name[2]='\0';
			 GPS_month = atoi(name);

			 st_fild = n_GPS_fild[3];						// год - 2 младшие цифры
			 memcpy(&name,&GPS_string[st_fild+2],2);			 
			 name[2]='\0';
			 GPS_year = atoi(name);
	//	  */

	}

}

else
	   {
	   
//IO1SET |= 0x00020000;	   
	  
	   ///////////////////////////////////////////////////////////////////////////////
 //		  ПРИЁМ ИНФОРМАЦИИ ПО ПРОТОКОЛУ BINARY ОТ приёмника СПА 			  //
 //																			  //
 //		  Выделяю время из пакетов 149, 154, 159,   						  //
 //

						GPS_status ='V';
					    GPS_Quality=0;
 
 			switch (GPS_string[3])
			{
				case 0x95:						       // Пакет ID = 149
				   
						  //GPS_status ='V';
				/*	   					
						   GPS_Quality=	(GPS_string[7] & 0x04) >> 2;
						   if(!(GPS_string[6] & 0x40)) GPS_status ='A';
							 else                      GPS_status ='V'; 
			   			   GPS_hour = GPS_string[8]	 ;
						   GPS_min  = GPS_string[9]	 ;
						   GPS_sec  = GPS_string[10] ;
						   GPS_year = GPS_string[16] ;
						   GPS_month= GPS_string[17] ;
						   GPS_dom	= GPS_string[18] ;
					*/
					break;

				case 0x9A:						       // Пакет ID = 154

				   		   //GPS_status ='V';
				/*				
						   GPS_Quality=	(GPS_string[7] & 0x04) >> 2;
						   if(!(GPS_string[6] & 0x40)) GPS_status ='A';
							 else                      GPS_status ='V'; 
						   GPS_hour = GPS_string[8]	 ;
						   GPS_min  = GPS_string[9]	 ;
						   GPS_sec  = GPS_string[10] ;
						   GPS_year = GPS_string[16] ;
						   GPS_month= GPS_string[17] ;
						   GPS_dom	= GPS_string[18] ;
					 */
					break;

				case 0x9F:						       // Пакет ID = 159
		
	  // /*				  
	  			   memcpy(&gps_temp,&GPS_string[14],4);	  // ПРоверка дробной части секунды 

					 if ((gps_temp & 0xFFFFFF00) == 0){	  // записываю только целую секунду
				  
						   n_Satellites = 0;
						   if(!(GPS_string[6] & 0x40)) GPS_status ='A';
							 else                      GPS_status ='V'; 

						   GPS_Quality=	(GPS_string[7] & 0x04) >> 2;

						   GPS_hour = GPS_string[10] ;
						   GPS_min  = GPS_string[11] ;
						   GPS_sec  = GPS_string[12] ;
						   GPS_year = GPS_string[18] ;
						   GPS_month= GPS_string[19] ;
						   GPS_dom	= GPS_string[20] ;

						   memcpy(&gps_temp,&GPS_string[58],4);	   // ГЛОНАСС
						   for(leap = 0;leap < 32;leap ++)
						   {
								if (gps_temp & 0x00000001) n_Satellites++;
								    gps_temp = gps_temp >> 1;
						   }


						   memcpy(&gps_temp,&GPS_string[54],4);	   // GPS
						   for(leap = 0;leap < 32;leap ++)
						   {
								if (gps_temp & 0x00000001) n_Satellites++;
								    gps_temp = gps_temp >> 1;
						   }





				//	  */
					 }
					break;

			}
// IO1CLR |= 0x00020000;
 
 	   }


	//	GPS_rej = 0;

//	/*
	   if((GPS_Quality == 0)|(GPS_status != 'A'))  GPS_rej = 0;

	   if((GPS_Quality != 0)|(GPS_status == 'A')){	 // Если работает GPS
//	 */
/// IO1SET |= 0x00020000;

				   if (CHECKBIT(flag2,TF)){
							 test_timer++;
					 }



		 GPS_rej = 1;

			YEAR    = 2000 + GPS_year;
   			MONTH   = GPS_month;
   			DOM     = GPS_dom;
   			HOUR    = GPS_hour;
   			MIN     = GPS_min;
			SEC     = GPS_sec;
		
	
		
			leap = 28;
				if ((YEAR & 0x003) == 0)	leap = 29;  

  switch(GPS_month){		 					// 
				
		
		case 1:	 
					DOY	= GPS_dom;	//31	
		   	break;

		case 2:	 	
					DOY	= GPS_dom + 31;		 // 28-29
		   	break;

		case 3:	 
					DOY	= GPS_dom + 31+leap;	
		   	break;

		case 4:	 
					DOY	= GPS_dom + 62+leap;//30;			
		   	break;

		case 5:
			 		DOY	= GPS_dom + 92+leap;// 31;		
		   	break;

		case 6:
					DOY	= GPS_dom + 123+leap;//30;	 			
		   	break;

		case 7:	
					DOY	= GPS_dom + 153+leap;//31; 			
		   	break;

		case 8:
					DOY	= GPS_dom +184 +leap;//31;	 			
		   	break;

		case 9:	 
					DOY	= GPS_dom +215+leap;// 30;			
		   	break;

		case 10:
					DOY	= GPS_dom +245+leap;// 31;	 			
		   	break;

		case 11:
					DOY	= GPS_dom + 276+leap;//30;	 			
		   	break;

		case 12:
					DOY	= GPS_dom +306+leap;// 31;	 			
		   	break;
			}
//		  }
	   }
 ///  IO1CLR |= 0x00020000;



 //	*/											
}


  //*************** Переписываю время из часов  ************
  //            для выдачи в следующем выходном потоке


void write_time(void){
U8 GPS_dt;


	   		time [15] = (SEC % 10)|0x30;
	        time [14] = (SEC / 10)|0x30;

		    time [12] = (MIN % 10)|0x30;
	        time [11] = (MIN / 10)|0x30;

	  	   	time [9] = (HOUR % 10)|0x30;
	        time [8] = (HOUR / 10)|0x30;



				GPS_dt= DOY / 100;
  	time [4] = GPS_dt | 0x30;						 // день года
    time [5] = ((DOY - (GPS_dt * 100)) / 10) | 0x30;
    time [6] = ((DOY - (GPS_dt * 100)) % 10) | 0x30;

	time [0] = 0x32;
	time [1] = 0x30;
	time [2] = (GPS_year/10) | 0x30;	                // год - 2 младшие цифры
	time [3] = (GPS_year%10) | 0x30;

}
