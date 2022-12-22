#include <windows.h>
#include <conio.h>
#include <stdio.h>

HANDLE sem1 = NULL;
HANDLE sem2 = NULL;
HANDLE s_hFileMap = NULL;
PVOID pView;
int* inChar;
LONG cnt;

int otvoriMapiranje(){
	s_hFileMap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, TEXT("Spremnik"));
	if(s_hFileMap == NULL)
	{
		printf("pokreni prvo proces koji uzima znak!!!\n");
		return 1;
	}
    pView = MapViewOfFile(s_hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	inChar = (int *) pView;
	sem1 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("Sem1"));
	if(sem1 == NULL)
	{
		printf("pokreni prvo proces koji uzima znak!!!\n");
		return 1;
	}
	sem2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("Sem2"));
	if(sem1 == NULL)
	{
		printf("pokreni prvo proces koji uzima znak!!!\n");
		return 1;
	}
}

void ispisujZnakove(){
	printf("Upisani znakovi su: ");
	do
	{
		WaitForSingleObject(sem2, INFINITE);
		_putch(*inChar);
		ReleaseSemaphore(sem1, 1, &cnt);		
	} while(*inChar != '0');
}

void zatvoriMapiranje(){
	UnmapViewOfFile(pView);
	CloseHandle(s_hFileMap);
	CloseHandle(sem1);
	CloseHandle(sem2);
}
