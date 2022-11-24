#include "mutex.h"


HANDLE th;
HANDLE mutex;


void main(){
	mutex = kreirajMutex();
	th = kreirajThread();

	for (int i = 0; i < 2; i++) {
		cekajMutex();
		ispis(1);
		otpustiMutex();
		cekajMutex();
		ispis(2);
		otpustiMutex();

	}
	zatvoriThread(th);
	zatvoriMutex(mutex);

	getchar();
}