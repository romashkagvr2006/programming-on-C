
                AREA    IAPEXE, CODE, READONLY
                ARM

IAP_ENTRY      EQU     0x7FFFFFF1

;IAP_ENTRY       EQU     IAP_DEBUG
SYSCLK			EQU		4*14745600

                EXPORT  BOOT_Execute

BOOT_Execute    LDR     R0, Addr_Prep_Erase_16 ; R0 = &IAP.cmd,
                LDR     R1, Status_Addr        ; R1 = &Status,
                ADR     LR, BOOT_Exit1         ; Return Address
                LDR     R2,=IAP_ENTRY          ; IAP Entry (Thumb Mode)
                BX      R2                     ; Execute IAP Command

BOOT_Exit1      LDR     R0, Addr_Erase_16      ; R0 = &IAP.cmd,
                LDR     R1, Status_Addr        ; R1 = &Status,
                ADR     LR, BOOT_Exit2         ; Return Address
                LDR     R2,=IAP_ENTRY          ; IAP Entry (Thumb Mode)
                BX      R2                     ; Execute IAP Command

BOOT_Exit2      B       BOOT_Exit2

;----------------------------------------------	Address	table

Addr_Prep_Erase_16	DCD      Prep_Erase_16
Addr_Erase_16	    DCD      Erase_16

;----------------------------------------------	Prepare Sector 16 for Erase	
Prep_Erase_16	    DCD      50				    
				    DCD      16				    ; Start Sector
				    DCD      16				    ; End Sector
;----------------------------------------------	Erase 16	
Erase_16	        DCD      52	
				    DCD      16				    ; Start Sector
				    DCD      16				    ; End Sector
				    DCD      SYSCLK/1000/4      ; CCLK in kHz
;----------------------------------------------	Last of 256 kb	
Status_Addr	        DCD      0x813FFFFC 	    ; Status

IAP_DEBUG		BX		 LR

;----------------------------------------------	End of asm code
SIGNATURE       DCD      0x33333333
                END
