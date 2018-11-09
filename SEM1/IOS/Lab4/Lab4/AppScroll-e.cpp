//--------------------------------------------------------------------
// TUCN, Computer Science Department
// Input/Output Systems and Peripheral Devices
//--------------------------------------------------------------------
// http://users.utcluj.ro/~baruch/en/pages/teaching/inputoutput-systems/laboratory.php
//--------------------------------------------------------------------
// File:		AppScroll-e.cpp
// Date:		10.10.2015
// Modified:	21.11.2015
//--------------------------------------------------------------------
// IOS application example with vertical scroll bar
//--------------------------------------------------------------------

#include <iostream>
#include <cstdio>
#include <windows.h>
#include "Hw.h"
#include "PCI-e.h"
#include "PCI-vendor-dev.h"
using namespace std;

#define NLIN 500								// number of lines in the display window
#define NCOL 240								// number of columns in the display window

// Global variables
char szBuffer[NLIN][NCOL];						// buffer for the window contents
int  cLine;										// number of current line in the display buffer

												// Declarations of external functions
void DisplWindow(HWND hWnd);

DWORD64 qvFuncAddr;

PPCI_CONFIG0 returnsPointer(WORD busNumber, WORD deviceNumber, WORD PCIeFunctionNumber) {
	DWORD64 qwAdrDisp = PCI_CONFIG_START;
	qwAdrDisp = qwAdrDisp | (busNumber << 20) | (deviceNumber << 15) | (PCIeFunctionNumber << 12);
	return (PPCI_CONFIG0)qwAdrDisp;
}

DWORD readDWORD(byte bus_number, byte device_number, byte function_number, byte dw_number) {
	DWORD data = ((1 << 31) | (bus_number << 16) | (device_number << 11) | (function_number << 8) | (dw_number << 2));
	__outpd(PCI_CONFIG_ADR, data);
	DWORD readData = __inpd(PCI_CONFIG_DATA);
	return readData;
}

//--------------------------------------------------------------------
// Function AppScroll
//--------------------------------------------------------------------
//
// Function:	IOS application example with vertical scroll bar
//
// Parameters:	- Handle to the application window
//
// Returns:		0 - Operation completed successfully
//				1 - Error at initializing the Hw driver
//
//--------------------------------------------------------------------

int AppScroll(HWND hWnd)
{
	int   i;

	char szMes0[] = "Error initializing the Hw driver";
	char szMes1[] = "IOS Application";

	// Initialize the Hw library
	if (!HwOpen()) {
		wsprintf(szBuffer[0], szMes0);
		MessageBox(NULL, szBuffer[0], "HwOpen", MB_ICONSTOP);
		return 1;
	}

	// Erase the display buffer and the window contents
	for (i = 0; i < NLIN; i++) {
		memset(szBuffer[i], ' ', NCOL);
	}
	cLine = 1;

	// Copy the start message into the display buffer and display the message
	wsprintf(szBuffer[cLine], szMes1);
	cLine += 2;
	DisplWindow(hWnd);

	//--------------------------------------------------------------------
	// To be completed with the application's code
	//--------------------------------------------------------------------

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 31; j++)
			for (int k = 0; k < 7; k++)
			{
				///2.7.2, 2.7.3
				PPCI_CONFIG0 pRegPci = returnsPointer(i, j, k);
				WORD wVendorID = _inmw((DWORD_PTR)&pRegPci->VendorID);

				if (wVendorID == 0xFFFF)
					continue;
				wsprintf(szBuffer[cLine++], "2.7.3\n", i, j, k);

				wsprintf(szBuffer[cLine++], "bus = %d  device = %d  function = %d", i, j, k);
				DWORD baseClass = _inmw((DWORD_PTR)&pRegPci->BaseClass);
				DWORD subClass = _inmw((DWORD_PTR)&pRegPci->SubClass);
				DWORD progInterface = _inmw((DWORD_PTR)&pRegPci->ProgInterface);
				DWORD subSystVendorID = _inmw((DWORD_PTR)&pRegPci->SubSystVendorID);
				DWORD deviceId = _inmw((DWORD_PTR)&pRegPci->BaseClass);

				//addresses
				wsprintf(szBuffer[cLine++], "base class = %d  subclass = %d  progInterface = %d, subsystVendorID = %d",
					baseClass, subClass, progInterface, subSystVendorID);

				//base class subclass interface
				for (int i = 0; i < PCI_CLASS_TABLE_LEN; i++)
					if (PciClassTable[i].Class == baseClass && PciClassTable[i].SubClass == subClass
						&& PciClassTable[i].ProgIf == progInterface)
					{
						wsprintf(szBuffer[cLine++], "class subclass descriptor = %s progInterface descriptor = %X \n\n",
							PciClassTable[i].ClassDesc, PciClassTable[i].ProgIfDesc);
					}

				//ids
				for (int i = 0; i < PCI_VENTABLE_LEN; i++)
					if (PciVenTable[i].VenId == subSystVendorID)
						wsprintf(szBuffer[cLine++], "vendor id = %d  vendor descriptor = %s ",
							PciVenTable[i].VenId, PciVenTable[i].VenFull);

				for (int i = 0; i < PCI_DEVTABLE_LEN; i++)
					if (PciDevTable[i].VenId == subSystVendorID && PciDevTable[i].DevId == deviceId)
						wsprintf(szBuffer[cLine++], "device id = %d  device descriptor = %s ",
							PciDevTable[i].DevId, PciDevTable[i].ChipDesc);


				///2.7.4
				wsprintf(szBuffer[cLine++], "\n2.7.4\n");
				WORD vendor_id = LOWORD(readDWORD(i, j, k, 0));
				WORD device_id = HIWORD(readDWORD(i, j, k, 0));

				if (vendor_id != 0xFFFF)
				{
					wsprintf(szBuffer[cLine++], "bus = %d  device = %d  function = %d", i, j, k);
					wsprintf(szBuffer[cLine++], "class: %x\n", (HIWORD(readDWORD(i, j, k, 0x02)) << 7) | HIBYTE(LOWORD(i, j, k, 0x02)));
					wsprintf(szBuffer[cLine++], "vendorId = %d\n", vendor_id);

					for (int index = 0; index < PCI_VENTABLE_LEN; index++)
						if (PciVenTable[index].VenId == vendor_id)
							wsprintf(szBuffer[cLine++], "vendor information: %s\n", PciVenTable[index].VenFull);

					for (int index = 0; index < PCI_DEVTABLE_LEN; index++)
						if (PciDevTable[index].DevId == device_id)
							wsprintf(szBuffer[cLine++], "chip descriptor: %s\n", PciDevTable[index].ChipDesc);
				}

				wsprintf(szBuffer[cLine++], "--------------------------------------------------");
				wsprintf(szBuffer[cLine++], "\n\n\n\n\n");
			}

	// Display the messages
	DisplWindow(hWnd);

	HwClose();
	return 0;
}
