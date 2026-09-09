
//-----------------------------------------------------------------------------
// Definitions for Davicom DM9000
//-----------------------------------------------------------------------------

#define DM9000_NCR		0x00	// Network Control Reg
#define DM9000_NSR		0x01	// Network Status Reg
#define DM9000_TCR		0x02	// TX Control Reg
#define DM9000_TSR1		0x03	// TX Status Reg1
#define DM9000_TSR2		0x04	// TX Status Reg2
#define DM9000_RXCR		0x05	// RX Control Reg
#define DM9000_RXSR		0x06	// RX Status Reg
#define DM9000_ROCR		0x07	// RX Overflow Count Reg
#define DM9000_BPTR		0x08	// Back Pressure Threshold Reg
#define DM9000_FCTR		0x09	// Flow Control Threshold Reg
#define DM9000_FCR		0x0a	// RX Flow Control Reg
#define DM9000_EPCR		0x0b	// EEPROM & PHY Control Reg
#define DM9000_EPAR		0x0c	// EEPROM & PHY Address Reg
#define DM9000_EPDRL	0x0d	// EEPROM & PHY Data Byte Low
#define DM9000_EPDRH	0x0e	// EEPROM & PHY Data Byte High
#define DM9000_WCR		0x0f	// Wakeup Control Reg
#define DM9000_MAC_REG	0x10	// Contains our MAC regs up To 0x15
#define DM9000_MLC_REG	0x16	// Contains our Multicast regs up To 0x1d
#define DM9000_GPCR		0x1e	// General purpose control register GPUI-Control Bit 0: In, 1: OUT
#define DM9000_GPR		0x1f	// General purpose register GPIO-Register, Bit0: Phy-Power, Bit 1,2,3: GPIO
#define DM9000_TRPAL	0x22	// TX SRAM Read Pointer Address Low Byte
#define DM9000_TRPAH	0x23	// TX SRAM Read Pointer Address High Byte
#define DM9000_RWPAL	0x24	// RX SRAM Write Pointer Address Low Byte
#define DM9000_RWPAH	0x25	// RX SRAM Write Pointer Address High Byte
#define DM9000_VID		0x28	// Must be 0x0A46 for Davicom (Little Endian!)
#define DM9000_PID		0x2a	// Must be 0x9000 for DM9000 (Little Endian!)
#define DM9000_CHIPR	0x2c	// DM9000 chip revision
#define DM9000_SMCR		0x2f	// Special Mode Control register
#define DM9000_MRCMDX	0xf0	// Memory Data Read Command without address increment
#define DM9000_MRCMD	0xf2	// Memory Data Read Command with address increment
#define DM9000_MRRL		0xf4	// Memory Data Read_address Reg Low Byte
#define DM9000_MRRH		0xf5	// Memory Data Read_address Reg High Byte
#define DM9000_MWCMDX	0xf6	// Memory Data Write Command without address increment
#define DM9000_MWCMD	0xf8	// Memory Data Write Command with address increment
#define DM9000_MWRL		0xfa	// Memory Data Write_address Reg Low Byte
#define DM9000_MWRH		0xfb	// Memory Data Write_address Reg High Byte
#define DM9000_TXPLL	0xfc	// TX Packet length Low byte
#define DM9000_TXPLH	0xfd	// TX Packet length High byte
#define DM9000_ISR		0xfe	// Interrupt status Reg.
#define DM9000_IMR		0xff	// Interrupt mask Reg.

#define DM9000_EEPROM			0x00	// EEPROM Control Select
#define DM9000_autoload_addr	0x03
#define DM9000_VendID_addr		0x04
#define DM9000_ProdID_addr		0x05
#define DM9000_pinctrl_addr		0x06
#define DM9000_wakeup_addr		0x07

#define DM9000_Def_autoload	0x1455	// Autoload Control for LED mode only
#define DM9000_VendID		0x0A46
#define DM9000_ProdID		0x9000
#define DM9000_Def_pinctrl	0x01E6	// Pin Control Configuration
#define DM9000_Def_wakeup	0x0180	// Wakeup configuration/LED mode/PHY Enable

#define DM9000_PHY		0x40	// PHY Control select
#define DM9000_BMCR		0x00	// PHY Control Reg. Addr.
#define DM9000_BMSR		0x01	// PHY Status Reg. Addr.
#define DM9000_PHYID1	0x02	// PHYID1 Reg. Addr.
#define DM9000_PHYID2	0x03	// PHYID2 Reg. Addr.
#define DM9000_ANAR		0x04	// Auto-Negotiation Advertisment Reg. Addr.
#define DM9000_ANLPAR	0x05	// Auto-Negotiation Link Partner Ability Reg. Addr.
#define DM9000_ANER		0x06	// PHY Auto Negotiation Expansion Reg. Addr.
#define DM9000_DSCR		0x16	// Davicom Specified Config Reg. Addr.
#define DM9000_DSCSR	0x17	// Davicom Specified Config and Status Reg. Addr.
#define DM9000_10BTCSR	0x18	// 10BaseT Config and Status Reg. Addr.

#define DM9000_REG05	0x30	// SKIP_CRC/SKIP_LONG
#define DM9000_REG08	0x37
#define DM9000_REG09	0x38
#define DM9000_REG0A	0x29	// Flow Control Enable
#define DM9000_REGFF	0x83	// IMR

#define DM9000_PKT_MAX		UIP_BUFSIZE	// Received packet max size
#define DM9000_PKT_RDY		0x01	    // Packet ready to receive
#define DM9000_INT_MII		0x00
#define DM9000_EXT_MII		0x80

#define DMFE_MAX_MULTICAST 		14

#define DM9000_RX_INTR			0x01
#define DM9000_TX_INTR			0x02
#define DM9000_OVERFLOW_INTR	0x04

#define DM9000_BYTE_MODE		0x02	// 8-bit mode
#define DM9000_WORD_MODE		0x00	// 16-bit mode	
#define DM9000_DWORD_MODE		0x01	// 32-bit mode


enum DM9000_PHY_mode {
	DM9000_10MHD   	= 0,
	DM9000_100MHD  	= 1,
	DM9000_10MFD   	= 4,
	DM9000_100MFD  	= 5,
	DM9000_AUTO    	= 8,
	DM9000_1M_HPNA 	= 0x10
};

enum DM9000_NIC_TYPE {
	FASTETHER_NIC 	= 0,
	HOMERUN_NIC   	= 1,
	LONGRUN_NIC   	= 2
};

// Active operation mode
enum DM9000_OP_mode {
	OP_10MHD		= 1,
	OP_10MFD		= 2,
	OP_100MHD		= 4,
	OP_100MFD		= 8
};

enum DM9000_SF_mode{
	VLAN_Enable		= 1,
	FlowControl		= 2,
	TxPausePacket	= 4
};
