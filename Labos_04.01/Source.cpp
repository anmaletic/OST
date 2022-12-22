#include "avioni.h"


HANDLE mutex;


void main()
{

	mutex = kreirajAvione();

	zatvoriPistu(mutex);

	parkirajAvione();
}