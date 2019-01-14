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
#include "Hw.h"
#include "ATA-ATAPI-e.h"
#include <ctime>

#define NLIN 500								// number of lines in the display window
#define NCOL 240								// number of columns in the display window

// Global variables
char szBuffer[NLIN][NCOL];						// buffer for the window contents
int  cLine;										// number of current line in the display buffer

// Declarations of external functions
void DisplWindow(HWND hWnd);

WORD PCMB;
WORD PCNL;
WORD SCMB;
WORD SCNL;

SATA_PCI_CFG* getPointer(BYTE busNr, BYTE deviceNr, BYTE functionNr)
{
	DWORD64 qwFAddr;
	qwFAddr = PCI_CONFIG_START;
	qwFAddr = (busNr << 20) | (deviceNr << 15) | (functionNr << 12) | qwFAddr;
	return PSATA_PCI_CFG(qwFAddr);
}

DWORD getBaseAddresses(BYTE busNr, BYTE deviceNr, BYTE functionNr, int primary)
{
	SATA_PCI_CFG* pRegPci;
	pRegPci = getPointer(busNr, deviceNr, functionNr);
	if (primary == 1)
		return (LOWORD(_inmdw((DWORD_PTR)&pRegPci->PCNL_BAR)) & 0xFFFC) << 16 | (LOWORD(_inmdw((DWORD_PTR)&pRegPci->PCMD_BAR)) & 0xFFF8);
	if (primary == 0)
		return (LOWORD(_inmdw((DWORD_PTR)&pRegPci->SCNL_BAR)) & 0xFFFC) << 16 | (LOWORD(_inmdw((DWORD_PTR)&pRegPci->SCMD_BAR)) & 0xFFF8);
}

void diagnostic(WORD CMB)
{
	BYTE statusReg;
	BYTE deviceReg;
	BYTE errorReg;
	BYTE LBAMid;

	clock_t begin = clock();
	clock_t end;
	double elapsed_secs;

	while (TRUE)
	{
		statusReg = __inp(CMB + ATA_STATUS);
		if ((statusReg & (STATUS_BSY | STATUS_DRQ)) == 0)
			break;

		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		if (elapsed_secs > 2.5)
		{
			wsprintf(szBuffer[cLine++], "The drive does not respond or it does not exist");
			return;
		}
	}

	deviceReg = __inp(CMB + ATA_DEVICE);
	__outp(CMB + ATA_DEVICE, deviceReg & ~DEVICE_DEV);

	__outp(CMB + ATA_COMMAND, ATA_EXEC_DEVICE_DIAG);
	Sleep(2);

	begin = clock();
	while (TRUE)
	{
		statusReg = __inp(CMB + ATA_STATUS);
		if ((statusReg & STATUS_BSY) == 0)
			break;
		end = clock();

		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		if (elapsed_secs > 6)
		{
			wsprintf(szBuffer[cLine++], "BSY bit does not become 0 after 6s");
			return;
		}
	}
	errorReg = __inp(CMB + ATA_ERROR);
	wsprintf(szBuffer[cLine++], "errorReg = 0x%X", errorReg);

	LBAMid = __inp(CMB + ATA_LBA_MID);
	if (LBAMid == 0x14)
	{
		wsprintf(szBuffer[cLine++], "ATAPI drive");
	}
	else if (LBAMid == 0x00)
	{
		wsprintf(szBuffer[cLine++], "ATA drive");
	}
	else
	{
		wsprintf(szBuffer[cLine++], "drive not present");
	}
}

void identifyDevice(WORD CMB, WORD CNL, int driveNr)
{
	BYTE statusReg;
	BYTE deviceReg;
	BYTE errorReg;
	WORD data[256];

	clock_t begin = clock();
	clock_t end;
	double elapsed_secs;

	while (TRUE)
	{
		statusReg = __inp(CMB + ATA_STATUS);
		if ((statusReg & (STATUS_BSY | STATUS_DRQ)) == 0)
			break;

		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		if (elapsed_secs > 1)
		{
			wsprintf(szBuffer[cLine++], "The drive does not respond or it does not exist");
			return;
		}
	}

	deviceReg = __inp(CMB + ATA_DEVICE);
	if (driveNr == 0)
		__outp(CMB + ATA_DEVICE, deviceReg & ~DEVICE_DEV);
	if (driveNr == 1)
		__outp(CMB + ATA_DEVICE, deviceReg & DEVICE_DEV);

	__outp(CMB + ATA_COMMAND, ATA_ID_DEVICE);

	begin = clock();
	while (TRUE)
	{
		statusReg = __inp(CMB + ATA_STATUS);
		if ((statusReg & STATUS_BSY) == 0)
			break;
		end = clock();

		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		if (elapsed_secs > 1)
		{
			wsprintf(szBuffer[cLine++], "BSY bit does not become 0 after 1s");
			return;
		}
	}

	if ((statusReg & STATUS_DRQ) == 0)
	{
		errorReg = __inp(CMB + ATA_ERROR);
		wsprintf(szBuffer[cLine++], "Error occured, errorReg = 0x%X", errorReg);
		return;
	}

	for (int i = 0; i < 256; i++)
	{
		data[i] = __inpw(CMB + ATA_DATA);
	}

	wsprintf(szBuffer[cLine++], "Number of logical cylinders = %d", (int)data[1]);
	wsprintf(szBuffer[cLine++], "Number of logical headers = %d", (int)data[3]);
	wsprintf(szBuffer[cLine++], "Number of logical sectors = %d", (int)data[6]);

	char c1[21];
	int c = 0;
	for (int i = 10; i <= 19; i++)
	{
		c1[c++] = HIBYTE(data[i]);
		c1[c++] = LOBYTE(data[i]);
	}
	c1[20] = 0;
	wsprintf(szBuffer[cLine++], "Serial number = %s", c1);

	char c2[9];
	c = 0;
	for (int i = 23; i <= 26; i++)
	{
		c2[c++] = HIBYTE(data[i]);
		c2[c++] = LOBYTE(data[i]);
	}
	c2[8] = 0;
	wsprintf(szBuffer[cLine++], "Firmware number = %s", c2);

	char c3[41];
	c = 0;
	for (int i = 27; i <= 46; i++)
	{
		c3[c++] = HIBYTE(data[i]);
		c3[c++] = LOBYTE(data[i]);
	}
	c3[40] = 0;
	wsprintf(szBuffer[cLine++], "Model number = %s", c3);

	DWORD sec28 = data[60] << 16 | data[61];
	wsprintf(szBuffer[cLine++], "Total number of addressable sectors (28-bit LBA addressing) = %X", sec28);
	wsprintf(szBuffer[cLine++], "Total number of addressable sectors (48-bit LBA addressing) = %X",
		data[100] << 48 | data[101] << 32 | data[102] << 16 | data[103]);

	wsprintf(szBuffer[cLine++], "capacity (28-bit LBA addressing) = %X GB", sec28 / 200000);
	wsprintf(szBuffer[cLine++], "capacity (48-bit LBA addressing) = %X GB",
		(data[100] << 48 | data[101] << 32 | data[102] << 16 | data[103]) / 200000);

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

	DWORD addresses;
	addresses = getBaseAddresses(0, 31, 2, 1);
	PCMB = LOWORD(addresses);
	PCNL = HIWORD(addresses);
	wsprintf(szBuffer[cLine], "Primary CMB = %X, CNL = %X", PCMB, PCNL);
	cLine++;

	addresses = getBaseAddresses(0, 31, 2, 0);
	SCMB = LOWORD(addresses);
	SCNL = HIWORD(addresses);
	wsprintf(szBuffer[cLine], "Secondary CMB = %X, CNL = %X", SCMB, SCNL);
	cLine++;
	DisplWindow(hWnd);


	cLine++;
	wsprintf(szBuffer[cLine++], "Primary diagnostic");
	diagnostic(PCMB);
	DisplWindow(hWnd);
	/*
	cLine++;
	wsprintf(szBuffer[cLine++], "Secondary diagnostic");
	diagnostic(SCMB);
	DisplWindow(hWnd);

	cLine++;
	identifyDevice(PCMB, PCNL, 0);
	DisplWindow(hWnd);
	*/
	HwClose();
	return 0;
}
