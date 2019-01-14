//--------------------------------------------------------------------
// TUCN, Computer Science Department
// Input/Output Systems and Peripheral Devices
//--------------------------------------------------------------------
// http://users.utcluj.ro/~baruch/en/pages/teaching/inputoutput-systems/laboratory.php
//--------------------------------------------------------------------
// File:		ATA-ATAPI-e.h
// Date:		18.08.2015
// Modified:	13.12.2015
//--------------------------------------------------------------------
// Definitions for the ATA/ATAPI interface
//--------------------------------------------------------------------

#ifndef _ATA_ATAPI_H  
#define _ATA_ATAPI_H 

#ifndef _PCI_H
#define PCI_CONFIG_START	0xF8000000			// Start address of the PCI/PCIe configuration space
#define PCI_CONFIG_ADR		0x0CF8				// Address port for accessing the configuration space
#define PCI_CONFIG_DATA		0x0CFC				// Data port for accessing the configuration space
#endif

// Structure for the PCI/PCIe configuration registers of SATA controllers
typedef struct tSATA_PCI_CFG {
	WORD		VID;							// 0x00 Vendor ID
	WORD		DID;							// 0x02 Device ID
	WORD		PCICMD;							// 0x04 PCI Command
	WORD		PCISTS;							// 0x06 PCI Status
	BYTE		RID;							// 0x08 Revision ID
	BYTE		PI;								// 0x09 Programming Interface
	BYTE		SCC;							// 0x0A Sub Class Code
	BYTE		BCC;							// 0x0B Base Class Code
	BYTE		Res0;							// 0x0C Reserved
	BYTE		PMLT;							// 0x0D Primary Master Latency Timer
	BYTE		HTYPE;							// 0x0E Header Type
	BYTE		Res1;							// 0x0F Reserved
	DWORD		PCMD_BAR;						// 0x10 Primary Command Block Base Address
	DWORD		PCNL_BAR;						// 0x14 Primary Control Block Base Address
	DWORD		SCMD_BAR;						// 0x18 Secondary Command Block Base Address
	DWORD		SCNL_BAR;						// 0x1C Secondary Control Block Base Address
	DWORD		BAR;							// 0x20 Legacy Bus Master Base Address
	DWORD		ABAR;							// 0x24 AHCI Base Address / SATA Index Data Pair Base Address
	DWORD		Res2;							// 0x28-0x2B Reserved
	WORD		SVID;							// 0x2C Subsystem Vendor ID
	WORD		SID;							// 0x2E Subsysem ID
	DWORD		Res3;							// 0x30-0x33 Reserved
	BYTE		CAP;							// 0x34 Capabilities Pointer
	BYTE		Res4[3];						// 0x35-0x37 Reserved
	DWORD		Res5;							// 0x38-0x3B Reserved
	BYTE		INT_LN;							// 0x3C Interrupt Line
	BYTE		INT_PN;							// 0x3D Interrupt Pin
	BYTE		Res6[2];						// 0x3E-0x3F Reserved
	WORD		PIDE_TIM;						// 0x40-0x41 Primary IDE Timing
	WORD		SIDE_TIM;						// 0x42-0x43 Secondary IDE Timing
	BYTE		SIDETIM;						// 0x44 Slave IDE Timing
	BYTE		Res7[3];						// 0x45-0x47 Reserved
	BYTE		SDMA_CNT;						// 0x48 Synchronous DMA Control
	BYTE		Res8;							// 0x49 Reserved
	WORD		SDMA_TIM;						// 0x4A-0x4B Synchronous DMA Timing
	DWORD		Res9[2];						// 0x4C-0x53 Reserved
	DWORD		IDE_CONFIG;						// 0x54-0x57 IDE I/O Configuration
} SATA_PCI_CFG, *PSATA_PCI_CFG;

//--------------------------------------------------------------------
// Offsets for the ATA registers
// R and W indicate whether the register can be used for read (R) or write (W)
//--------------------------------------------------------------------

// Offsets for the Command Block registers
// The offsets shall be added to the Command Block base address (for primary or secondary ATA channel)
#define ATA_DATA				0				// Data (R, W)
#define ATA_ERROR				1				// Error (R)
#define ATA_FEATURES			1				// Features (W)
#define ATA_SECT_CNT			2				// Sector Count (R, W)
#define ATA_LBA_LOW				3				// LBA Low (R, W)
#define ATA_LBA_MID				4				// LBA Mid (R, W)
#define ATA_LBA_HIGH			5				// LBA High (R, W)
#define ATA_DEVICE				6				// Device (R, W)
#define ATA_STATUS				7				// Status (R)
#define ATA_COMMAND				7				// Command (W)

// Offsets for the Control Block registers
// The offsets shall be added to the Control Block base address (for primary or secondary ATA channel)
#define ATA_ALT_STATUS			2				// Alternate Status (R)
#define ATA_DEVICE_CTRL			2				// Device Control (W)

//--------------------------------------------------------------------
// Offsets for the ATAPI registers
// R and W indicate whether the register can be used for read (R) or write (W)
//--------------------------------------------------------------------

// Offsets for the Command Block registers
// The offsets shall be added to the Command Block base address (for primary or secondary ATA channel)
#define ATAPI_DATA				0				// Data (R, W)
#define ATAPI_ERROR				1				// Error (R)
#define ATAPI_FEATURES			1				// Features (W)
#define ATAPI_INT_REASON		2				// Interrupt Reason (R)
#define ATAPI_SECT_CNT			2				// Sector Count (W)
#define ATAPI_LBA_LOW			3				// LBA Low (R, W)
#define ATAPI_BYTE_CNT_LOW		4				// Byte Count Low (R, W)
#define ATAPI_BYTE_CNT_HIGH		5				// Byte Count High (R, W)
#define ATAPI_DEVICE			6				// Device (R, W)
#define ATAPI_STATUS			7				// Status (R)
#define ATAPI_COMMAND			7				// Command (W)

// Offsets for the Control Block registers
// The offsets shall be added to the Control Block base address (for primary or secondary ATA channel)
#define ATAPI_ALT_STATUS		2				// Alternate Status (R)
#define ATAPI_DEVICE_CTRL		2				// Device Control (W)

//--------------------------------------------------------------------
// Masks for the ATA and ATAPI registers
//--------------------------------------------------------------------

// Error Register (ATA and ATAPI)
#define ERROR_ABRT				(1 << 2)		// ABRT (Command aborted)

// Device Register (ATA and ATAPI)
#define DEVICE_LBA				(1 << 6)		// LBA (LBA addressing)
#define DEVICE_DEV				(1 << 4)		// DEV (Device select)

// Status Register (ATA and ATAPI)
#define STATUS_BSY				(1 << 7)		// BSY (Busy)
#define STATUS_DRDY				(1 << 6)		// DRDY (Device Ready)
#define STATUS_DF				(1 << 5)		// DF (Device Fault)
#define STATUS_DRQ				(1 << 3)		// DRQ (Data Request)
#define STATUS_ERR				(1 << 0)		// ERR (Error)
#define STATUS_CHK				(1 << 0)		// CHK (Check, for the PACKET command)

// Device Control Register (ATA and ATAPI)
#define DEVICE_CTRL_HOB			(1 << 7)		// HOB (High Order Byte)
#define DEVICE_CTRL_SRST		(1 << 2)		// SRST (Software Reset)
#define DEVICE_CTRL_NIEN		(1 << 1)		// nIEN (Interrupt Enable)

//--------------------------------------------------------------------
// Signatures for ATA, SATA, ATAPI, and SATAPI drives
// - ATA interface: The 4 bytes (starting with the most significant) correspond
//   to registers: LBA High; LBA Mid; LBA Low; Sector Count
// - ATAPI interface: The 4 bytes (starting with the most significant) correspond
//   to registers: Byte Count High; Byte Count Low; LBA Low; Interrupt Reason
//--------------------------------------------------------------------

#define SIG_ATA					0x00000101		// signature for an ATA drive
#define SIG_SATA				0xC33C0101		// signature for a SATA drive
#define SIG_ATAPI				0xEB140101		// signature for an ATAPI drive
#define SIG_SATAPI				0x96690101		// signature for a SATAPI drive

//--------------------------------------------------------------------
// Command codes for the ATA interface
//--------------------------------------------------------------------

#define ATA_DEVICE_RESET		0x08			// Device Reset
#define ATA_EXEC_DEVICE_DIAG	0x90			// Execute Device Diagnostic
#define ATA_FLUSH_CACHE			0xE7			// Flush Cache
#define ATA_FLUSH_CACHE_EXT		0xEA			// Flush Cache Extended
#define ATA_ID_DEVICE			0xEC			// Identify Device
#define ATA_ID_PACKET_DEVICE	0xA1			// Identify Packet Device
#define ATA_IDLE				0xE3			// Idle
#define ATA_IDLE_IMMED			0xE1			// Idle Immediate
#define ATA_NV_CACHE			0xB6			// Non Volatile Cache
#define ATA_PACKET				0xA0			// Packet
#define ATA_READ_BUFFER			0xE4			// Read Buffer
#define ATA_READ_DMA			0xC8			// Read DMA
#define ATA_READ_DMA_EXT		0x25			// Read DMA Extended
#define ATA_READ_DMA_QUEUED		0xC7			// Read DMA Queued
#define ATA_READ_DMA_QUEUED_EXT	0x26			// Read DMA Queued Extended
#define ATA_READ_LOG_EXT		0x2F			// Read Log Extended
#define ATA_READ_LOG_DMA_EXT	0x47			// Read Log DMA Extended
#define ATA_READ_MULTIPLE		0xC4			// Read Multiple
#define ATA_READ_MULTIPLE_EXT	0x29			// Read Multiple Extended
#define ATA_READ_NATIVE_MAX		0xF8			// Read Native Maximum Address
#define ATA_READ_NATIVE_MAX_EXT	0x27			// Read Native Maximum Address Extended
#define ATA_READ_SECTORS		0x20			// Read Sector(s)
#define ATA_READ_SECTORS_EXT	0x24			// Read Sector(s) Extended
#define ATA_READ_VERIF_SECT		0x40			// Read Verify Sector(s)
#define ATA_READ_VERIF_SECT_EXT	0x42			// Read Verify Sector(s) Extended
#define ATA_SECURITY_DIS_PASSW	0xF6			// Security Disable Password
#define ATA_SECURITY_ERASE_PREP	0xF3			// Security Erase Prepare
#define ATA_SECURITY_ERASE_UNIT	0xF4			// Security Erase Unit
#define ATA_SECURITY_SET_PASSW	0xF1			// Security Set Password
#define ATA_SERVICE				0xA2			// Service
#define ATA_SET_FEATURES		0xEF			// Set Features
#define ATA_SMART				0xB0			// SMART
#define ATA_SMART_DIS_OPER		0xD9			// SMART - SMART Disable Operations
#define ATA_SMART_EN_OPER		0xD8			// SMART - SMART Enable Operations
#define ATA_SMART_READ_DATA		0xD0			// SMART - SMART Read Data
#define ATA_SMART_READ_LOG		0xD5			// SMART - SMART Read Log
#define ATA_SMART_RETURN_STATUS	0xDA			// SMART - SMART Return Status
#define ATA_SMART_WRITE_LOG		0xD6			// SMART - SMART Write Log
#define ATA_STANDBY				0xE2			// Standby
#define ATA_STANDBY_IMMED		0xE2			// Standby Immediate
#define ATA_WRITE_BUFFER		0xE8			// Write Buffer
#define ATA_WRITE_DMA			0xCA			// Write DMA
#define ATA_WRITE_DMA_EXT		0x35			// Write DMA Extended
#define ATA_WRITE_DMA_QUEUED	0xCC			// Write DMA Queued
#define ATA_WRITE_LOG_EXT		0x3F			// Write Log Extended
#define ATA_WRITE_LOG_DMA_EXT	0x57			// Write Log DMA Extended
#define ATA_WRITE_MULTIPLE		0xC3			// Write Multiple
#define ATA_WRITE_MULTIPLE_EXT	0x39			// Write Multiple Extended
#define ATA_WRITE_SECTORS		0x30			// Write Sector(s)
#define ATA_WRITE_SECTORS_EXT	0x34			// Write Sector(s) Extended

//--------------------------------------------------------------------
// SCSI command codes for the ATAPI interface
//--------------------------------------------------------------------

// Command codes for CD drives
#define SCSI_INQUIRY			0x12			// Inquiry
#define SCSI_LOAD_UNLOAD		0xA6			// Load/Unload CD
#define SCSI_MECH_STATUS		0xBD			// Mechanism Status
#define SCSI_MODE_SELECT_10		0x55			// Mode Select (10)
#define SCSI_MODE_SELECT_6		0x15			// Mode Select (6)
#define SCSI_MODE_SENSE_10		0x5A			// Mode Sense (10)
#define SCSI_MODE_SENSE_6		0x1A			// Mode Sense (6)
#define SCSI_PAUSE_RESUME		0x4B			// Pause/Resume
#define SCSI_PLAY_AUDIO_10		0x45			// Play Audio (10)
#define SCSI_PLAY_AUDIO_12		0xA5			// Play Audio (12)
#define SCSI_PLAY_AUDIO_MSF		0x47			// Play Audio MSF
#define SCSI_PLAY_CD			0xBC			// Play CD
#define SCSI_PREV_ALLOW_REMOVAL	0x1E			// Prevent/Allow Medium Removal
#define SCSI_READ_10			0x28			// Read (10)
#define SCSI_READ_12			0xA8			// Read (12)
#define SCSI_READ_CD			0xBE			// Read CD
#define SCSI_READ_CD_MSF		0xB9			// Read CD MSF
#define SCSI_READ_CD_REC_CAP	0x25			// Read CD Recorded Capacity
#define SCSI_READ_HEADER		0x44			// Read Header
#define SCSI_READ_SUBCHANNEL	0x42			// Read Sub-channel
#define SCSI_READ_TOC_PMA_ATIP	0x43			// Read TOC/PMA/ATIP
#define SCSI_RELEASE_10			0x57			// Release (10)
#define SCSI_REQUEST_SENSE		0x03			// Request Sense
#define SCSI_RESERVE_10			0x56			// Reserve (10)
#define SCSI_SCAN				0xBA			// Scan
#define SCSI_SEEK_10			0x2B			// Seek (10)
#define SCSI_SEEK_6				0x0B			// Seek (6)
#define SCSI_SEND_DIAG			0x1D			// Send Diagnostic
#define SCSI_SET_CD_SPEED		0xBB			// Set CD Speed
#define SCSI_START_STOP_UNIT	0x1B			// Start/Stop Unit
#define SCSI_STOP_PLAY_SCAN		0x4E			// Stop Play/Scan
#define SCSI_TEST_UNIT_READY	0x00			// Test Unit Ready

// Command codes for CD-R/RW drives
#define SCSI_BLANK				0xA1			// Blank
#define SCSI_CLOSE_TRK_SESSION	0x5B			// Close Track/Session
#define SCSI_FORMAT_UNIT		0x04			// Format Unit
#define SCSI_READ_BUFFER_CAP	0x5C			// Read Buffer Capacity
#define SCSI_READ_DISC_INFO		0x51			// Read Disc Information
#define SCSI_MASTER_CUE			0x59			// Read Master Cue
#define SCSI_READ_TRK_INFO		0x52			// Read Track Information
#define SCSI_REPAIR_TRK			0x58			// Repair Track
#define SCSI_RESERVE_TRK		0x53			// Reserve Track
#define SCSI_SEND_CUE_SHEET		0x5D			// Send Cue Sheet
#define SCSI_SEND_OPC_INFO		0x54			// Send OPC Information
#define SCSI_SYNCHR_CACHE		0x35			// Synchronize Cache
#define SCSI_WRITE_10			0x2A			// Write (10)
#define SCSI_WRITE_12			0xAA			// Write (12)

#endif
