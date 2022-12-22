#include <process.h>
#include <windows.h>
#include <stdio.h>

#define sinkronizacija

#define BR_TH 5
HANDLE semafor;
HANDLE hThread[BR_TH];

unsigned int cekajSemafor(){
	return WaitForSingleObject(semafor, INFINITE);
}

void otpustiSemafor(){
	ReleaseSemaphore(semafor, 0, NULL);
}

unsigned int WINAPI avioni(PVOID pvParam){
	int *n = (int *)pvParam;
	printf("Avion %d => Kontrolni toranj: Trazim dozvola za spustanje.\n",*n);
	#ifdef sinkronizacija
	if(cekajSemafor()==WAIT_OBJECT_0){
		printf("Avion %d => Kontrolni toranj: Cekam dozvolu za spustanje.\n",*n);
	}
	#endif
		printf("Kontrolni toranj => Avion %d: Dozvola odobrena.\n",  *n);
		printf("Avion %d => Kontrolni toranj: Sletio sam na pistu.\n",*n);
		printf("Kontrolni toranj => svima: Pista je slobodna.\n",*n);
	#ifdef sinkronizacija
	otpustiSemafor();
	#endif
	return 0;
}

void kreirajAvioneBin(){
	int i;
	unsigned int dwThread[BR_TH];
	semafor=CreateSemaphore(NULL,0,1,NULL);
	for(i = 0; i < BR_TH; i++){
		hThread[i]= (HANDLE) _beginthreadex(NULL, 0, avioni,(PVOID) &dwThread[i], 0, &dwThread[i]);
	}
	WaitForMultipleObjects(BR_TH, hThread, TRUE, INFINITE);
}

void kreirajAvione(){
	int i;
	unsigned int dwThread[BR_TH];
	semafor=CreateSemaphore(NULL,6,5,NULL);
	for(i = 0; i < BR_TH; i++){
		hThread[i]= (HANDLE) _beginthreadex(NULL, 0, avioni,(PVOID) &dwThread[i], 0, &dwThread[i]);
	}
	WaitForMultipleObjects(BR_TH, hThread, TRUE, INFINITE);
}

void zatvoriPistu(){
	CloseHandle(semafor);
}

void parkirajAvione(){
	int i;
	for(i=0;i<BR_TH;i++){
		CloseHandle(hThread[i]);
	}
}

