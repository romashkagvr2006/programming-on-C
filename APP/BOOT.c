//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <LPC22XX.H>
#include <stdio.h>
#include <string.h>
#include <RTL.h>
//#include "..\INC\File_Config.h"
#include "..\APP\EXTERNALS.h"
#include <File_Config.h>

#ifdef USE_SIMULATOR

const unsigned int RAM_image[] = {0xEFE8F220,0xE8F0EF20,0xE0F0EEE1};

const char HEX_sample[] = {

":0400000500000000F7\r\n"
":020000040000FA\r\n"
":1000000018F09FE518F09FE518F09FE518F09FE5C0\r\n"
":1000100018F09FE50000A0E1F0FF1FE518F09FE554\r\n"
":1000200058000000400000004400000048000000AC\r\n"
":100030004C000000000000005000000054000000D0\r\n"

":10FFF000293C62723E0D0A73342020202020202DDF\r\n"
":0400000500010000F6\r\n"
":020000040001F9\r\n"
":1000000020F2E8EF20EFF0E8E1EEF0E0202855499B\r\n"

":102CB0000000000000000000000000000000000014\r\n"
":102CC0000000000000000000000000000000000004\r\n"
":102CD00000000000000000000000000000000000F4\r\n"
":042CE00000000000F0\r\n"
":00000001FF\r\n"

};

#else

const unsigned int RAM_image[] = {
0xE92D47F0,0xE24DD028,0xE3A04000,0xE3A06481,0xE3A0A000,0xEA00004A,0xE3A00032,0xE58D0014,
0xE58DA018,0xE58DA01C,0xE1A0100D,0xE28D0014,0xE3E0213A,0xE1A0E00F,0xE12FFF12,0xE3A00034,
0xE58D0014,0xE58DA018,0xE58DA01C,0xE59F0110,0xE58D0020,0xE1A0100D,0xE28D0014,0xE3E0213A,
0xE1A0E00F,0xE12FFF12,0xE35A0008,0x3A000001,0xE35A0009,0x9A000001,0xE3A09008,0xEA000000,
0xE3A09040,0xE3A05000,0xE3A07000,0xEA000022,0xE3A08000,0xEA000003,0xE7960108,0xE59F20C4,
0xE7820108,0xE2888001,0xE3580C01,0x3AFFFFF9,0xE3A00032,0xE58D0014,0xE58DA018,0xE58DA01C,
0xE1A0100D,0xE28D0014,0xE3E0213A,0xE1A0E00F,0xE12FFF12,0xE3A00033,0xE58D0014,0xE0850004,
0xE58D0018,0xE59F007C,0xE58D001C,0xE3A00B01,0xE58D0020,0xE59F0068,0xE58D0024,0xE1A0100D,
0xE28D0014,0xE3E0213A,0xE1A0E00F,0xE12FFF12,0xE2866B01,0xE2855B01,0xE2877001,0xE1570009,
0x3AFFFFDA,0xE35A0008,0x3A000001,0xE35A0009,0x9A000001,0xE2844A02,0xEA000000,0xE2844801,
0xE28AA001,0xE35A0010,0x3AFFFFB2,0xE3A00000,0xE1A0E00F,0xE12FFF10,0xE28DD028,0xE8BD47F0,
0xE12FFF1E,0x00003999,0x40002000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000001,0x00000480,0x00000000,0x00000000,0x00000001,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x40000170,0x000004E4,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};

#endif

//---------------------------------
// Update firmware      
//---------------------------------
void Boot(void)  {

char * p;
char   buf[128];
U32    hex_index;
U32    hex_line;

U32  * d;
U32    i;

U32    offset;
U32    addr;
U32    v;
U8     len;
U8     check;
U8     tag;



printf("Parsing BOOT.HEX file...\n"); fflush (stdout);

d = (U32*)(RAM_AREA);
for(i = 0; i < MAX_BOOT_SIZE/4; i++) d[i] = 0xFFFFFFFF;

#ifdef USE_SIMULATOR
p = (char*)(RAM_AREA + MAX_BOOT_SIZE);
for(i = 0; HEX_sample[i]; i++) p[i] = HEX_sample[i];
#endif

// Parse HEX strings

offset = 0; hex_index = 0; hex_line = 0;
while(1)
  {
  for(i = 0; i < 128; i++)
    {
	if(':' == rd_ex_ram(RAM_AREA + MAX_BOOT_SIZE + (hex_index++) )) goto boot_phase1;
	}
  goto boot_err;

boot_phase1:

  for(i = 0; i < 128; i++)
    {
	buf[i] = rd_ex_ram(RAM_AREA + MAX_BOOT_SIZE + (hex_index++) );
	if(buf[i] == 13)  goto boot_phase2;
	}
  goto boot_err;

boot_phase2:
  
  hex_line++;

  if(hex_index > (RAM_AREA + RAM_SIZE - 256) ) goto boot_err;
  
  p = buf; check = 0;

  sscanf(p,"%2x",&v); len  = v; check += len; p += 2;
  sscanf(p,"%4x",&v); addr = v; check += (addr>>8) + (addr);  p += 4;
  sscanf(p,"%2x",&v); tag  = v; check += tag; p += 2;

  if(len > 32)  goto boot_err;
  
  if( (len == 2) && (tag == 4) )
    {
    sscanf(p,"%4x",&v); offset = v*65536; check += (v>>8) + (v);  p += 4;
    if(offset > (MAX_BOOT_SIZE - 65536)) goto boot_err;
    }
  else
    {
    for(i = 0; i < len; i++)
      {
      sscanf(p, "%2x", &v);
      check+=v; p+=2; 
      if(tag == 0) wr_ex_ram(RAM_AREA + offset + (addr++) , (U8)v);
      }
    }

  sscanf(p, "%2x", &v);
  if( (check + v) & 0xFF ) goto boot_err;

  if( (len == 0) && (tag == 1) && (addr == 0) ) break;
  }

// Search for RAM_image

d = (U32*)(RAM_AREA); v = 1;
for(i = 0; i < (MAX_BOOT_SIZE - sizeof(RAM_image))/4; i++)
  {
  if(RAM_image[0] == d[i])
    {  
    v = 0;
	for(addr = 1; addr < sizeof(RAM_image)/4; addr++)
	if(RAM_image[addr] != d[addr + i]) { v = 1; break; }
    }
  if(v == 0) break;
  }

if(v)
  {
  printf("BOOT.HEX file error - ram image not found\n"); fflush (stdout);
  STATUS |= ER_BAD_HEX_FILE;
  process_cmd_stop();
  return;
  }

// Calculate signature for vector 0x14

d = (U32*)(RAM_AREA); d[5] = 0; v = 0;
for(i = 0; i < 8; i++) v += d[i];
d[5] = -v;

printf("BOOT.HEX file OK. Write to FLASH...\n"); fflush (stdout);

d = (U32*)(0x40000000);
for(i = 0; i < sizeof(RAM_image)/4; i++) d[i] = 0;
for(i = 0; i < sizeof(RAM_image)/4; i++) d[i] = RAM_image[i];

((void (*)(void)) (0x40000000)) ();

boot_err:

printf("BOOT.HEX file parsing error at line %u\n", hex_line); fflush (stdout);
STATUS |= ER_BAD_HEX_FILE;
process_cmd_stop();

}

//-------------------------------------
// Erase FLASH area : 0x20000..0x3BFFF     
//-------------------------------------
void boot_arm_erase_flash(void) {
fs_EraseSector (0x20000);
fs_EraseSector (0x30000);
fs_EraseSector (0x32000);
fs_EraseSector (0x34000);
fs_EraseSector (0x36000);
fs_EraseSector (0x38000);
fs_EraseSector (0x3A000);
}

//-------------------------------------
// Write to FLASH  : 0x20000..0x3BFFF     
//-------------------------------------
int boot_arm_write_flash(U8 *buf, U32 len) {

if( (0x20000 + file_data_count) >= 0x3C000 ) return(0);

if( (0x20000 + file_data_count + len) >= 0x3C000 ) len = 0x3C000 - 0x20000 - file_data_count; 

fs_ProgramPage (0x20000 + file_data_count, len, buf);

file_data_count += len;

return(0);
}

//---------------------------------
// Update firmware from FLASH     
//---------------------------------
void Boot_arm(void)  {
U32 i;
U32 v;

v = 0; i = 0x20000;
while(i < 0x3C000)
  {
  v += *(U32*)(i); i+= 4;
  }

if(v) { print_log("Bad code area check sum\n",  0,0); STATUS |= ER_BAD_HEX_FILE; return; }

v = 0; i = 0x20200;
while(i < 0x20220)
  {
  v += *(U32*)(i); i+= 4;
  }
if(v) { print_log("Bad vector area check sum\n",  0,0); STATUS |= ER_BAD_HEX_FILE; return; }

printf("!!!UPDATE FIRMWARE (BOOT.ARM)!!!\n"); fflush (stdout);

((void (*)(void)) (0x2007C)) ();

}
