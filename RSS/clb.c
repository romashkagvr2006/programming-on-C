

#include "..\APP\EXTERNALS.h"
#include <string.h>
#include <math.h>

float f_clb;
float a_clb;
float t_clb;
float popr_clb;
float AD_popr;
float AD_T;

float out_amp_s[3];
float out_amp_kp[3];
float	faza[3];
float	kp[3];
float	kp_db[3];
float	cnrk[3];

U8 r_clb;
U8 N_clb = 3;

S32 clb_data_X[120];
S32 clb_data_Y[120];
S32 clb_data_Z[120];

void set_clb_f(void){		   // Задать частоту калибровки
U16 f_sin;
U8 k_popr;


	FSUK_KOMANDA[0]=5;		  //команда для ФСУК - Произвести калибровку
	

	if (f_clb >= 1){

	   FSUK_KOMANDA[1] = 1;					// частота больше 1 Гц
	   f_sin = f_clb;
	   memcpy (&FSUK_KOMANDA[2],&f_sin,2);
	   clb_time = 32; 					  // Время калибровки определяет ФСУК ~ 30*f_clb
	   clb_init = 11;
	}

	   else  {
		   FSUK_KOMANDA[1] = 0;					// частота меньше 1 Гц

		   f_sin = 1000*f_clb;
		   f_sin = 1000/f_sin;		// ПЕРИОД СИГНАЛА
		   clb_init = 7 * f_sin;	// определение фазы через 7 периодов сигнала 
		   clb_time = f_sin * 16+2;	// Время калибровки определяет ФСУК ~ 15 периодов
		   clb_init =  clb_init + 2;
		   f_clb = 1.0/f_sin;
		   f_sin = 1000/f_sin;

		   memcpy (&FSUK_KOMANDA[2],&f_sin,2);
	          
		 }
		  switch (PCLState)				// Тип калибровки
		  {
		  	case '1':
									    // Регистратор
				break;
			case '2':					// Внутренняя резистивная
					FSUK_KOMANDA[1] |= 0x20;				    
				break;				   
			case '3':				    // Внутренняя ёмкостная
					FSUK_KOMANDA[1] |= 0x28;				    
				break;
			case '4':				    // Внешняя резистивная
					FSUK_KOMANDA[1] |= 0x40;				    
				break;
			case '5':				    // Внешняя ёмкостная
					FSUK_KOMANDA[1] |= 0x48;				     
				break;
			
		  }

	//		  N_clb = 3;	  number_of_chenal
			  N_clb = number_of_chenal;

		//Расчёт поправки на сдвиг ФНЧ на 825 ms для Fацп = 120 Гц(175 ms это  (1000 - 825 = 175ms))сигнал начинается 
			t_clb = (1.0/f_clb) *1000.0;		 // на 175 мс раньше точки измерения фазы
	 // 		popr_clb = (175.0/t_clb)*360.0;
 			popr_clb = (AD_popr/t_clb)*360.0;

		   	k_popr =  popr_clb/360.0;

			  if (k_popr != 0){
		   		  popr_clb = popr_clb - (360.0 * k_popr);
			   }

		if 	(popr_clb > 180)  popr_clb = popr_clb - 360.0;
				
		 
		  FSUK_KOMANDA[4]	= 0;
		  FSUK_KOMANDA[5]	= 0;
		  FSUK_KOMANDA[6]	= 0;
		  FSUK_KOMANDA[7]	= 0;
		  FSUK_KOMANDA[8]	= 0;
		  FSUK_KOMANDA[9]	= 0;
		  FSUK_KOMANDA[10]	= 0;
		  FSUK_KOMANDA[11]	= 0;

}
///*

	   
void ampl(void)	// Расчет амплитуды калибровочного сигнала время расчета около 30 mc

{	unsigned char i, k, l, m, vybor = 10, cykl = 12, h;
	float rr, a[2][3], w, s, c, det, x1, x2, out_amp, pi = 3.14159;
          
	S32 *  pAdd;

		   out_amp_s[0] =0;
		   out_amp_s[1] =0;
		   out_amp_s[2] =0;
		//  	rr = 2*pi*1/128;		 

			rr = 2*pi*f_clb/data_rate;	  // 2*pi*fсигн/sampl rate

	 for (h = 0; h < number_of_chenal; h++){	// number_of_chenal прохода, рассчет по каналам X,Y,Z 

	 switch (h)
	 {										    // выбор базового адреса канала
	 	case 0:
				  pAdd=&clb_data_X[0];
			break;
		case 1:
				  pAdd=&clb_data_Y[0];
			break;
		case 2:
				  pAdd=&clb_data_Z[0];
			break;
	}


				m = 0;

	  	for (l = 0; l < cykl ; l++){				   

	   		for (i = 0; i <2 ; i++){
		   		for (k = 0; k <3 ; k++){
			  			a[i][k]=0;
					}
			}

	 //   Алгоритм восстановления аплитуды гармонического сигнала
     //   методом наименьших квадратов
	 

			for (i = 0; i < vybor; i++){

				w = rr*i;
				s = sin(w);
				c = cos(w);

				a[0][0] = a[0][0] + s*s;
				a[0][1] = a[0][1] + s*c;

				a[0][2] = a[0][2] + (*(pAdd + i + m))*s;	//  
				a[1][2] = a[1][2] + (*(pAdd + i + m))*c;	// 

			
		      }
				 	m = m + vybor;

			a[1][0] = a[0][1];
			a[1][1] = vybor - a[0][0];
			det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
			x1 = (a[0][2] * a[1][1] - a[0][1] * a[1][2])/det;
			x2 = (a[0][0] * a[1][2] - a[0][2] * a[1][0])/det;
			out_amp = sqrt((x1)*(x1) + (x2)*(x2));
			out_amp_s[h] = out_amp_s[h] + out_amp;
	

			if (l ==0 ){

				faza[h] = atan2 (x2,x1);			      //Фаза в радианах

 
		    	faza[h] = faza[h] * (180.0/pi) - popr_clb;  //Фаза в градусах	c учетом
														    //сдвига ФНЧ на время групповой задержки


				   i = faza[h]/360.0;
				if (i != 0)	{
				   faza[h] = faza[h]/i;
				}
				
				if (faza[h] < -180.0){
				  faza[h] = 360.0 + faza[h];
				  goto mmm;
				  }
					if (faza[h] > 180.0) {
				  		faza[h] = faza[h] - 360.0;
					}
					
  mmm:
			}
	
	}
// Расчет АЧХ и ЦНРК при внутренней калибровке регистратора и 	
// емкостной калибровке.
	  		
			out_amp_s[h] = out_amp_s[h]/cykl;		 //  амплитуда сигнала

					if (f_clb == 3){				  // Центральная частота 1 и 3 Гц
					   out_amp_kp[h] = out_amp_s[h];

					cnrk[h] = (1.4142135 * a_clb)/out_amp_s[h]; 	// ЦНРК

					  }

				  kp[h] = out_amp_s[h]/out_amp_kp[h];	            //  Кп по АЧХ
				  kp_db[h] = (log10(kp[h]))*10; 		            //  Кп по АЧХ в дБ

		
   
   }
 }

  // */
