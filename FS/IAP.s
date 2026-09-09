;/***********************************************************************/
;/*  This file is part of the ARM Toolchain package                     */
;/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2006                         */
;/***********************************************************************/
;/*                                                                     */
;/*  IAP.S:  IAP Execution Function                                     */
;/*                                                                     */
;/***********************************************************************/


                AREA    IAPEXE, CODE, READONLY
                ARM

;void IAP_Execute (struct sIAP *pIAP);
                EXPORT  IAP_Execute

IAP_Execute     STMFD   SP!,{LR}               ; Save Return Address
                ADD     R1,R0,#0x14            ; R0 = &IAP.cmd, R1 = &IAP.stat
                ADR     LR,IAP_Exit            ; Return Address
                LDR     R2,=0x7FFFFFF1         ; IAP Entry (Thumb Mode)
                BX      R2                     ; Execute IAP Command

IAP_Exit        LDMFD   SP!,{LR}               ; Restore Return Address
                BX      LR                     ; Return


                END
