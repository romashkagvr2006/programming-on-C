/*----------------------------------------------------------------------------
 *      R T L  -  T C P N E T
 *----------------------------------------------------------------------------
 *      Name:    NET_DEBUG.C
 *      Purpose: Debug Module
 *      Rev.:    V3.10 / 14-jun-2007
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2007 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "..\INC\Net_Config.h"
#include <stdarg.h>
#include <stdio.h>

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

// <e>TcpNet Debug Definitions
// ===========================
#define DBG_ENABLE     1

//   <o>Memory Management Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Dynamic Memory debug messages
#define DBG_MEM        1

//   <o>Ethernet Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Ethernet debug messages
#define DBG_ETH        1

//   <o>PPP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off PPP debug messages
#define DBG_PPP        0

//   <o>SLIP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off SLIP debug messages
#define DBG_SLIP       0

//   <o>ARP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off ARP debug messages
#define DBG_ARP        1

//   <o>IP Debug    <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off IP debug messages
#define DBG_IP         1

//   <o>ICMP Debug  <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off ICMP debug messages
#define DBG_ICMP       1

//   <o>UDP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off UDP debug messages
#define DBG_UDP        1

//   <o>TCP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off TCP debug messages
#define DBG_TCP        1

//   <o>NBNS Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off NetBIOS Name Service debug messages
#define DBG_NBNS       1

//   <o>DHCP Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Dynamic Host Configuration debug messages
#define DBG_DHCP       1

//   <o>DNS Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Domain Name Service debug messages
#define DBG_DNS        1

//   <o>Application Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Application debug messages
//   <I> for: HTTP, TFTP, SMTP, Telnet
#define DBG_APP        1

// </e>

//------------- <<< end of configuration section >>> -----------------------


#if DBG_ENABLE == 1

const int __tcpnet__debug__ = 1;

/*--------------------------- init_debug ------------------------------------*/

void init_debug (void) {
   /* Add your code to initialize the Debug output. This is usually the  */
   /* serial interface. The function is called at TcpNet system startup. */
   /* You may need to customize also the 'putchar()' function.           */

}


/*--------------------------- __debug__ -------------------------------------*/

void __debug__ (U32 proc, const char *fmt, ...) {
   /* This function is called to output TcpNet Debug messages. */
   va_list args;

   switch (proc) {
      case MEM:
         /* Memory Management Debug Messages */
#if DBG_MEM > 1
         printf ("MEM: ");
         break;
#else
         return;
#endif

      case ETH:
         /* Ethernet Debug Messages */
#if DBG_ETH > 1
         printf ("ETH: ");
         break;
#else
         return;
#endif

      case PPP:
         /* PPP Link Debug Messages */
#if DBG_PPP > 1
         printf ("PPP: ");
         break;
#else
         return;
#endif

      case SLIP:
         /* SLIP Link Debug Messages */
#if DBG_SLIP > 1
         printf ("SLIP:");
         break;
#else
         return;
#endif

      case ARP:
         /* ARP Debug Messages */
#if DBG_ARP > 1
         printf ("ARP: ");
         break;
#else
         return;
#endif

      case IP:
         /* IP Debug Messages */
#if DBG_IP > 1
         printf ("IP : ");
         break;
#else
         return;
#endif

      case ICMP:
         /* ICMP Debug Messages */
#if DBG_ICMP > 1
         printf ("ICMP:");
         break;
#else
         return;
#endif

      case UDP:
         /* UDP Debug Messages */
#if DBG_UDP > 1
         printf ("UDP: ");
         break;
#else
         return;
#endif

      case TCP:
         /* TCP Debug Messages */
#if DBG_TCP > 1
         printf ("TCP: ");
         break;
#else
         return;
#endif

      case NBNS:
         /* NBNS Debug Messages */
#if DBG_NBNS > 1
         printf ("NBNS:");
         break;
#else
         return;
#endif

      case DHCP:
         /* DHCP Debug Messages */
#if DBG_DHCP > 1
         printf ("DHCP:");
         break;
#else
         return;
#endif

      case DNS:
         /* DNS Debug Messages */
#if DBG_DNS > 1
         printf ("DNS: ");
         break;
#else
         return;
#endif

      case APP:
         /* TcpNet Application Debug Messages */
#if DBG_APP > 1
         break;
#else
         return;
#endif

   }
   va_start (args,fmt);
   vprintf (fmt,args);
   va_end (args);
}


/*--------------------------- __error__ -------------------------------------*/

void __error__ (U32 proc, const char *fmt, ...) {
   /* This function is called to output TcpNet Error messages. */
   va_list args;

   switch (proc) {
      case MEM:
         /* Memory Management Error Messages */
#if DBG_MEM > 0
         printf ("MEM ERR: ");
         break;
#else
         return;
#endif

      case ETH:
         /* Ethernet Error Messages */
#if DBG_ETH > 0
         printf ("ETH ERR: ");
         break;
#else
         return;
#endif

      case PPP:
         /* PPP Link Debug Messages */
#if DBG_PPP > 0
         printf ("PPP ERR: ");
         break;
#else
         return;
#endif

      case SLIP:
         /* SLIP Link Debug Messages */
#if DBG_SLIP > 0
         printf ("SLIP ERR:");
         break;
#else
         return;
#endif

      case ARP:
         /* ARP Error Messages */
#if DBG_ARP > 0
         printf ("ARP ERR: ");
         break;
#else
         return;
#endif

      case IP:
         /* IP Error Messages */
#if DBG_IP > 0
         printf ("IP ERR: ");
         break;
#else
         return;
#endif

      case ICMP:
         /* ICMP Error Messages */
#if DBG_ICMP > 0
         printf ("ICMP ERR:");
         break;
#else
         return;
#endif

      case UDP:
         /* UDP Error Messages */
#if DBG_UDP > 0
         printf ("UDP ERR: ");
         break;
#else
         return;
#endif

      case TCP:
         /* TCP Error Messages */
#if DBG_TCP > 0
         printf ("TCP ERR: ");
         break;
#else
         return;
#endif

      case NBNS:
         /* NBNS Error Messages */
#if DBG_NBNS > 0
         printf ("NBNS ERR:");
         break;
#else
         return;
#endif

      case DHCP:
         /* DHCP Error Messages */
#if DBG_DHCP > 0
         printf ("DHCP ERR:");
         break;
#else
         return;
#endif

      case DNS:
         /* DNS Error Messages */
#if DBG_DNS > 0
         printf ("DNS ERR: ");
         break;
#else
         return;
#endif

      case APP:
         /* TcpNet Application Error Messages */
#if DBG_APP > 0
         break;
#else
         return;
#endif
   }
   va_start (args,fmt);
   vprintf (fmt,args);
   va_end (args);
}


#endif

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/


