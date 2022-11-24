#include "mutex.h"




HANDLE m1;
HANDLE m2;


void Zadatak1()
{
	kreirajMutexe();
	zatvoriMutexe();
}

void Zadatak2()
{
	m1 = kreirajMutex();
	m2 = kreirajMutex();
}

void main()
{
	//Zadatak1();
	Zadatak2();
}