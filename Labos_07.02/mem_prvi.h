#include <windows.h>
#include <conio.h>
#include <stdio.h>

HANDLE sem1 = NULL;
HANDLE sem2 = NULL;
HANDLE s_hFileMap = NULL;
int* inChar;
LONG cnt;
PVOID pView;

void kreirajMapiranje(){
	s_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, TEXT("Spremnik"));
    pView = MapViewOfFile(s_hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	inChar = (int *) pView;
	sem1 = CreateSemaphore(NULL, 1, 1, TEXT("Sem1"));
	sem2 = CreateSemaphore(NULL, 0, 1, TEXT("Sem2"));
}

void upisujZnakove(){
	printf("Upisujte znakove: ");
	do
	{
		WaitForSingleObject(sem1, INFINITE);
		*inChar=_getch();
		ReleaseSemaphore(sem2, 1, &cnt);		
	} while(*inChar != '0');
}

void zatvoriMapiranje(){
	UnmapViewOfFile(pView);
	CloseHandle(s_hFileMap);
	CloseHandle(sem1);
	CloseHandle(sem2);
}
