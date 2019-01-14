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
#include "SetupAPI.h"
#include "hidsdi.h"


#define NLIN 500								// number of lines in the display window
#define NCOL 240								// number of columns in the display window

// Global variables
char szBuffer[NLIN][NCOL];						// buffer for the window contents
int  cLine;										// number of current line in the display buffer

// Declarations of external functions
void DisplWindow(HWND hWnd);


void displayHIDStrings(HWND hWnd){
	struct _GUID GUID;
	HidD_GetHidGuid(&GUID);

	HANDLE PnPHandle;
	PnPHandle = SetupDiGetClassDevs(&GUID, NULL, NULL,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (PnPHandle == INVALID_HANDLE_VALUE){
		wsprintf(szBuffer[cLine++], "ERROR WHILE OBTAINING THE INFORMATION RELATED TO HID DEVICES");
	}
	else {
		for (int deviceNo = 0; deviceNo < 20; deviceNo++){
			SP_DEVICE_INTERFACE_DATA interfaceData;
			interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
			if (SetupDiEnumDeviceInterfaces(PnPHandle, NULL, &GUID, deviceNo, &interfaceData) != TRUE){
				if (GetLastError() == ERROR_NO_MORE_ITEMS){
					wsprintf(szBuffer[cLine++], "NO MORE ITEMS, BREAKING THE LOOP");
					break;
				}
			}
			else {
				DWORD bufferSize;
				SetupDiGetDeviceInterfaceDetail(PnPHandle, &interfaceData, NULL, 0, &bufferSize, NULL);
				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER){
					PSP_DEVICE_INTERFACE_DETAIL_DATA_A detailInterfaceData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)malloc(bufferSize);
					detailInterfaceData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
					BOOL isSetupSuccessful = SetupDiGetDeviceInterfaceDetail(PnPHandle, &interfaceData, detailInterfaceData, bufferSize, &bufferSize, NULL);
					if (isSetupSuccessful != TRUE){
						free(detailInterfaceData);
						wsprintf(szBuffer[cLine++], "INVALID ALLOCATION");

					}
					else {
						HANDLE fileHandle = CreateFile(detailInterfaceData->DevicePath,
							GENERIC_READ | GENERIC_WRITE,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, 0, NULL);
						if (fileHandle == INVALID_HANDLE_VALUE){
							fileHandle = CreateFile(detailInterfaceData->DevicePath,
								0, FILE_SHARE_READ | FILE_SHARE_WRITE,
								NULL, OPEN_EXISTING, 0, NULL);
							if (fileHandle == INVALID_HANDLE_VALUE) {
								wsprintf(szBuffer[cLine++], "INVALID HANDLE VALUE");
								free(detailInterfaceData);
							}
							else {
								char identifierString[256];
								HidD_GetProductString(fileHandle, identifierString, sizeof(identifierString));
								free(detailInterfaceData);
								wsprintf(szBuffer[cLine++], "%ls", identifierString);
								CloseHandle(fileHandle);
							}
						}
						else {
							char identifierString[256];
							HidD_GetProductString(fileHandle, identifierString, sizeof(identifierString));
							free(detailInterfaceData);
							wsprintf(szBuffer[cLine++], "%ls", identifierString);
							CloseHandle(fileHandle);
						}
					}
				}
			}
		}
		SetupDiDestroyDeviceInfoList(PnPHandle);
	}
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


	// Erase the display buffer and the window contents
	for (i = 0; i < NLIN; i++) {
		memset (szBuffer[i], ' ', NCOL);
	}
	cLine = 1;

	// Copy the start message into the display buffer and display the message
	wsprintf(szBuffer[cLine], szMes1);
	cLine += 2;
	DisplWindow(hWnd);

//--------------------------------------------------------------------
// To be completed with the application's code
//--------------------------------------------------------------------

	displayHIDStrings(hWnd);
	// Display the messages
	DisplWindow(hWnd);
	return 0;
}
