#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

DWORD dwNitID;
int rez;

struct podaci_s{
		int x;
		int y;
		int z;
		int result;
};

int vratiRezultat(){
	return rez;
}

/* Thread funkcija */
DWORD WINAPI Mnozi(LPVOID pvParam){
	int i, j, k;
	struct podaci_s *Podaci;
	Podaci = (struct podaci_s *) pvParam;
	Podaci->x = 10;
	Podaci->y = 10;
	Podaci->z = 10;
	Podaci->result = 0;
   	printf("Ja sam thread i pocinjem racunati...\n");
	for(i = 1; i <= Podaci->x; i++){
		for(j = 1; j <= Podaci->y; j++){
			for(k = 1; k <= Podaci->z; k++ ){
				Podaci->result = i * j * k;
			}
		} 
	}
	printf("Ja sam thread i upravo sam zavrsio!\n");
	rez=Podaci->result;
	return 0;
}


HANDLE kreirajThread(){
	struct podaci_s Brojevi;
	HANDLE th = CreateThread(NULL, 0, Mnozi, (PVOID)&Brojevi, 0, &dwNitID);
	return th;
}

void cekajThread(HANDLE hNit){
	WaitForSingleObject(hNit, INFINITE);
}

void zatvoriThread(HANDLE hNit){
	CloseHandle(hNit);
}