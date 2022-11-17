#include "proces.h"
#include <iostream>
#include <string>


PROCESS_INFORMATION pi;


void main() 
{
	pi = kreirajProces(pi);

	std::cout << "Started process: " << pi.dwProcessId << "\n";

	cekajProces(pi);

	zatvoriProces(pi);


	std::cout << "Closed process: " << pi.dwProcessId;
}
