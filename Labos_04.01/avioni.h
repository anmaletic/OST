#include <process.h>
#include <windows.h>
#include <stdio.h>

#define sinkronizacija

#define BR_TH 5
HANDLE mtx;
HANDLE hThread[BR_TH];
unsigned int br[BR_TH];

void cekajMutex(){
	WaitForSingleObject(mtx,INFINITE); // ceka dok mutex objekt ne postane signaliziran (bez vlasnistva)
}

void otpustiMutex(){
	ReleaseMutex(mtx); // otpusti vlasnistvo
}

unsigned int WINAPI avioni(PVOID pvParam){
	int *n = (int *)pvParam;
	printf("Avion %d => Kontrolni toranj: Trazim dozvolu za spustanje.\n",*n);
	#ifdef sinkronizacija
	cekajMutex();
	#endif
		printf("Kontrolni toranj => Avion %d: Dozvola odobrena.\n",  *n);
		printf("Avion %d => Kontrolni toranj: Sletio sam na pistu.\n",*n);
		printf("Kontrolni toranj => svima: Pista je slobodna.\n",*n);
	#ifdef sinkronizacija
	otpustiMutex();
	#endif
	return 0;
}



HANDLE kreirajAvione(){
	int i;
	unsigned int dwThread[BR_TH];
	mtx=CreateMutex(NULL, FALSE, NULL);
	for(i = 0; i < BR_TH; i++){
		hThread[i]= (HANDLE) _beginthreadex(NULL, 0, avioni,(PVOID) &dwThread[i], 0, &dwThread[i]);
	}
	#ifdef sinkronizacija
	WaitForMultipleObjects(BR_TH, hThread, TRUE, INFINITE);
	#endif
	return mtx;
}

void zatvoriPistu(HANDLE mutex){
	CloseHandle(mtx);
}

void parkirajAvione(){
	int i;
	for(i=0;i<BR_TH;i++){
		CloseHandle(hThread[i]);
	}
}

