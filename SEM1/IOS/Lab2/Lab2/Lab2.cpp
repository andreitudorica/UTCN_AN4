// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Hw.h"
#include "ComDef-e.h"
#include <stdio.h>

#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT7 (1<<7)


int _tmain(int argc, _TCHAR* argv[])
{

	char szBuffer[4096 + 1];
	char szMes8[] = "Error at opening the COM1 port\nCode: 0x%08X";
	DWORD dwLastError;

	HANDLE hFile;

	//1
	if (!HwOpen()){
		printf("Driver not installed/working correctly");
	}

	hFile = CreateFile(TEXT("COM1"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		dwLastError = GetLastError();
		printf(szBuffer, szMes8, dwLastError);
		return 2;
	}

	//1
	__outp(LCR, __inp(LCR) | LCR_DLAB);
	while ((__inp(LCR) && LCR_DLAB) == 0);
	//2
	__outp(DLR_LSB, 0x06);
	__outp(DLR_MSB, 0x00);

	//3
	__outp(LCR, __inp(LCR) | LCR_DLAB);
	__outp(LCR, __inp(LCR) & (~BIT3));
	__outp(LCR, __inp(LCR) & (~BIT2));
	__outp(LCR, __inp(LCR) | BIT1);
	__outp(LCR, __inp(LCR) | BIT0);


	//4
	__outp(MCR, __inp(MCR) | BIT0);
	__outp(MCR, __inp(MCR) | BIT1);
	__outp(MCR, __inp(MCR) | BIT3);


	for (int i = 0; i < 8; i++) {
		printf("LCR[%d]: %d\n", i, (LCR & ((byte)1 << i)) != 0);

	}
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("MCR[%d]: %d\n", i, (MCR & ((byte)1 << i)) != 0);


	}


	CloseHandle(hFile);
	HwClose();
	getchar();
	return 0;
}

