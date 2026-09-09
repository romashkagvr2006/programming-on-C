/*----------------------------------------------------------------------------
 *      R T L  -  T C P N E T
 *----------------------------------------------------------------------------
 *      Name:    HTTP_UIF.C
 *      Purpose: HTTP Server User Interface Module
 *      Rev.:    V3.22
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2008 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include "Net_Config.h"

// Conditional compilation - only compile if HTTP is enabled
#if HTTP_ENABLE

/*----------------------------------------------------------------------------
 * HTTP Server File Access CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- http_fopen ------------------------------------*/

void *http_fopen (U8 *fname) {
   /* Open file 'fname' for reading. Return file handle. */
   return (fopen ((const char *)fname, "r"));
}


/*--------------------------- http_fclose -----------------------------------*/

void http_fclose (void *f) {
   /* Close the file opened for reading. */
   fclose (f);
}

/*--------------------------- http_fread ------------------------------------*/

U16 http_fread (void *f, U8 *buf, U16 len) {
   /* Read 'len' bytes from file to buffer 'buf'. The file will be closed, */
   /* when the number of read bytes is less than 'len'. */
   return (fread (buf, 1, len, f));
}


/*--------------------------- http_fgets ------------------------------------*/

BOOL http_fgets (void *f, U8 *buf, U16 size) {
   /* Read a string from file to buffer 'buf'. The file will be closed, */
   /* when this function returns __FALSE. */
   if (fgets ((char *)buf, size, f) == NULL) {
      return (__FALSE);
   }
   return (__TRUE);
}

#endif

 /*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
