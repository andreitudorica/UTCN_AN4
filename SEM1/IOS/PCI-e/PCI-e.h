//--------------------------------------------------------------------
// TUCN, Computer Science Department
// Input/Output Systems and Peripheral Devices
//--------------------------------------------------------------------
// http://users.utcluj.ro/~baruch/en/pages/teaching/inputoutput-systems/laboratory.php
//--------------------------------------------------------------------
// File:		PCI-e.h
// Date:		09.08.2015
// Modified:	13.08.2015
//--------------------------------------------------------------------
// Definitions for accessing the PCI/PCIe configuration space
//--------------------------------------------------------------------

#ifndef _PCI_H
#define _PCI_H

#define PCI_CONFIG_START	0xF8000000	// Start address of the PCI/PCIe configuration space
#define PCI_CONFIG_ADR		0x0CF8		// Address port for accessing the configuration space
#define PCI_CONFIG_DATA		0x0CFC		// Data port for accessing the configuration space

// Structures for the PCI/PCIe configuration registers

// Structure for header Type 0
typedef struct tPCI_CONFIG0 {
	WORD		VendorID;				// 0x00 Vendor ID
	WORD		DeviceID;				// 0x02 Device ID
	WORD		Command;				// 0x04 Command Register
	WORD		Status;					// 0x06 Status Register
	BYTE		RevisionID;				// 0x08 Revision ID
	BYTE		ProgInterface;			// 0x09 Programming Interface
	BYTE		SubClass;				// 0x0A Sub-Class Code
	BYTE		BaseClass;				// 0x0B Base Class-Code
	BYTE		CacheLineSize;			// 0x0C Cache Line Size
	BYTE		LatencyTimer;			// 0x0D Master Latency Timer (0x00 for PCIe)
	BYTE		HeaderType;				// 0x0E Header Type
	BYTE		BIST;					// 0x0F Built-In Self-Test
	DWORD		BaseAddress0;			// 0x10 Base Address 0
	DWORD		BaseAddress1;			// 0x14 Base Address 1
	DWORD		BaseAddress2;			// 0x18 Base Address 2
	DWORD		BaseAddress3;			// 0x1C Base Address 3
	DWORD		BaseAddress4;			// 0x20 Base Address 4
	DWORD		BaseAddress5;			// 0x24 Base Address 5
	DWORD		CardBusCIS;				// 0x28 CardBus CIS Pointer
	WORD		SubSystVendorID;		// 0x2C Subsystem Vendor ID
	WORD		SubSystID;				// 0x2E Subsystem ID
	DWORD		ROMBaseAddress;			// 0x30 Expansion ROM Base Address
	BYTE		CapabilitiesPtr;		// 0x34 Capabilities Pointer
	BYTE		Res0[3];				// 0x35-0x37 Reserved
	DWORD		Res1;					// 0x38 Reserved
	BYTE		InterruptLine;			// 0x3C Interrupt Line
	BYTE		InterruptPin;			// 0x3D Interrupt Pin
	BYTE		MinGrant;				// 0x3E Minimum Grant (0x00 for PCIe)
	BYTE		MaxLatency;				// 0x3F Maximum Latency (0x00 for PCIe)
	DWORD		DevSpecific[48];		// 0x40-0xFF Device-Specific Registers
} PCI_CONFIG0, *PPCI_CONFIG0;

// Structure for header Type 1
typedef struct tPCI_CONFIG1 {
	WORD		VendorID;				// 0x00 Vendor ID
	WORD		DeviceID;				// 0x02 Device ID
	WORD		Command;				// 0x04 Command Register
	WORD		Status;					// 0x06 Status Register
	BYTE		RevisionID;				// 0x08 Revision ID
	BYTE		ProgInterface;			// 0x09 Programming Interface
	BYTE		SubClass;				// 0x0A Sub-Class Code
	BYTE		BaseClass;				// 0x0B Base Class-Code
	BYTE		CacheLineSize;			// 0x0C Cache Line Size
	BYTE		LatencyTimer;			// 0x0D Master Latency Timer (0x00 for PCIe)
	BYTE		HeaderType;				// 0x0E Header Type
	BYTE		BIST;					// 0x0F Built-In Self-Test
	DWORD		BaseAddress0;			// 0x10 Base Address 0
	DWORD		BaseAddress1;			// 0x14 Base Address 1
	BYTE		PrimaryBus;				// 0x18 Primary Bus Number
	BYTE		SecondaryBus;			// 0x19 Secondary Bus Number
	BYTE		SubordinateBus;			// 0x1A Subordinate Bus Number
	BYTE		SecondaryLatency;		// 0x1B Secondary Latency Timer
	BYTE		IOBase;					// 0x1C I/O Base
	BYTE		IOLimit;				// 0x1D I/O Limit
	WORD		SecondaryStatus;		// 0x1E Secondary Status Register
	WORD		MemoryBase;				// 0x20 Memory Base
	WORD		MemoryLimit;			// 0x22 Memory Limit
	WORD		PrefMemoryBase;			// 0x24 Prefetchable Memory Base
	WORD		PrefMemoryLimit;		// 0x26 Prefetchable Memory Limit
	DWORD		PrefBaseUpper32;		// 0x28 Prefetchable Base Upper 32 Bits
	DWORD		PrefLimitUpper32;		// 0x2C Prefetchable Limit Upper 32 Bits
	WORD		IOBaseUpper16;			// 0x30 I/O Base Upper 16 Bits
	WORD		IOLimitUpper16;			// 0x32 I/O Limit Upper 16 Bits
	BYTE		CapabilitiesPtr;		// 0x34 Capabilities Pointer
	BYTE		Res0[3];				// 0x35-0x37 Reserved
	DWORD		ROMBaseAddress;			// 0x38 Expansion ROM Base Address
	BYTE		InterruptLine;			// 0x3C Interrupt Line
	BYTE		InterruptPin;			// 0x3D Interrupt Pin
	WORD		BridgeControl;			// 0x3E Bridge Control
	DWORD		DevSpecific[48];		// 0x40-0xFF Device-Specific Registers
} PCI_CONFIG1, *PPCI_CONFIG1;

// Structure for the PCI/PCIe class code table
typedef struct tPCI_CLASS_TABLE
{
	BYTE	Class;						// class code
	BYTE	SubClass;					// sub-class code
	BYTE	ProgIf;						// programming interface
	CHAR	*ClassDesc;					// class and sub-class descriptor
	CHAR	*ProgIfDesc;				// programming interface descriptor
} PCI_CLASS_TABLE, *PPCI_CLASS_TABLE;

PCI_CLASS_TABLE PciClassTable [] =
{
	0x00, 0x00, 0x00, "Non-VGA unclassified device (before PCI revision 2.0)", "",
	0x00, 0x01, 0x00, "VGA compatible unclassified device (before PCI revision 2.0)", "",

	0x01, 0x00, 0x00, "SCSI mass storage controller", "",
	0x01, 0x01, 0x00, "IDE mass storage controller", "",
	0x01, 0x02, 0x00, "Floppy disk controller", "",
	0x01, 0x03, 0x00, "IPI (Intelligent Peripheral Interface) mass storage controller", "",
	0x01, 0x04, 0x00, "RAID mass storage controller", "",
	0x01, 0x05, 0x20, "ATA mass storage controller ", "(with single-stepping DMA)",
	0x01, 0x05, 0x30, "ATA mass storage controller ", "(with chained DMA)",
	0x01, 0x06, 0x00, "SATA mass storage controller ", "(Vendor specific)",
	0x01, 0x06, 0x01, "SATA mass storage controller ", "(AHCI)",
	0x01, 0x06, 0x02, "SATA mass storage controller ", "(Serial Storage Bus)",
	0x01, 0x07, 0x00, "Serial Attached SCSI mass storage controller", "",
	0x01, 0x07, 0x01, "Serial Attached SCSI mass storage controller ", "(Serial Storage Bus)",
	0x01, 0x08, 0x01, "Non-volatile memory controller ", "(NVHCMI)",
	0x01, 0x08, 0x02, "Non-volatile memory controller ", "(NVM Express)",
	0x01, 0x80, 0x00, "Mass storage controller", "",

	0x02, 0x00, 0x00, "Ethernet network controller", "",
	0x02, 0x01, 0x00, "Token Ring network controller", "",
	0x02, 0x02, 0x00, "FDDI network controller", "",
	0x02, 0x03, 0x00, "ATM network controller", "",
	0x02, 0x04, 0x00, "ISDN network controller", "",
	0x02, 0x05, 0x00, "WorldFIP (Factory Instrumentation Protocol) network controller", "",
	0x02, 0x06, 0x00, "PICMG network controller", "",
	0x02, 0x07, 0x00, "InfiniBand network controller", "",
	0x02, 0x08, 0x00, "Fabric network controller", "",
	0x02, 0x80, 0x00, "Network controller", "",

	0x03, 0x00, 0x00, "VGA-compatible display controller ", "(VGA)",
	0x03, 0x00, 0x01, "VGA-compatible display controller ", "(8514)",
	0x03, 0x01, 0x00, "XGA-compatible display controller", "",
	0x03, 0x02, 0x00, "3D display controller", "",
	0x03, 0x80, 0x00, "Display controller", "",

	0x04, 0x00, 0x00, "Video multimedia device", "",
	0x04, 0x01, 0x00, "Audio multimedia device", "",
	0x04, 0x02, 0x00, "Computer telephony device", "",
	0x04, 0x03, 0x00, "Audio device", "",
	0x04, 0x80, 0x00, "Multimedia device", "",

	0x05, 0x00, 0x00, "RAM memory controller", "",
	0x05, 0x01, 0x00, "Flash memory controller", "",
	0x05, 0x80, 0x00, "Memory controller", "",

	0x06, 0x00, 0x00, "Host/PCI bridge", "",
	0x06, 0x01, 0x00, "PCI/ISA bridge", "",
	0x06, 0x02, 0x00, "PCI/EISA bridge", "",
	0x06, 0x03, 0x00, "PCI/Micro Channel bridge", "",
	0x06, 0x04, 0x00, "PCI/PCI bridge ", "(Normal decode)",
	0x06, 0x04, 0x01, "PCI/PCI bridge ", "(Subtractive decode)",
	0x06, 0x05, 0x00, "PCI/PCMCIA bridge", "",
	0x06, 0x06, 0x00, "PCI/NuBus bridge", "",
	0x06, 0x07, 0x00, "PCI/CardBus bridge", "",
	0x06, 0x08, 0x00, "PCI/RACEway bridge ", "(Transparent mode)",
	0x06, 0x08, 0x01, "PCI/RACEway bridge ", "(Endpoint mode)",
	0x06, 0x09, 0x40, "Semi-transparent PCI-to-PCI bridge ", "(Primary PCI bus towards host CPU)",
	0x06, 0x09, 0x80, "Semi-transparent PCI-to-PCI bridge ", "(Secondary PCI bus towards host CPU)",
	0x06, 0x0A, 0x00, "InfiniBand to PCI bridge", "",
	0x06, 0x80, 0x00, "Bridge", "",

	0x07, 0x00, 0x00, "Serial controller ", "(8250)",
	0x07, 0x00, 0x01, "Serial controller ", "(16450)",
	0x07, 0x00, 0x02, "Serial controller ", "(16550)",
	0x07, 0x00, 0x03, "Serial controller ", "(16650)",
	0x07, 0x00, 0x04, "Serial controller ", "(16750)",
	0x07, 0x00, 0x05, "Serial controller ", "(16850)",
	0x07, 0x00, 0x06, "Serial controller ", "(16950)",
	0x07, 0x01, 0x00, "Parallel port ", "(SPP)",
	0x07, 0x01, 0x01, "Parallel port ", "(Bi-directional)",
	0x07, 0x01, 0x02, "Parallel port ", "(ECP)",
	0x07, 0x01, 0x03, "Parallel communications controller ", "(IEEE 1284)",
	0x07, 0x01, 0xFE, "Parallel communications device ", "(IEEE 1284)",
	0x07, 0x02, 0x00, "Multiport serial controller", "",
	0x07, 0x03, 0x00, "Modem ", "(Generic)",
	0x07, 0x03, 0x01, "Modem ", "(Hayes, 16450-compatible interface)",
	0x07, 0x03, 0x02, "Modem ", "(Hayes, 16550-compatible interface)",
	0x07, 0x03, 0x03, "Modem ", "(Hayes, 16650-compatible interface)",
	0x07, 0x03, 0x04, "Modem ", "(Hayes, 16750-compatible interface)",
	0x07, 0x04, 0x00, "GPIB (IEEE 488.1/2) controller", "",
	0x07, 0x05, 0x00, "Smart Card controller", "",
	0x07, 0x80, 0x00, "Communications controller", "",

	0x08, 0x00, 0x00, "Programmable interrupt controller (PIC) ", "(8259)",
	0x08, 0x00, 0x01, "Programmable interrupt controller (PIC) ", "(ISA)",
	0x08, 0x00, 0x02, "Programmable interrupt controller (PIC) ", "(EISA)",
	0x08, 0x00, 0x10, "Programmable interrupt controller (PIC) ", "(IO APIC)",
	0x08, 0x00, 0x20, "Programmable interrupt controller (PIC) ", "(IO(X) APIC)",
	0x08, 0x01, 0x00, "DMA controller ", "(8237)",
	0x08, 0x01, 0x01, "DMA controller ", "(ISA)",
	0x08, 0x01, 0x02, "DMA controller ", "(EISA)",
	0x08, 0x02, 0x00, "Timer ", "(8254)",
	0x08, 0x02, 0x01, "Timer ", "(ISA)",
	0x08, 0x02, 0x02, "Timer ", "(EISA)",
	0x08, 0x02, 0x03, "Timer ", "(HPET)",
	0x08, 0x03, 0x00, "Real-time clock (RTC) ", "(Generic)",
	0x08, 0x03, 0x01, "Real-time clock (RTC) ", "(ISA)",
	0x08, 0x04, 0x00, "PCI hot-plug controller", "",
	0x08, 0x05, 0x00, "SD host controller", "",
	0x08, 0x06, 0x00, "IOMMU system controller", "",
	0x08, 0x80, 0x00, "System peripheral", "",

	0x09, 0x00, 0x00, "Keyboard controller", "",
	0x09, 0x01, 0x00, "Digitizer", "",
	0x09, 0x02, 0x00, "Mouse controller", "",
	0x09, 0x03, 0x00, "Scanner controller", "",
	0x09, 0x04, 0x00, "Gameport controller ", "(Generic)",
	0x09, 0x04, 0x10, "Gameport controller ", "(Extended)",
	0x09, 0x80, 0x00, "Input device controller", "",

	0x0A, 0x00, 0x00, "Generic docking station", "",
	0x0A, 0x80, 0x00, "Docking station", "",

	0x0B, 0x00, 0x00, "i386 processor", "",
	0x0B, 0x01, 0x00, "i486 processor", "",
	0x0B, 0x02, 0x00, "Pentium processor", "",
	0x0B, 0x10, 0x00, "Alpha processor", "",
	0x0B, 0x20, 0x00, "PowerPC processor", "",
	0x0B, 0x30, 0x00, "MIPS processor", "",
	0x0B, 0x40, 0x00, "Co-processor", "",

	0x0C, 0x00, 0x00, "Firewire (IEEE 1394) bus controller ", "(Generic)",
	0x0C, 0x00, 0x10, "Firewire (IEEE 1394) bus controller ", "(OHCI)",
	0x0C, 0x01, 0x00, "ACCESS.bus controller", "",
	0x0C, 0x02, 0x00, "SSA (Serial Storage Architecture) controller", "",
	0x0C, 0x03, 0x00, "USB controller ", "(UHCI)",
	0x0C, 0x03, 0x10, "USB controller ", "(OHCI)",
	0x0C, 0x03, 0x20, "USB controller ", "(EHCI)",
	0x0C, 0x03, 0x30, "USB controller ", "(XHCI)",
	0x0C, 0x03, 0x80, "USB controller ", "(Unspecified programming interface)",
	0x0C, 0x03, 0xFE, "USB device", "",
	0x0C, 0x04, 0x00, "Fibre Channel controller", "",
	0x0C, 0x05, 0x00, "SMBus controller", "",
	0x0C, 0x06, 0x00, "InfiniBand bus controller", "",
	0x0C, 0x07, 0x00, "IPMI (Intelligent Platform Management Interface) SMIC (Server Management Interface Chip) interface", "",
	0x0C, 0x07, 0x01, "IPMI (Intelligent Platform Management Interface) keyboard controller interface", "",
	0x0C, 0x07, 0x02, "IPMI (Intelligent Platform Management Interface) block transfer interface", "",
	0x0C, 0x08, 0x00, "SERCOS (Serial Real-Time Communication System) interface", "",
	0x0C, 0x07, 0x00, "CANbus controller", "",
	0x0C, 0x80, 0x00, "Serial bus controller", "",

	0x0D, 0x00, 0x00, "IrDA controller", "",
	0x0D, 0x01, 0x00, "Consumer IR controller", "",
	0x0D, 0x10, 0x00, "RF controller", "",
	0x0D, 0x11, 0x00, "Bluetooth controller", "",
	0x0D, 0x12, 0x00, "Broadband controller", "",
	0x0D, 0x20, 0x00, "802.1a controller", "",
	0x0D, 0x21, 0x00, "802.1b controller", "",
	0x0D, 0x80, 0x00, "Wireless controller", "",

	0x0E, 0x00, 0x00, "I2O intelligent I/O controller", "",
	0x0E, 0x80, 0x00, "Intelligent I/O controller", "",

	0x0F, 0x01, 0x00, "Satellite TV controller", "",
	0x0F, 0x02, 0x00, "Satellite audio communication controller", "",
	0x0F, 0x03, 0x00, "Satellite voice communication controller", "",
	0x0F, 0x04, 0x00, "Satellite data communication controller", "",
	0x0F, 0x80, 0x00, "Satellite communication controller", "",

	0x10, 0x00, 0x00, "Network and computing encryption controller", "",
	0x10, 0x01, 0x00, "Entertainment encryption controller", "",
	0x10, 0x80, 0x00, "Encryption controller", "",

	0x11, 0x00, 0x00, "DPIO (Digital Parallel In Out) module", "",
	0x11, 0x01, 0x00, "Performance counters", "",
	0x11, 0x10, 0x00, "Communications synchronization plus time and frequency measurement controller", "",
	0x11, 0x20, 0x00, "Data acquisition and signal processing management controller", "",
	0x11, 0x80, 0x00, "Data acquisition and signal processing controller", "",

	0x12, 0x00, 0x00, "Processing accelerator", "",

	0xFF, 0x00, 0x00, "Device vith unassigned class/sub-class code", "",
};

// Number of table entries; it can be used for searching in the table
#define	PCI_CLASS_TABLE_LEN	(sizeof(PciClassTable) / sizeof(PCI_CLASS_TABLE)) 

#endif
