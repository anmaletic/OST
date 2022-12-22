#include <process.h>
#include <windows.h>
#include <stdio.h>

#define BR_TH 2
#define MAX_N 30

//#define sinkronizacija

HANDLE hSem1;
HANDLE hSem2;
HANDLE Threadovi[2];
int Brojac = 1;

unsigned int WINAPI IspisNeparnog(PVOID pvParam){
	int kraj = 0;
	do{
		#ifdef sinkronizacija
		WaitForSingleObject(hSem1, INFINITE);
		#endif
		printf("Neparni broj je %d\n", Brojac);
		Brojac++;
		#ifdef sinkronizacija
		ReleaseSemaphore(hSem2, 1, NULL);
		#endif
		if(Brojac >= MAX_N)
			kraj = 1;
	}while(!kraj);
	return 0;
}

unsigned int WINAPI IspisParnog(PVOID pvParam){
	int kraj = 0;
	do{
		#ifdef sinkronizacija
		WaitForSingleObject(hSem2, INFINITE);
		#endif
		printf("Parni broj je %d\n", Brojac);
		Brojac++;
		if(Brojac >= MAX_N)
			kraj = 1;
		#ifdef sinkronizacija
		ReleaseSemaphore(hSem1, 1, NULL);
		#endif
	}while(!kraj);
	return 0;
}

void kreirajSemafore(){
	hSem1 = CreateSemaphore(NULL,0,1,NULL);
	hSem2 = CreateSemaphore(NULL, 1, 1, NULL);
}

void kreirajThreadove(){
	unsigned int threadID[BR_TH];
	Threadovi[0]=(HANDLE) _beginthreadex(NULL, 0, IspisNeparnog, NULL, 0, &threadID[0]);
	Threadovi[1]=(HANDLE) _beginthreadex(NULL, 0, IspisParnog, NULL, 0, &threadID[1]);
	WaitForMultipleObjects(BR_TH, Threadovi, TRUE, INFINITE);
}

void zatvoriSemafore(){
		CloseHandle(hSem1);
		CloseHandle(hSem2);
	}	

void zatvoriThreadove(){
		CloseHandle(Threadovi[0]);
		CloseHandle(Threadovi[1]);
	}	