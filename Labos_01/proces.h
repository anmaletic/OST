#include <windows.h>
#include <tchar.h>

STARTUPINFO si; 

PROCESS_INFORMATION kreirajProces(PROCESS_INFORMATION pi){
	LPTSTR szImePrograma = _tcsdup(TEXT("Notepad")); 
	si.cb = sizeof(si);
	ZeroMemory(&si, sizeof(si)); 
	CreateProcess(NULL, szImePrograma, NULL, NULL, FALSE, 0,  NULL, NULL, &si, &pi); 
	return pi;
}

void zatvoriProces(PROCESS_INFORMATION pi){
	CloseHandle(pi.hThread); 
	CloseHandle(pi.hProcess); 
}

void cekajProces(PROCESS_INFORMATION pi){
	WaitForSingleObject(pi.hProcess, INFINITE); 
}
