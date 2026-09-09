/*----------------------------------------------------------------------------
 *      R T L  -  T C P N E T
 *----------------------------------------------------------------------------
 *      Name:    TFTP_UIF.C
 *      Purpose: TFTP Server User Interface Module
 *      Rev.:    V3.10 / 14-jun-2007
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2007 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include "..\INC\Net_Config.h"
#include "..\APP\EXTERNALS.h"
#include "..\APP\DEFINITION.h"

/*----------------------------------------------------------------------------
 * Telnet File Access CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- tftp_fopen ------------------------------------*/

void *tftp_fopen (U8 *fname, U8 *mode) {
   /* Open filename fname for reading or writing. */
   return (fopen((const S8 *)fname, (const S8 *)mode));
}


/*--------------------------- tftp_fopen ------------------------------------*/

void tftp_fclose (void *file) {
   /* Close the file, opened for reading or writing. This function is */
   /* called, when the TFTP Session is closing.                       */
   fclose ((FILE *)file);
}


/*--------------------------- tftp_read -------------------------------------*/

U16 tftp_fread (void *file, U32 fpos, U8 *buf) {
   /* Read file data to sending buffer. Max. data length is 512 bytes. */
   /* Return number of bytes copied to buffer.                         */
   
   if (fpos != ftell (file)) {
      /* Rewind file position pointer back for 512 bytes. */
      fseek ((FILE *)file, fpos, SEEK_SET);
   }
   return (fread (buf, 1, 512, (FILE *)file));
}


/*--------------------------- tftp_read -------------------------------------*/

U16 tftp_fwrite (void *file, U8 *buf, U16 len) {
   /* Write data to file. Return number of bytes actually written. When */
   /* returned number of bytes 'len' is less than 512, TFTP connection  */
   /* will be closed.                                                   */
   
   fwrite (buf, 1, len, (FILE *)file);
   fflush((FILE *)file);
   if(file_data_count == 0x80000000) return(1); else return (512);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
