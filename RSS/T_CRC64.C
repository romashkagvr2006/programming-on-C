


//		 Рабочий вариант расчета контрольной суммы длч CD1-1.

#include <RTL.h>
#include "..\APP\EXTERNALS.h"
#include <string.h>



// CRC parameters :

 int order = 64;									
 unsigned long long polynom = 0x000000000000001B;
 
 int direct = 1;
 
 unsigned long long crcinit = 0;
 unsigned long long crcxor = 0xffffffffffffffff;

 int refout = 0;

// Образец строки для проверки алгоритма

// unsigned char string[] = {"1234567812345678"};	  //CRC=0x42A1F9623FDC8C99



unsigned long long crcmask;
unsigned long long crchighbit;
unsigned long long crcinit_direct;
unsigned long long crcinit_nondirect;

const unsigned long long crctab[256]=		   
{    0,   27,   54,   45,  108,  119,   90,   65,  216,  195,  238,  245,  180,  175,  130,  153,
   432,  427,  390,  413,  476,  455,  490,  497,  360,  371,  350,  325,  260,  287,  306,  297,
   864,  891,  854,  845,  780,  791,  826,  801,  952,  931,  910,  917,  980,  975,  994, 1017,
   720,  715,  742,  765,  700,  679,  650,  657,  520,  531,  574,  549,  612,  639,  594,  585,
  1728, 1755, 1782, 1773, 1708, 1719, 1690, 1665, 1560, 1539, 1582, 1589, 1652, 1647, 1602, 1625,
  1904, 1899, 1862, 1885, 1820, 1799, 1834, 1841, 1960, 1971, 1950, 1925, 1988, 2015, 2034, 2025,
  1440, 1467, 1430, 1421, 1484, 1495, 1530, 1505, 1400, 1379, 1358, 1365, 1300, 1295, 1314, 1337,
  1040, 1035, 1062, 1085, 1148, 1127, 1098, 1105, 1224, 1235, 1278, 1253, 1188, 1215, 1170, 1161,
  3456, 3483, 3510, 3501, 3564, 3575, 3546, 3521, 3416, 3395, 3438, 3445, 3380, 3375, 3330, 3353,
  3120, 3115, 3078, 3101, 3164, 3143, 3178, 3185, 3304, 3315, 3294, 3269, 3204, 3231, 3250, 3241,
  3808, 3835, 3798, 3789, 3724, 3735, 3770, 3745, 3640, 3619, 3598, 3605, 3668, 3663, 3682, 3705,
  3920, 3915, 3942, 3965, 3900, 3879, 3850, 3857, 3976, 3987, 4030, 4005, 4068, 4095, 4050, 4041,
  2880, 2907, 2934, 2925, 2860, 2871, 2842, 2817, 2968, 2947, 2990, 2997, 3060, 3055, 3010, 3033,
  2800, 2795, 2758, 2781, 2716, 2695, 2730, 2737, 2600, 2611, 2590, 2565, 2628, 2655, 2674, 2665,
  2080, 2107, 2070, 2061, 2124, 2135, 2170, 2145, 2296, 2275, 2254, 2261, 2196, 2191, 2210, 2233,
  2448, 2443, 2470, 2493, 2556, 2535, 2506, 2513, 2376, 2387, 2430, 2405, 2340, 2367, 2322, 2313};



	/*
void generate_crc_table() {
  	int i, j;
	unsigned long long bit, crc;
	// make CRC lookup table used by table algorithms

		// at first, compute constant bit masks for whole CRC and CRC high bit

	crcmask = ((((unsigned long long)1<<(order-1))-1)<<1)|1;
	crchighbit = (unsigned long long)1<<(order-1);

  
	// generate lookup table
  
	for (i=0; i<256; i++) {

		crc=(unsigned long long)i;

		crc<<= order-8;

		for (j=0; j<8; j++) {

			bit = crc & crchighbit;
			crc<<= 1;
			if (bit) crc^= polynom;
		}			


		crc&= crcmask;
		crctab[i]= crc;
	}
}

	 */
		
unsigned long crctablefast (U8 *p, U32 len) {
U32 temp_c;
unsigned long long crc =0;
U8 temp_crc[8];
U8 dc;
 	   temp_c = len;

	 while (len--) crc = (crc << 8) ^ crctab[ ((crc >> (order-8)) & 0xff) ^ *p++];

	 memcpy(&temp_crc,&crc,8);

		   for (dc=0;dc<8;dc++){					   // Заношу CRC64  в конец пакета
			*(out_udp_adr+temp_c+dc) =	temp_crc[7-dc];
		   }
  
	return(crc);
}

   /*
 

int main() {

	// test program for checking four different CRC computing types that are:
	//  crctablefast().
	// 
	// 

//	int i;
//	unsigned long bit, crc;

  
	// at first, compute constant bit masks for whole CRC and CRC high bit

//	crcmask = ((((unsigned long long)1<<(order-1))-1)<<1)|1;
//	crchighbit = (unsigned long long)1<<(order-1);

  
	// generate lookup table

//	generate_crc_table();
  
 crctablefast((unsigned char *)string, strlen(string));		 //22.45mks
 


	return(0);
}

   */
