#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "moj_malloc.h"
#define NUM_ELEMS 10000
#define MAX_SIZE 4194304  

char* niz[NUM_ELEMS];
double trajanje;
time_t pocetak, kraj;
//#ifndef MOJ_MALLOC
void alociraj(){
	int i,j;
	
	time(&pocetak);
	printf("Alociram memoriju za %d elemenata...\n", NUM_ELEMS);
	for(i = 0; i < NUM_ELEMS;i++)
	{
		int size = rand() % MAX_SIZE;
		niz[i] = (char*) malloc(size);
	}
	printf("Alociranje zavrseno!\n");
}

void oslobodi(){
	int i,j;
	printf("Oslobadjam memoriju!\n");
	for(j = 0; j < 50; j++)
	{
		for(i = 0; i < NUM_ELEMS/2;i++)
		{ 
			free(niz[i]);
		}
		
		for(i = 0; i < NUM_ELEMS/2;i++)
		{
			int size = rand() % MAX_SIZE;
			niz[i] = (char*) malloc(size);
		}
		for(i = NUM_ELEMS/2; i < NUM_ELEMS;i++)
		{
			free(niz[i]);
		}
		
		for(i = NUM_ELEMS/2; i < NUM_ELEMS;i++)
		{
			int size = rand() % MAX_SIZE;
			niz[i] = (char*) malloc(size);
		}
	}
		/*for(i = 0; i < NUM_ELEMS;i++)
		{
			free(niz[i]);
		}*/
	printf("Oslobadjanje memorije zavrseno!\n");
}

//#else


void alocirajNaHeapu(){
	int i;
	time(&pocetak);
	printf("Alociram memoriju za %d elemenata...\n", NUM_ELEMS);
	for(i = 0; i < NUM_ELEMS;i++)
	{
		int size = rand() % MAX_SIZE; 
		niz[i] = (char*) moj_malloc(size);
	}
	printf("Alociranje zavrseno!\n");
}

void oslobodiNaHeapu(){
	int i,j;
	printf("Oslobadjam memoriju!\n");
	for(j = 0; j < 50; j++)
	{
		for(i = 0; i < NUM_ELEMS/2;i++)
		{
			moj_free(niz[i]);
		}
		for(i = 0; i < NUM_ELEMS/2;i++)
		{
			int size = rand() % MAX_SIZE;
			niz[i] = (char*) moj_malloc(size);
		}
		for(i = NUM_ELEMS/2; i < NUM_ELEMS;i++)
		{
			moj_free(niz[i]);
		}
		for(i = NUM_ELEMS/2; i < NUM_ELEMS;i++)
		{
			int size = rand() % MAX_SIZE;
			niz[i] = (char*) moj_malloc(size);
		}
	}	
	printf("Oslobadjanje memorije zavrseno!\n");
}

void ispis(){
	time(&kraj);
	trajanje = difftime(kraj, pocetak);
	printf("\n\nTRAJALO JE: %.0lf sekundi.\n\n", trajanje);
}

//#endif