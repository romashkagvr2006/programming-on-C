/*----------------------------------------------------------------------------
 *      R T L  -  T C P N E T
 *----------------------------------------------------------------------------
 *      Name:    TELNET_UIF.C
 *      Purpose: Telnet Server User Interface Module
 *      Rev.:    V3.10 / 14-jun-2007
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2007 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "..\INC\Net_Config.h"
#include <string.h>
#include <stdio.h>
#include "..\APP\EXTERNALS.h"
#include "..\APP\DEFINITION.h"

/* Net_Config.c */
extern struct   tcp_info tcp_socket[];
extern U8 const tcp_NumSocks;
extern U8 const tnet_EnAuth;
extern U8       tnet_auth_passw[20];

/* ANSI ESC Sequences for terminal control. */
#define CLS     "\033[2J"
#define TBLUE   "\033[37;44m"
#define TNORM   "\033[0m"

/* My structure of data overlaid in 'cmd' buffer. */
typedef struct {
   U16 id;
   U16 nmax;
   U16 idx;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)&p[0])

/* Local variables */
static U8 const tnet_header[] = {
   CLS "\r\n"
   "        " TBLUE
   "*=============================================================*\r\n" TNORM
   "        " TBLUE
   "*                 Embedded Telnet Server                      *\r\n" TNORM
   "        " TBLUE
   "*=============================================================*\r\n" TNORM
   };
static U8 const tnet_help1[] = {
   "\r\n\r\n"
   "    Available Commands:\r\n"
   "    ----------------------------\r\n"
   "    tcpstat          - display a tcp status\r\n"
   "    rinfo            - display remote machine info\r\n"};
static U8 const tnet_help2[] = {
   "    passw [new]      - change system password\r\n"
   "    passwd           - display current password\r\n"};
static U8 const tnet_help3[] = {
   "    help             - display this help\r\n"
   "    ?                - display this help\r\n"
   "    bye              - disconnect\r\n"
   "    <ESC>            - disconnect\r\n"
   "    <CTRL^C>         - disconnect\r\n"
   "    <BS>             - delete Character left\r\n"};

static U8 const tcp_stat[] = {
   CLS "\r\n"
   "     " TBLUE
   "=============================================================\r\n" TNORM
   "     " TBLUE
   " Socket   State       Rem_IP       Rem_Port  Loc_Port  Timer \r\n" TNORM
   "     " TBLUE
   "=============================================================\r\n" TNORM
   };

static char const state[][11] = {
   "FREE",
   "CLOSED",
   "LISTEN",
   "SYN_REC",
   "SYN_SENT",
   "FINW1",
   "FINW2",
   "CLOSING",
   "LAST_ACK",
   "TWAIT",
   "CONNECT"};

/*----------------------------------------------------------------------------
 *      Telnet CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- tnet_cbfunc -----------------------------------*/

U16 tnet_cbfunc (U8 code, U8 *buf, U16 buflen) {
   /* This function is called by the Telnet Client to get formated system    */
   /* messages for different code values.                                    */
   /* Values for 'code':                                                     */
   /*    0 - initial header                                                  */
   /*    1 - prompt string                                                   */
   /*    2 - header for login only if authorization is enabled               */
   /*    3 - string 'Username' for login                                     */
   /*    4 - string 'Password' for login                                     */
   /*    5 - message 'Login incorrect'                                       */
   /*    6 - message 'Login timeout'                                         */
   U16 len = 0;

   /* Make a reference to disable compiler warning. */
   buflen = buflen;

   switch (code) {
      case 0:
         /* Write initial header after login. */
         len = str_copy (buf, (U8 *)&tnet_header);
         break;
      case 1:
         /* Write a prompt string. */
         len  = str_copy (buf, "\r\n");
         len += str_copy (buf + len, dev_name);
         len += str_copy (buf + len, ">");
         break;				   
      case 2:
         /* Write Login header. */
         len = str_copy (buf, CLS "\r\nEmbedded Telnet Server,"
                                  " please login...\r\n");
         break;
      case 3:
         /* Write 'username' prompt. */
         len = str_copy (buf, "\r\nUsername: ");
         break;
      case 4:
         /* Write 'Password' prompt. */
         len = str_copy (buf, "\r\nPassword: ");
         break;
      case 5:
         /* Write 'Login incorrect'.message. */
         len = str_copy (buf, "\r\nLogin incorrect");
         break;
      case 6:
         /* Write 'Login Timeout' message. */
         len = str_copy (buf, "\r\nLogin timed out after 60 seconds.\r\n");
         break;
   }
   return (len);
}


/*--------------------------- tnet_process_cmd ------------------------------*/

U16 tnet_process_cmd (U8 *cmd, U8 *buf, U16 buflen, U16 xcnt) {
   /* This is a Telnet Client callback function to make a formatted output   */
   /* for 'stdout'. It returns the number of bytes written to the out buffer.*/
   /* Hi-bit of return value (len is or-ed with 0x8000) is a disconnect flag.*/
   /* Bit 14 (len is or-ed with 0x4000) is a repeat flag for the Tnet client.*/
   /* If this bit is set to 1, the system will call the 'tnet_process_cmd()' */
   /* again with parameter 'xcnt' incremented by 1. This function should     */
   /* NEVER write more than 'buflen' bytes to the buffer.                    */
   /* Parameters:                                                            */
   /*   cmd    - telnet received command string                              */
   /*   buf    - Telnet transmit buffer                                      */
   /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
   /*   xcnt   - exec. counter used for repeated loops                       */
   /*            (on 1st call = 0, 2nd call = 1, ...                         */
   TCP_INFO *tsoc;
   U16 len;
   REMOTEM rm;
   U8  c;

   /* On first call to this function, the value of 'xcnt' is 0 */
   if (xcnt != 0) {
      len = 0;
      /* This is a repeated call to this function. */
      switch (MYBUF(cmd)->id) {
         // Log_txt display
         case 1:
         if(command_complete)
           {
           buf[len++] = '\r'; buf[len++] = '\n';
		   pLog_txt = 0;
		   while(1)
		   	  {
		      c = get_log_char();
			  if(c == 0) break;
			  buf[len++] = c;
			  if(len >= buflen - 2) break;
			  }
   	       }
		 return (len);

         case 2:
            /* TCP status display. */
            while (len < buflen-80) {
               /* Let's use as much of the buffer as possible. */
               /* This will produce less packets and speedup the transfer. */
               if (MYBUF(cmd)->idx == 0) {
                  len += str_copy (buf, (U8 *)tcp_stat);
               }
               tsoc = &tcp_socket[MYBUF(cmd)->idx];
               len += sprintf    ((S8 *)(buf+len), "\r\n%9d %10s  ", MYBUF(cmd)->idx, 
                                  state[tsoc->State]);
               if (tsoc->State <= TCP_STATE_CLOSED) {
                  len += sprintf ((S8 *)(buf+len),
                                  "        -             -         -       -\r\n");
               }
               else if (tsoc->State == TCP_STATE_LISTEN) {
                  len += sprintf ((S8 *)(buf+len),
                                  "        -             -     %5d       -\r\n",
                                  tsoc->LocPort);
               }
               else {
                  /* First temporary print for alignment. */
                  sprintf ((S8 *)(buf+len+16),"%d.%d.%d.%d",tsoc->RemIpAdr[0],
                           tsoc->RemIpAdr[1],tsoc->RemIpAdr[2],tsoc->RemIpAdr[3]);
                  len += sprintf ((S8 *)(buf+len),"%15s    %5d    %5d     %4d\r\n",
                                  buf+len+16,tsoc->RemPort,tsoc->LocPort,tsoc->AliveTimer);
               }
               if (++MYBUF(cmd)->idx >= tcp_NumSocks) {
                  /* OK, we are done, reset the index counter for next callback. */
                  MYBUF(cmd)->idx = 0;
                  /* Setup a callback delay. This function will be called again after    */
                  /* delay has expired. It is set to 20 system ticks 20 * 100ms = 2 sec. */
                  tnet_set_delay (20);
                  break;
               }
            }
            /* Request a repeated call, bit 14 is a repeat flag. */
            len |= 0x4000;
      }
      return (len);
   }

   /* Simple Command line parser */

   len = strlen ((const S8 *)cmd);

   if (tnet_ccmp (cmd, "BYE") == __TRUE) {
      /* 'BYE' command, send message and disconnect */
      len = str_copy (buf, "\r\nDisconnect...\r\n");
      /* Hi bit of return value is a disconnect flag */
      return (len | 0x8000);
   }

   if (tnet_ccmp (cmd, "PASSW") == __TRUE && tnet_EnAuth) {
      /* Change the system password. */
      if (len == 5) {
         /* Disable password. */
         tnet_auth_passw[0] = 0;
      }
      else {
         mem_copy (&tnet_auth_passw, &cmd[6], 20);
      }
      len = sprintf ((S8 *)buf, "\r\n OK, New Password: \"%s\"",tnet_auth_passw);
      return (len);
   }

   if (tnet_ccmp (cmd, "PASSWD") == __TRUE && tnet_EnAuth) {
      /* Only display the current system password. */
      len = sprintf ((S8 *)buf, "\r\n System Password: \"%s\"",tnet_auth_passw);
      return (len);
   }

   if (tnet_ccmp (cmd, "TCPSTAT") == __TRUE) {
      /* Display a TCP status similar to that in HTTP_Demo example. */
      len = str_copy (buf, CLS);
      MYBUF(cmd)->id  = 2;
      MYBUF(cmd)->idx = 0;
      return (len | 0x4000);
   }

   if (tnet_ccmp (cmd, "RINFO") == __TRUE) {
      /* Display Remote Machine IP and MAC address. */
      tnet_get_info (&rm);
      len  = sprintf ((S8 *)buf,"\r\n Remote IP : %d.%d.%d.%d",
                      rm.IpAdr[0],rm.IpAdr[1],rm.IpAdr[2],rm.IpAdr[3]);
      len += sprintf ((S8 *)(buf+len),
                      "\r\n Remote MAC: %02X-%02X-%02X-%02X-%02X-%02X",
                      rm.HwAdr[0],rm.HwAdr[1],rm.HwAdr[2],
                      rm.HwAdr[3],rm.HwAdr[4],rm.HwAdr[5]);
      return (len);
   }

   if (tnet_ccmp (cmd, "HELP") == __TRUE || tnet_ccmp (cmd, "?") == __TRUE) {
      /* 'HELP' command, display help text */
      len = str_copy (buf,(U8 *)tnet_help1);
      if (tnet_EnAuth) {
         len += str_copy (buf+len,(U8 *)tnet_help2);
      }
      len += str_copy (buf+len,(U8 *)tnet_help3);
      return (len);
   }

   process_cmd_start(TELNET_SRC , (char*)cmd);

   len = 0; buf[len++] = '\r'; buf[len++] = '\n';
   MYBUF(cmd)->id  = 1;
   MYBUF(cmd)->idx = 0;
   return (len | 0x4000);

}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
