#include <stdio.h>
#include <windows.h>
#include <process.h>

/* N je broj threadova i broj elemenata u jednom retku/stupcu matrice */
#define N 15	

struct Podaci_s{
	int red;
};

/* Matrice */
int a[N][N];
int b[N][N];
int c[N][N];


/* Broj redova i stupaca u matrici */
int n;

int i;

HANDLE hNiti[N];
unsigned int dwNitiID[N];
/* Thread funkcija */
unsigned int WINAPI ZbrojiRedak(PVOID pvPodatak){
	unsigned int dwRezultat = 0;
	int j, red;
	struct Podaci_s *Pod;
	Pod = (struct Podaci_s *) pvPodatak;
	red = Pod->red;
	printf("\nRacunam u %d. threadu!\n", red+1);
	/* Izracun sume jednog retka matrice */
	for(j = 0; j < n; j++){
		c[red][j] = a[red][j] + b[red][j];
	}
	printf("Racunanje u %d. threadu je zavrseno!\n", red+1);
	return(dwRezultat);
}

void IspisMatrice( int mat[][N] ){
	int i, j;
	for(i = 0; i < N; i++){
			for(j = 0; j < N; j++)
				printf("%d ", mat[i][j]);
			printf("\n");
		}
	printf("\n");
}
void inicijalizacija(){
	int i,j;
	n = N;
	/* Inicijalizacija matrica */
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			a[i][j] = 2000;
			b[i][j] = j + 1;
		}
	}
}

void kreirajThreadove(){
	struct Podaci_s Pod[N];
	unsigned int dwNitiID[N];
	for(i = 0; i < N; i++){
		Pod[i].red = i;
		hNiti[i] = (HANDLE) _beginthreadex(NULL, 0, ZbrojiRedak, (PVOID) &Pod[i], 0, &dwNitiID[i]);
	}
	WaitForMultipleObjects(N, hNiti, TRUE, INFINITE);
}

void zatvori(){
	for(i = 0; i < N; i++)
		CloseHandle(hNiti[i]);	
}
