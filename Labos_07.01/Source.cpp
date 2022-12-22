#include "heap.h"


void funkcijaA() {
	alociraj();
	oslobodi();
	ispis();
}


void funkcijaB() {
	alocirajNaHeapu();
	oslobodiNaHeapu();
	ispis();
}

void main() {
	funkcijaA();
	funkcijaB();
}