#include <windows.h>
#include <process.h>
#include <stdio.h>

#define VEL_SPR 10
#define BR_TH 10

HANDLE pun;
HANDLE prazan;
HANDLE brava;

int ulaz = 0;
int izlaz = 0;
int spremnik[VEL_SPR];
int nKamiona, nRadnika;
HANDLE niti[BR_TH];

/* 
   ispisuje + za indeks u nizu s kojeg je  potrosac netom procitao podatak
   ispisuje * za indeks koji ima popunjeno mjesto 
   ispisuje 0 za prazno mjesto otprije
*/
void IspisiSpremnik()
{
	int i;
	for(i = 0; i < VEL_SPR; i++) 
	{
		if(spremnik[i] == 0) {
			putchar('0');
		}
		else if(spremnik[i] == 1) {
			putchar('*');
		}
		else { 
			putchar('+');
			spremnik[i] = 0;
		}
	}
	printf("\t");
}

void dodaj(int data)
{
	spremnik[ulaz] = data;
	ulaz = (ulaz + 1) % VEL_SPR;
}

int uzmi()
{
	int data;
	data = spremnik[izlaz];
	spremnik[izlaz] = -1;
	izlaz = (izlaz + 1) % VEL_SPR;
	return data;
}

int produciraj() 
{
	int i, j, k, z;
	for(i=0; i < 10; i++)		
		for(j=0; j < 10; j++)
			for(k=0; k < 10; k++)
				z = 10;
	return 1;
}

void potrosi(int data) 
{
	int i, j, k, z;
	for(i=0; i < 10; i++)
		for(j=0; j < 10; j++)
			for(k=0; k < 10; k++)
				z = 10;
}

unsigned int WINAPI proizvodjac(PVOID pvParam)
{
	int data;
	while(1){
		data = produciraj();
		WaitForSingleObject(prazan, INFINITE); /* cekaj sve dok je spremnik prazan */
		WaitForSingleObject(brava, INFINITE);  /* zaštita pristupa spremniku */
		dodaj(data);
		IspisiSpremnik();
		puts("Proizvodjac");
		ReleaseSemaphore(brava, 1, NULL);
		ReleaseSemaphore(pun, 1, NULL);
	}
	return 0;
}

unsigned int WINAPI potrosac(PVOID pvParam)
{
	int data;
	while(1){
		WaitForSingleObject(pun, INFINITE);   /* cekaj sve dok je spremnik pun */
		WaitForSingleObject(brava, INFINITE); /* zaštita pristupa spremniku */
		data = uzmi();
		IspisiSpremnik();
		puts("Potrosac");
		ReleaseSemaphore(brava, 1, NULL);  /* oslobodi pristup spremniku*/
		ReleaseSemaphore(prazan, 1, NULL); /* obavijesti proizvodjaca da ima jedno prazno mjesto */
		potrosi(data);
	}
	return 0;
}

void kreirajSemafore(){
	pun = CreateSemaphore(NULL, 0, VEL_SPR,NULL);
	prazan = CreateSemaphore(NULL, VEL_SPR, VEL_SPR, NULL);
	brava = CreateSemaphore(NULL, 1, 1, NULL);
}

void kreirajThreadove(){
	int i;
	HANDLE niti[BR_TH];
	unsigned int nitiID[BR_TH];
	nKamiona = nRadnika = 0;
	printf("Unesite broj kamiona: maximalno %d....", BR_TH/2);
	scanf_s("%d", &nKamiona);
	printf("\n");
	printf("Unesite broj radnika: maximalno %d....", BR_TH/2);
	scanf_s("%d", &nRadnika);
	printf("\n");
	
	/* threadovi proizvodjaci */
	for(i = 0; i < nKamiona; i++) {
		niti[i] = (HANDLE) _beginthreadex(NULL, 0, proizvodjac, NULL, 0, &nitiID[i]);
	}

	/* threadovi potrosaci */
	for(i = 0; i < nRadnika; i++) {
		niti[i + nKamiona] = (HANDLE) _beginthreadex(NULL, 0, potrosac, NULL, 0,  &nitiID[i + nKamiona]);
	}
	WaitForMultipleObjects(nKamiona + nRadnika, niti, TRUE, 2000);
}

void zatvoriSemafore(){
	CloseHandle(pun);
	CloseHandle(prazan);
	CloseHandle(brava);
}

void zatvoriThreadove(){
	int i;
	for(i = 0; i < nKamiona + nRadnika; i++) {
		CloseHandle(niti[i]);
	}
}
