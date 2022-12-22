#include <windows.h>
#include <stdio.h>

struct mojHeap{
	HANDLE hp;
	unsigned long upotreba;
	unsigned long maxVel;
};

struct mojHeap nizHeapova[] =   
{
	{NULL,0,0x00000008},
	{NULL,0,0x00000010},
	{NULL,0,0x00000020},
	{NULL,0,0x00000040},
	{NULL,0,0x00000080},
	{NULL,0,0x00000100},
	{NULL,0,0x00000200},
	{NULL,0,0x00000400},
	{NULL,0,0x00000800},
	{NULL,0,0x00001000},
	{NULL,0,0x00002000},
	{NULL,0,0x00004000},
	{NULL,0,0x00008000},								
	{NULL,0,0x00010000},
	{NULL,0,0x00020000},
	{NULL,0,0x00040000},
	{NULL,0,0x00080000},
	{NULL,0,0x00100000},
	{NULL,0,0x00200000},
	{NULL,0,0x00400000},
	{NULL,0,0x00800000},
	{NULL,0,0x01000000},
	{NULL,0,0x02000000},
	{NULL,0,0x04000000},
	{NULL,0,0x08000000},
	{NULL,0,0x10000000},
	{NULL,0,0x20000000},
	{NULL,0,0x40000000},
	{NULL,0,0x7f000000}								
};

void ispisi_heap(void){

	int i, brHeapova;
	struct mojHeap* tmp = NULL;
	
	printf("Ispis heap-a****************************************\n");

	brHeapova = sizeof(nizHeapova) / sizeof(nizHeapova[0]);
	tmp = nizHeapova;

	for(i = 0; i < brHeapova; i++){

		printf("Heap blok indeksa %d velicine %ld koristen %ld puta i njegov handle je %p\n", i+1, 
			   tmp->maxVel, tmp->upotreba, tmp->hp);
		tmp++;
	}

	printf("Kraj ispisa heap-a**********************************\n");
}

struct mojHeap* nadjiHeap(unsigned long vel){

	struct mojHeap* tmp = nizHeapova;
	int brHeapova = sizeof(nizHeapova) / sizeof(nizHeapova[0]);
	
	while(brHeapova--){

		if(vel <= tmp->maxVel){

			if(tmp->hp == NULL){

				tmp->hp = HeapCreate(0, 0, 0);

				if(tmp->hp == NULL){
					return NULL;
				}
			}
			return tmp;
		}
		tmp++;
	}
	return NULL;
}

void* moj_malloc( unsigned long vel ){

	char* tmp = NULL;
	struct mojHeap** pHeapAdr = NULL;
	struct mojHeap* hp = NULL;

	hp = nadjiHeap(vel);

	if(hp == NULL){
		return NULL;
	}

	tmp = (char*) HeapAlloc(hp->hp, 0, hp->maxVel + sizeof(struct mojHeap*));

	if(tmp != NULL){

		hp->upotreba++;

		pHeapAdr = (struct mojHeap**) tmp;
		*pHeapAdr = hp;

		tmp += sizeof(struct mojHeap*);
	}

	return (void*) tmp;
}

void moj_free(void* pAdr)
{
	struct mojHeap* hp = NULL;
	struct mojHeap** pHeapAdr = NULL;
	char* tmp = NULL;

	if(pAdr == NULL)
		return;

	tmp = (char*) pAdr;

	tmp -= sizeof(struct mojHeap*);
	
	pHeapAdr = (struct mojHeap**) tmp;
	hp = *pHeapAdr;

	HeapFree(hp->hp, 0, tmp);
	hp->upotreba--;
	
	if(hp->upotreba == 0){

		HeapDestroy(hp->hp);
		hp->hp = NULL;
	}
}
