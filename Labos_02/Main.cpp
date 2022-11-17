#include "thread.h"
#include "threadovi.h"

HANDLE hNit;


void Zadatak1() {
	hNit = kreirajThread();
	cekajThread(hNit);
	zatvoriThread(hNit);
	int result = vratiRezultat();
	printf("%d", result);
}

void Zadatak2() {
	inicijalizacija();
	kreirajThreadove();

	IspisMatrice(a);
	IspisMatrice(b);
	IspisMatrice(c);

	zatvori();
}

int  main(void) {
	//Zadatak1();
	Zadatak2();
}

