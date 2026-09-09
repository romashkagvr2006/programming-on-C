/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2007                         */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.C:  Flash Programming Functions adapted                   */
/*               for Philips LPC2xxx 256kB Flash                       */
/*               using Flash Boot Loader with IAP                      */
/*                                                                     */
/***********************************************************************/

#include <LPC22XX.H>
#include <stdio.h>
//#include "..\INC\File_Config.h"
#include "..\APP\EXTERNALS.h"
#include <File_Config.h>

struct sIAP {                  // IAP Structure
  U32 cmd;                     // Command
  U32 par[4];                  // Parameters
  U32 stat;                    // Status
} IAP;


/*
IAP Execute
Parameter:      pIAP:  Pointer to IAP
Return Value:   None (stat in IAP)
*/

#ifdef USE_SIMULATOR
void erase_sector(U32 n) {

U32 adr;
U32 i;
U32 sz;

if(n < 8) { sz = 8192;  adr = n << 13; return; }
else
  {
  if(n < 10) { sz = 65536; adr = (n - 7) << 16; return; }
  else       { sz = 8192;  adr = ((n - 10) << 13) + 0x00030000;  }
  } 

for(i = 0; i < sz; i++) *(U8*)(adr + i + 0x80000000) = 0xFF;

}

void _IAP_Execute (struct sIAP *pIAP) {
U8 * adr;
U8 * padr;
U32 n;

IAP.stat = 0;                                // Command OK

if(IAP.cmd == 50) return;                    // Prepare Sector

if(IAP.cmd == 51)                            // Copy RAM to Flash
  {
  padr = (U8*)(IAP.par[0] | 0x80000000);     // Destination Flash Address
  adr  = (U8*) IAP.par[1];                   // Source RAM Address
  for(n = 0; n < IAP.par[2]; n++) padr[n] = adr[n];
  return;
  }

if(IAP.cmd == 52)                            // Erase Sector
  {
  for(n = IAP.par[0]; n <= IAP.par[1]; n++) erase_sector(n);
  return;
  }
}

#else

void IAP_Execute (struct sIAP *pIAP);

void _IAP_Execute (struct sIAP *pIAP) {

PLLCON &= ~2; // Disconnect PLL
IAP_Execute (pIAP);
PLLCON |=  2; // Connect PLL

}

#endif

/*
 * Get Sector Number
 *    Parameter:      adr:  Sector Address
 *    Return Value:   Sector Number
 */

U32 GetSecNum (U32 adr) {
  U32 n;

  n = (adr >> 13) & 0x1F;                      // Pseudo Sector Number
  if (n >= 24) {                               // High Small 8kB Sectors
    n -= 14;
  }
  else if (n >= 8) {                           // Large 64kB Sectors
    n  = 8 + (n >> 4);
  }

  return (n);                                  // Sector Number
}

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

int fs_EraseSector (U32 adr) {
  U32 n;

  n = GetSecNum(adr);                          // Get Sector Number

  IAP.cmd    = 50;                             // Prepare Sector for Erase
  IAP.par[0] = n;                              // Start Sector
  IAP.par[1] = n;                              // End Sector
  _IAP_Execute (&IAP);                         // Execute IAP Command
  if (IAP.stat) return (1);                    // Command Failed

  IAP.cmd    = 52;                             // Erase Sector
  IAP.par[0] = n;                              // Start Sector
  IAP.par[1] = n;                              // End Sector
  IAP.par[2] = SYSCLK/1000/4;                  // CCLK in kHz
  _IAP_Execute (&IAP);                         // Execute IAP Command
  if (IAP.stat) return (1);                    // Command Failed

  return (0);                                  // Finished without Errors
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

int fs_ProgramPage (U32 adr, U32 sz, U8 * buf) {

  U32 padr, ofs, cnt, n;

  IAP.cmd    = 50;                             // Prepare Sector for Write
  IAP.par[0] = GetSecNum(adr);                 // Start Sector
  IAP.par[1] = GetSecNum(adr + sz - 1);        // End Sector
  _IAP_Execute (&IAP);                         // Execute IAP Command
  if (IAP.stat) return (1);                    // Command Failed

  while (sz) {                                 // Go through all Data
    padr = adr & ~(PAGE_SZ - 1);               // Page Address
    ofs  = adr - padr;                         // Data Offset
    cnt  = PAGE_SZ - ofs;                      // Data Count
    if (cnt > sz) cnt = sz;                    // Adjust Data Count
    if (cnt != PAGE_SZ) {                      // Incomplete Page being written
      for (n = 0; n < PAGE_SZ/4; n++) {        // Go through complete Page
        FlashPage[n] = *((U32 *)padr + n);          // Read Page Data from Flash
      }
    }
    for (n = 0; n < cnt; n++) {                // Go through Page Data
      *((U8 *)FlashPage + ofs++) = *buf++;     // Copy & Align to Page Buffer
    }

    IAP.cmd    = 51;                           // Copy RAM to Flash
    IAP.par[0] = padr;                         // Destination Flash Address
    IAP.par[1] = (U32)FlashPage;               // Source RAM Address
    IAP.par[2] = PAGE_SZ;                      // Page Size
    IAP.par[3] = SYSCLK/1000/4;                // CCLK in kHz

    _IAP_Execute (&IAP);                       // Execute IAP Command
    if (IAP.stat) return (1);                  // Command Failed

    adr += cnt;                                // Next Address
    sz  -= cnt;                                // Next Size
  }

  return (0);                                  // Finished without Errors

}
