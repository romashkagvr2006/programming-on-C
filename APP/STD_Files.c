//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <LPC22XX.H>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <RTL.h>
#include "..\APP\EXTERNALS.h"


//------------------------
// Read status as html
//------------------------
void read_settings_as_html(void) {
U8  p;
U32 i;
float f;

p = sprintf(html_buf,"<tr><td>%u</td><td>",file_data_count);

if(file_data_count == 0) //SIGNATURE	 
  {
  p += sprintf(html_buf + p,"0x%08X</td></tr>", FlashPage[file_data_count]);
  file_data_count++; return;
  }

if(file_data_count == 1) //STATUS		 
  {
  p += sprintf(html_buf + p,"0x%08X</td></tr>", FlashPage[file_data_count]);
  file_data_count++; return;
  }

if(file_data_count == 5) //DATA_START	
  {
  p += sprintf(html_buf + p,"%u(0x%08X)</td></tr>", FlashPage[file_data_count], FlashPage[file_data_count]);
  file_data_count++; return;
  }
if(file_data_count == 6) //DATA_LENGTH
  {
  p += sprintf(html_buf + p,"%u(0x%08X)</td></tr>", FlashPage[file_data_count], FlashPage[file_data_count]);
  file_data_count++; return;
  }

if(file_data_count == 7) //MAC1		
  {
  p += sprintf(html_buf + p,"0x%08X</td></tr>", FlashPage[file_data_count]);
  file_data_count++; return;
  }

if(file_data_count == 8) //MAC2		 
  {
  p += sprintf(html_buf + p,"0x%08X</td></tr>", FlashPage[file_data_count]);
  file_data_count++; return;
  }

if(file_data_count == 9) //IP		 
  {
  i = FlashPage[file_data_count];
  p += sprintf(html_buf + p,"%d.%d.%d.%d</td></tr>", (i>>24)&0xFF,(i>>16)&0xFF,(i>>8)&0xFF,i&0xFF);
  file_data_count++; return;
  }

if( (file_data_count >= 27)&&(file_data_count <= 34) ) //MO,SKO
  {
  f = FlashPage[file_data_count]/100.0;
  sprintf(html_buf + p,"%0.2f</td></tr>", f);
  file_data_count++; return;
  }

sprintf(html_buf + p,"%u</td></tr>", FlashPage[file_data_count]);
file_data_count++;

}

//------------------------
// Read ram as html
//------------------------
	/*
void read_ram_as_html(void) {
U16 a;
U8  c;

phtml_buf = sprintf(html_buf,"<tr><td>%08X</td>", DATA_START + file_data_count); // Address

phtml_buf += sprintf(html_buf+phtml_buf,"<td>");
for(a = 0; a < 16; a++)
  {

  c = rd_ex_ram(DATA_START + file_data_count + a);
  phtml_buf += sprintf(html_buf+phtml_buf,"%02X ", c);
  }

phtml_buf += sprintf(html_buf+phtml_buf,"</td><td> ");
for(a = 0; a < 16; a++)
  {
  c = rd_ex_ram(DATA_START + file_data_count + a);
  if(c < 0x20) c = '.'; 
  html_buf[phtml_buf++] = c;
  }
phtml_buf += sprintf(html_buf+phtml_buf,"</td></tr>");

file_data_count += 16;
}
   */
//------------------------
// Open data file
//------------------------
int std_file_open(const char *name, int openmode) {
U32  i;

i = 0; while(name[i]) tolower(name[i++]);
file_data_count = 0; flash_changed = 0;

if (strcmp(name, "command.txt")  == 0) return (COMMAND_TXT);
if (strcmp(name, "log.txt")      == 0) { pLog_txt = 0; return (LOG_TXT); }
if (strcmp(name, "settings.htm") == 0) return (SETTINGS_HTM);
if (strcmp(name, "settings.bin") == 0) return (SETTINGS_BIN);

//if (strcmp(name, "fifo.htm")     == 0) { Data_Open_Dev(); return (FIFO_HTM);  }
//if (strcmp(name, "fifo.bin")     == 0) { Data_Open_Dev(); return (FIFO_BIN);  }

if (strcmp(name, "ram.htm")      == 0) return (RAM_HTM);
if (strcmp(name, "ram.bin")      == 0) return (RAM_BIN);
//if (strcmp(name, "boot.hex")     == 0) return (BOOT_HEX);
//if (strcmp(name, "boot.arm")     == 0) { boot_arm_erase_flash(); return (BOOT_ARM); }

return(0);
}

//------------------------
// Read from data file
//------------------------
int std_file_read(int fh, U8 *buf, U32 len, int mode) {
U32  l;
static U8 eof;
U8 * p;
char c;

//if(fh == FIFO_BIN)  return(Data_Read_Bin_Dev(buf, len));

//==================================== ram.bin

if(fh == RAM_BIN)
  {
//  for(l = 0; l < len; l++)
//    {
//    buf[l] = rd_ex_ram(DATA_START + file_data_count++);
//    if(file_data_count > DATA_LENGTH) return ( (len - l) | 0x80000000 );
//	}
//  return(0);
  }

//==================================== command.txt

if(fh == COMMAND_TXT)
  {
  for(l = 0; l < len; l++)
    {
    eof = Command_cgi[file_data_count++];
	buf[l] = eof;
	if(eof == 0) return ( (len - l) | 0x80000000 );
    }
  return(0);
  }

//==================================== log.txt
  /*
if(fh == LOG_TXT)
  {
  for(l = 0; l < len; l++)
    {
    c = get_log_char(); buf[l] = c;
	if(c ==  0)   return ( (len - l) | 0x80000000 );
    }
  return(0);
  }
	*/
//==================================== settings.bin

if(fh == SETTINGS_BIN)
  {
  p = (U8*)FlashPage;
  for(l = 0; l < len; l++)
    {
    buf[l] = *(p + file_data_count++);
    if(file_data_count > 4*(LAST_SETTING+1)) return ( (len - l) | 0x80000000 );
	}
  return(0);
  }

//==================================== ...htm           

if( (fh == SETTINGS_HTM)||(fh == FIFO_HTM)||(fh == RAM_HTM) )
  {
  if(file_data_count == 0)
    {
    eof = 0;

    if(fh == SETTINGS_HTM)
      { 
//	  l = strlen(html_settings_head);
//	  if(l <= len) strcpy((char*)buf, html_settings_head); else return(0x8000000);
      }

    if(fh == FIFO_HTM)
      { 
//	  l = strlen(html_fifo_head);
//	  if(l <= len) strcpy((char*)buf, html_fifo_head); else return(0x8000000);
      }

    if(fh == RAM_HTM)
      { 
//	  l = strlen(html_ram_head);
//	  if(l <= len) strcpy((char*)buf, html_ram_head); else return(0x8000000);
      }

    }
  else
    {
	l = 0;
    while(html_buf[phtml_buf])
      {
      buf[l++] = html_buf[phtml_buf++];
      if(l >= len)	return(0);
	  }

    if(eof) return ( (len - l) | 0x80000000 );
	}

  while(1)
    {
    if(fh == SETTINGS_HTM)
      { 
      if(file_data_count > LAST_SETTING)
        {
        eof = 1; 
//	    strcpy(html_buf,html_table_tail);
	    }
	  else
	    {
        read_settings_as_html();
	    }
      }

    if(fh == FIFO_HTM)
      { 
 //     if(file_data_count >= N_clb)//DATA_LENGTH)
	  if(file_data_count >= DATA_LENGTH)
        {
        eof = 1; 
//	    strcpy(html_buf,html_table_tail);
	    }
	  else
	    {
//        Data_Read_Htm_Dev();
	    file_data_count++;
	    }
      }
    if(fh == RAM_HTM)
      { 
      if(file_data_count >= DATA_LENGTH)
        {
        eof = 1; 
//	    strcpy(html_buf,html_table_tail);
	    }
	  else
	    {
//        read_ram_as_html();
	    }
      }

	phtml_buf = 0;

	while(html_buf[phtml_buf])
	  {
	  buf[l++] = html_buf[phtml_buf++];
	  if(l >= len) return(0);
 	  }

    if(eof) return ( (len - l) | 0x80000000 );
    }
  }

//==================================== .........           

return(0x80000000);
}

//------------------------
// Write to data file
//------------------------
int std_file_write(int fh, const U8 *buf, U32 len, int mode) {

U8 * p;
U32  l;

//==================================== settings.bin

if(fh == SETTINGS_BIN)
  {
  p = (U8*)FlashPage;
  for(l = 0; l < len; l++)
    {
    *(p + file_data_count++) = buf[l];
    if(file_data_count > 4*(LAST_SETTING+1)) return (-1);
	}
  flash_changed = 1;
  return(0);
  }

//==================================== ram.bin

if(fh == RAM_BIN)
  {
//  for(l = 0; l < len; l++) wr_ex_ram(RAM_AREA  + file_data_count++ , buf[l]);
//  return(0);
  
  }

///==================================== boot.hex

///if(fh == BOOT_HEX)
///  {
///  for(l = 0; l < len; l++)  wr_ex_ram(RAM_AREA + MAX_BOOT_SIZE+ file_data_count++ , buf[l]); 
///  return(0);
///  }

///==================================== boot.arm

///if(fh == BOOT_ARM)
///  {
///  return(boot_arm_write_flash((U8*)buf, len));
///  }

//==================================== command.txt
/*
if( (fh == COMMAND_TXT) && (file_data_count == 0) )
  {
  file_data_count = 0x80000000;
  for(l = 0; l < len; l++)
    {
	if( (buf[l]== 0) ||	( buf[l]== 13) )
	  {
      process_cmd_start(TFTP_SRC , (char*)buf);
	  return (0);
      }
    }
  }
   */
return (-1);
}

//------------------------
// Close data file
//------------------------
int std_file_close(int fh) {

//if( (fh == SETTINGS_BIN) && (flash_changed) ) { flash_changed = 0;  var_save(); }
if( (fh == SETTINGS_BIN) && (flash_changed) ) { flash_changed = 0;   }
//if(fh == FIFO_BIN)     Data_Close_Dev();
//if(fh == FIFO_HTM)     Data_Close_Dev();
//if(fh == FIFO_BIN)   {IO1CLR |= 0x00010000;  CLEARBIT(flag,TX); Data_Close_Dev();}
//if(fh == BOOT_HEX)	   Boot();
//if(fh == BOOT_ARM)	   Boot_arm();
if(fh == RAM_BIN)	   { DATA_START = RAM_AREA; DATA_LENGTH = file_data_count;  };

return(0);
}

//================================== TEST RTL
/*
void RTL_test(void) {

U8 buf[512];
U32 len;

fo = fopen ("ram.bin","w");

len = fwrite (buf, 1, 512, fo);

fclose (fo);

}
*/
