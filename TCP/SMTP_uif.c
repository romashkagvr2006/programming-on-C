/*----------------------------------------------------------------------------
 *      R T L  -  T C P N E T
 *----------------------------------------------------------------------------
 *      Name:    SMTP_UIF.C
 *      Purpose: SMTP Client User Interface Module
 *      Rev.:    V3.10 / 14-jun-2007
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2007 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "..\INC\Net_Config.h"
#include <string.h>
#include <stdio.h>

/* Local variables */
static char const msghead[] = {
   "Hello!\r\n\r\n"
   "This is measurement report sent from embedded system\r\n"
   "running on Keil MCB167-NET evaluation board.\r\n"
   "Measurements are taken from analog inputs AIN0 - AIN7\r\n\r\n"
   "--------------------------------------------------------------\r\n"
};

static char const msgfoot[] = {
   "--------------------------------------------------------------\r\n"
   "The end of measurements.\r\n\r\n"
   "Bye..."
};

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/

U16 AD_in (U32 ch) { return(1234); };

/*----------------------------------------------------------------------------
 *      SMTP CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- smtp_cbfunc -----------------------------------*/

U16 smtp_cbfunc (U8 code, U8 *buf, U16 buflen, U16 xcnt) {
   /* This function is called by the SMTP client to get email parameters and */
   /* data. It returns the number of bytes written to the output buffer.     */
   /* Hi-bit of return value (len is or-ed with 0x8000) is a repeat flag for */
   /* the system. If this bit is set to 1, the system will call this function*/
   /* again with parameter 'xcnt' incremented by 1. This function should     */
   /* NEVER write more than 'buflen' bytes to the buffer.                    */
   /* Parameters:                                                            */
   /*   code   - function code with following values:                        */
   /*             0 - 'From   : ' - get email address of the sender          */
   /*             1 - 'To     : ' - get email address of recipient           */
   /*             2 - 'Subject: ' - get subject of email                     */
   /*             3 - 'Data   : ' - get email data in plain ascii format     */
   /*   buf     - SMTP transmit buffer                                       */
   /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
   /*   xcnt   - script exec. counter used for repeated loops                */
   /*            (on 1st call = 0, 2nd call = 1, ...                         */
   U32 i,len = 0;
   static U16 idx;

   switch (code) {
      case 0:
         /* Enter email address of the sender. */
         len = str_copy (buf, "mcb@keil.com");
         break;

      case 1:
         /* Enter email address of the recipient. */
         len = str_copy (buf, "somebody@keil.com");
         break;

      case 2:
         /* Enter email subject. */
         len = str_copy (buf, "Reported measurements");
         break;

      case 3:
         /* Enter email data. */
         if (xcnt == 0) {
            /* First call, enter an email header text. */
            len = str_copy (buf, (U8 *)msghead);
            idx = 1;
            goto rep;
         }
         if (idx == 0) {
            /* Last one, add a footer text to this email. */
            len = str_copy (buf, (U8 *)msgfoot);
            break;
         }
         for (len = 0; len < buflen-150;  ) {
            /* Let's use as much of the buffer as possible. */
            /* This will produce less packets and speedup the transfer. */
            len += sprintf ((S8 *)(buf+len), "%d. ",idx);
            for (i = 0; i < 8; i++) {
               len += sprintf ((S8 *)(buf+len), "AD%d= %d  ",i,AD_in(i));
            }
            len += str_copy (buf+len, "\r\n");
            if (++idx > 500) {
               idx = 0;
               break;
            }
         }
         /* Request a repeated call, bit 15 is a repeat flag. */
rep:     len |= 0x8000;
         break;
   }
   return ((U16)len);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
