//--------------------------------------------------------------------
// TUCN, Computer Science Department
// Input/Output Systems and Peripheral Devices
//--------------------------------------------------------------------
// http://users.utcluj.ro/~baruch/en/pages/teaching/inputoutput-systems/laboratory.php
//--------------------------------------------------------------------
// File:		TestCom1DT-e.cpp
// Date:		25.02.2009
// Modified:	05.09.2015
//--------------------------------------------------------------------
// Testing the COM1 serial port
//--------------------------------------------------------------------
// - Application example to illustrate port accesses
// - The MarvinHW driver is used for port accesses
// - The TextOut function is used for displaying the messages
//--------------------------------------------------------------------
// - Win API functions used:
//   CreateFile, GetClientRect, GetDC, GetLastError, MessageBox,
//   ReleaseDC, TextOut
//--------------------------------------------------------------------

#include <windows.h>
#include "Hw.h"
#include "ComDef-e.h"

// Global variables
static char szBuffer[200][120];					// buffer for the window contents
static int  cLine;								// number of current line in the display buffer
static DWORD dwCharH;							// character height
static DWORD dwCharW;							// average character width
static DWORD dwNLin;							// number of lines in the client area
static DWORD dwNCol;							// number of columns in the client area

// Declarations of functions used
void CharSize(HWND hWnd);
void ClientSize(DWORD ClientX, DWORD ClientY);
void DisplWindow(HWND hWnd, int nLin);

//--------------------------------------------------------------------
// Function TestCom1TO
//--------------------------------------------------------------------
//
// Function:	Tests the existence of the COM1 serial port
//
// Parameters:	- Handle to the application window
//
// Returns:		0 - Operation completed successfully
//				1 - Error at initializing the Hw driver
//				2 - Error at opening the COM1 port
//
//--------------------------------------------------------------------

int TestCom1TO(HWND hWnd)
{
	DWORD dwLastError;							// code of last error
	HANDLE hFile;
	RECT  rc;									// structure with coordinates of the client area
	BYTE  byVal;								// value read from port
	BOOL  bSucc;
	int   i;

	char szMes0[] = "Error at initializing the Hw driver\nCode: 0x%08X";
	char szMes1[] = "Testing the COM1 serial port using the MarvinHW driver";
	char szMes2[] = "Serial port with base address 0x%03X";
	char szMes3[] = "Value written to LCR register: 0xAA";
	char szMes4[] = "Value written to LCR register: 0x55";
	char szMes5[] = "Value read from LCR register:  0x%02X";
	char szMes6[] = "The port exists and works correctly";
	char szMes7[] = "The port does not exist or does not work correctly";
	char szMes8[] = "Error at opening the COM1 port\nCode: 0x%08X";

	// Initialize the Hw library
	if (!HwOpen()) {
		dwLastError = GetLastError();
		wsprintf(szBuffer[0], szMes0, dwLastError);
		MessageBox(NULL, szBuffer[0], "HwOpen", MB_ICONSTOP);
		return 1;
	}

	// Open the COM1 port
	hFile = CreateFile("COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		dwLastError = GetLastError();
		wsprintf(szBuffer[0], szMes8, dwLastError);
		MessageBox(NULL, szBuffer[0], "CreateFile", MB_ICONSTOP);
		return 2;
	}

	// Determine the size of characters
	CharSize(hWnd);

	// Compute the number of lines and columns in the client area
	GetClientRect(hWnd, &rc);					// determine the coordinates of the client area
	ClientSize(rc.right, rc.bottom);

	// Erase the display buffer and the window contents
	for (i = 0; i < 200; i++) {
		memset (szBuffer[i], ' ', 120);
	}
	DisplWindow(hWnd, -1);
	cLine = 1;

	// Copy the start message into the display buffer
	wsprintf(szBuffer[cLine], szMes1);
	cLine += 2;

	// Test the COM1 serial port and display the messages
	wsprintf(szBuffer[cLine], szMes2, COM1);
	cLine += 2;
	__outp(COM1+LCR, 0xAA);						// write the value 0xAA to the LCR register
	byVal = __inp(COM1+LCR);					// read the value written
	wsprintf(szBuffer[cLine], szMes3);
	cLine++;
	wsprintf(szBuffer[cLine], szMes5, byVal);	// prepare the message for the value read
	cLine++;
	if (byVal == 0xAA)
		bSucc = TRUE;
	else
		bSucc = FALSE;
	__outp(COM1+LCR, 0x55);						// write the value 0x55 to the LCR register
	byVal = __inp(COM1+LCR);					// read the value written
	wsprintf(szBuffer[cLine], szMes4);
	cLine++;
	wsprintf(szBuffer[cLine], szMes5, byVal);	// prepare the message for the value read
	cLine++;
	if (bSucc && (byVal == 0x55))
		wsprintf(szBuffer[cLine], szMes6);
	else
		wsprintf(szBuffer[cLine], szMes7);
	cLine++;

	// Display the messages
	DisplWindow(hWnd, -1);

	CloseHandle(hFile);
	HwClose();
	return 0;
}

//--------------------------------------------------------------------
// Function CharSize
//--------------------------------------------------------------------
//
// Function:	Determine the height and average width of a character
//
// Parameters:	- Handle to the application window
//
// Returns:		-
//
//--------------------------------------------------------------------

void CharSize(HWND hWnd)
{
	HDC hDc;									// handle to the device context
	TEXTMETRIC tm;								// structure with the display metrics

	hDc = GetDC(hWnd);							// determine the device context
	GetTextMetrics(hDc, &tm);					// determine the display metrics
	dwCharH = tm.tmHeight + tm.tmExternalLeading;
	dwCharW = tm.tmAveCharWidth;
	ReleaseDC(hWnd, hDc);
}

//--------------------------------------------------------------------
// Function ClientSize
//--------------------------------------------------------------------
//
// Function:	Computes the number of lines and columns in the client area
//
// Parameters:	- Width of client area
//				- Height of client area
//
// Returns:		-
//
//--------------------------------------------------------------------

void ClientSize(DWORD ClientX, DWORD ClientY)
{
	dwNLin = (ClientY / dwCharH) - 1;
	dwNCol = (ClientX / dwCharW) - 1;
}

//--------------------------------------------------------------------
// Function DisplWindow
//--------------------------------------------------------------------
//
// Function:	Displays the contents of the application window
//
// Parameters:	- Handle to the application window
//				- Number of the line to be displayed; if nLin = -1, all the
//				  lines up to the current line in the window are displayed
//
// Returns:		-
//
//--------------------------------------------------------------------

void DisplWindow(HWND hWnd, int nLin)
{
	HDC hDc;									// handle to the device context
	int i;

	hDc = GetDC(hWnd);							// determine the device context
	if (nLin == -1) {							// all the lines are displayed
		for (i = 0; i <= cLine; i++) {
			TextOut(hDc, 10, i * dwCharH, szBuffer[i], 120);
		}
	}
	else {										// a single line is displayed
		TextOut(hDc, 10, nLin * dwCharH, szBuffer[nLin], 120);
	}
	ReleaseDC(hWnd, hDc);
}
