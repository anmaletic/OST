/* Prvi zadatak */

#include <process.h>
#include <windows.h>
#include <stdio.h>

#define sinkronizacija

#define N_MAX 50
#define BR_TH 10
HANDLE mtx;
HANDLE hThread[BR_TH];
int Brojac = 1;

#pragma region Prvi Zadatak

unsigned WINAPI Funkcija1(PVOID pvParam) {
	int* n = (int*)pvParam;
#ifdef sinkronizacija
	WaitForSingleObject(mtx, INFINITE);
#endif
	printf("Funkcija 1 = %d\tThread %d\n", Brojac, *n);
	Brojac++;
#ifdef sinkronizacija
	ReleaseMutex(mtx);
#endif
	return 0;
}

unsigned WINAPI Funkcija2(PVOID pvParam) {
	int i;
	int* n = (int*)pvParam;
#ifdef sinkronizacija
	WaitForSingleObject(mtx, INFINITE);
#endif
	for (i = 0; i < N_MAX; i++) {
		printf("Funkcija 2 = %d\tThread %d\n", Brojac, *n);
		Brojac++;
	}
#ifdef sinkronizacija
	ReleaseMutex(mtx);
#endif
	return 0;
}

HANDLE kreirajMutex() {
	return CreateMutex(NULL, FALSE, NULL);
}

void kreirajMutexe() {
	int i;
	unsigned dwThread[BR_TH];
	mtx = kreirajMutex();
	for (i = 0; i < BR_TH; ) {
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, Funkcija1, (PVOID)&dwThread[i], 0, &dwThread[i]);
		i++;
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, Funkcija2, (PVOID)&dwThread[i], 0, &dwThread[i]);
		i++;
	}
	WaitForMultipleObjects(BR_TH, hThread, TRUE, INFINITE);
}

void zatvoriMutexe() {
	int i;
	for (i = 0; i < BR_TH; i++)
		CloseHandle(hThread[i]);
	CloseHandle(mtx);
}
#pragma endregion


/* Drugi zadatak */

void ispis(int nit){
	int i;
	for(i=0;i<10;i++){
		switch(nit){
		case 1:
				printf("Nit I : i=%d \n",i*1000+1);
				break;
		case 2:
				printf("Nit II : i=%d \n",i*1000+1);
				break;
		}
		
	}
}

void cekajMutex(){
	WaitForSingleObject(mtx,INFINITE); // ceka dok mutex objekt ne postane signaliziran (bez vlasnistva)
}

void otpustiMutex(){
	ReleaseMutex(mtx); // otpusti vlasnistvo
}

DWORD WINAPI novaFunkcija (LPVOID parametriNiti)
{
	int i;
	for(i=0; i<10; i++){
		cekajMutex();
		ispis(2);	
		otpustiMutex();    
	}
	return 0;
}

void zatvoriThread(HANDLE thread){
	CloseHandle(thread);
}
void zatvoriMutex(HANDLE mtx){
	CloseHandle(mtx);
}

HANDLE kreirajThread(){ 
	return CreateThread(NULL,0,novaFunkcija,NULL,0,0);
}



