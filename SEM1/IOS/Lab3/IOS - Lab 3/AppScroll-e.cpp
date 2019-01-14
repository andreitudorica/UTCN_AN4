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

#include <windows.h>
#include <iostream>
#include "Hw.h"
#include "PCI-e.h"
#include "PCI-vendor-dev.h"

#define NLIN 500								// number of lines in the display window
#define NCOL 240								// number of columns in the display window
#define TOTAL_BUS_NUMBER  15
#define  TOTAL_DEVICE_NUMBER  31
#define TOTAL_FUNCTION_NUMBER  7
// Global variables
char szBuffer[NLIN][NCOL];						// buffer for the window contents
int  cLine;										// number of current line in the display buffer



// Declarations of external functions
void DisplWindow(HWND hWnd);

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


PPCI_CONFIG0 getConfigurationHeader(BYTE bus, BYTE deviceNumber, BYTE function){

	DWORD64 qwAddr; 
	qwAddr = PCI_CONFIG_START;
	DWORD64 shiftedBus = bus << 20;
	DWORD64 shiftedDeviceNumber = deviceNumber << 15;
	DWORD64 shiftedFunction = function << 12;
	return PPCI_CONFIG0(qwAddr | shiftedBus | shiftedDeviceNumber | shiftedFunction);
}

DWORD getPCICompatible(BYTE busNumber, BYTE deviceNumber, BYTE function, DWORD doubleWordNumber){

	DWORD dwordRequestStructure = 1 << 31;
	dwordRequestStructure |= busNumber << 16;
	dwordRequestStructure |= deviceNumber << 11;
	dwordRequestStructure |= function << 8;
	dwordRequestStructure |= doubleWordNumber << 2;

	__outpdw(PCI_CONFIG_ADR, dwordRequestStructure);
	DWORD data = (__inpdw(PCI_CONFIG_DATA));

	return data;
}


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
		
	for (BYTE i = 0; i < TOTAL_BUS_NUMBER; i++){
		for (BYTE j = 0; j < TOTAL_DEVICE_NUMBER; j++){
			for (BYTE k = 0; k < TOTAL_FUNCTION_NUMBER; k++){
				PPCI_CONFIG0 configurationHeader = getConfigurationHeader(i, j, k);
				if (_inmw((DWORD_PTR)&configurationHeader->VendorID) != 0xFFFF){
					BYTE baseClass = _inm((DWORD_PTR)&configurationHeader->BaseClass);
					BYTE subClass = _inm((DWORD_PTR)&configurationHeader->SubClass);
					BYTE programmingInterface = _inm((DWORD_PTR)&configurationHeader->ProgInterface);
					WORD subSystemVendorId = _inmw((DWORD_PTR)&configurationHeader->SubSystVendorID);
					WORD subSystemID = _inmw((DWORD_PTR)&configurationHeader->SubSystVendorID);
					for (int o = 0; o < PCI_CLASS_TABLE_LEN; o++){
						if (PciClassTable[o].Class == baseClass && PciClassTable[o].SubClass == subClass && PciClassTable[o].ProgIf == programmingInterface){
							wsprintf(szBuffer[cLine++], "BASE CLASS: %x SUB CLASS: %x PROGRAMMING INTERFACE: %x SUBSYTEM ID: %x SUBSYTEM VENDOR ID: %x", baseClass, subClass, programmingInterface, subSystemID, subSystemVendorId);
							wsprintf(szBuffer[cLine++], "%s %s", PciClassTable[o].ClassDesc, PciClassTable[o].ProgIfDesc);
							cLine++;
						}
					}
				}
			}
		}
	}

	cLine += 2; 
	// 2.7.4 Reading from the configuration header for a devive

	
	for (BYTE busNumber = 0; busNumber < TOTAL_BUS_NUMBER; busNumber++){
		for (BYTE deviceNumber = 0; deviceNumber < TOTAL_DEVICE_NUMBER; deviceNumber++){
			for (BYTE function = 0; function < TOTAL_FUNCTION_NUMBER; function++){

				WORD vendorId = LOWORD(getPCICompatible(busNumber, deviceNumber, function, 0));
				if (vendorId == 0xFFFF) //vendorID == 0xFFFF
					break;
				WORD deviceId = HIWORD(getPCICompatible(busNumber, deviceNumber, function, 0));

				DWORD classRegister = getPCICompatible(busNumber, deviceNumber, function, 2);
				BYTE baseClass = HIBYTE(HIWORD(classRegister));
				BYTE subClass = LOBYTE(HIWORD(classRegister));
				BYTE programmingInterface = HIBYTE(LOWORD(classRegister));

					

				for (int o = 0; o < PCI_CLASS_TABLE_LEN; o++){
					if (PciClassTable[o].Class == baseClass && PciClassTable[o].SubClass == subClass && PciClassTable[o].ProgIf == programmingInterface){
						if (cLine < 500)
							wsprintf(szBuffer[cLine++], "BASE CLASS: %x, SUBCLASS: %x, PROGRAMMING INTERFACE: %x", baseClass, subClass, programmingInterface);
							wsprintf(szBuffer[cLine++], "%s %s", PciClassTable[o].ClassDesc, PciClassTable[o].ProgIfDesc);
							if (PciVenTable[o].VenId == vendorId){
								wsprintf(szBuffer[cLine++], "%s %s", PciVenTable[o].VenShort, PciVenTable[o].VenFull);
							}
							if (PciDevTable[o].VenId == vendorId && PciDevTable[0].DevId == deviceId){
								wsprintf(szBuffer[cLine++], "%s %s", PciDevTable[o].Chip, PciDevTable[o].ChipDesc);
							}
							cLine++;
					}
				}
			}
		}
	}

	// Display the messages
	DisplWindow(hWnd);

	HwClose();
	return 0;
}
