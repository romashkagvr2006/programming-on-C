/*----------------------------------------------------------------------------
 *      R T L  -  T C P N E T
 *----------------------------------------------------------------------------
 *      Name:    HTTP_ERR.C
 *      Purpose: HTTP Server Error Page Definitions
 *      Rev.:    V3.10 / 14-jun-2007
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2007 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "RTL.h"

// Conditional compilation - only compile if HTTP is enabled
#if HTTP_ENABLE

/* Note: Keep HTTP Error pages small sized. */

/* HTTP Error 404 - File not Found */
const char http_err_404[] = {
        "<head><title>Keil Embedded WEB Server</title></head>"
        "<body>"
        "<h2>HTTP 1.0 404 Error. File Not Found</h2>"
        "The requested URL was not found on this server."
        "<hr><br>"
        "<i>Keil Embedded WEB Server V2.00, 2007<br>"
        "<a href=http://www.keil.com> www.keil.com</a>"
        " - Embedded Development Tools</i>"
        "</body>"};

/* HTTP Error 401 - Unauthorized access. */
const char http_err_401[] = {
        "<head><title>Keil Embedded WEB Server</title></head>"
        "<body>"
        "<h2>HTTP 1.0 401 Error. Unauthorized Access</h2>"
        "You are not authorized to access this server."
        "<hr><br>"
        "<i>Keil Embedded WEB Server V2.00, 2007<br>"
        "<a href=http://www.keil.com> www.keil.com</a>"
        " - Embedded Development Tools</i>"
        "</body>"};

/* Page size definitions. */
const U32 sizeof_http_err_404 = sizeof (http_err_404);
const U32 sizeof_http_err_401 = sizeof (http_err_401);


#endif

 /*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
