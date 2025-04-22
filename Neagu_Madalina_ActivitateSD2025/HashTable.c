#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include<string.h>

typedef struct abonat abonat;
typedef struct nod nod;
typedef struct HT HT;

struct abonat {
	int cod;
	char* nume;
	char* tip;
	float suma;
};

abonat creareAbonat(int cod, char* nume, char* tip, float suma) {
	abonat a;
	a.cod = cod;
	a.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(a.nume, nume);
	a.tip = (char*)malloc(sizeof(char) * strlen(tip) + 1);
	strcpy(a.tip,tip);
	a.suma = suma;

	return a;
}

void afisareAbonat(abonat a) {
	printf("%d,%s,%s,%.2f \n", a.cod, a.nume, a.tip, a.suma);
}

struct nod {
	abonat info;
	nod* next;
};

struct HT {
	int dim;
	nod** vector;
};

int functieHash(HT tabela, int cod) {
	return cod % tabela.dim;
}

//int functieHash1(HT tabela, char* nume) {
//	return nume[0] % tabela.dim;
//}

int inserareHash(HT tabela, abonat a) {
	int poz = 0;
	if (tabela.vector) {
		poz = functieHash(tabela, a.cod);
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareAbonat(a.cod, a.nume, a.tip, a.suma);
		nou->next = NULL;
		if (tabela.vector[poz] == NULL) {
			tabela.vector[poz] = nou;
		}
		else {
			nod* aux = tabela.vector[poz];
			while (aux->next) {
				aux = aux->next;
			}
			aux->next = nou;
		}
	}

	return poz;
}

void afisareHash(HT tabela) {
	if (tabela.vector) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vector[i]) {
				printf("Pozitia:%d \n", i);
				nod* aux = tabela.vector[i];
				while (aux) {
					afisareAbonat(aux->info);
					aux = aux->next;
				}
			}
		}
	}
}

void dezalocare(HT tabela) {
	if (tabela.vector) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vector[i]) {
				nod* aux = tabela.vector[i];
				while (aux) {
					free(aux->info.nume);
					free(aux->info.tip);
					nod* temp = aux->next;
					free(aux);
					aux = temp;
				}
			}
		}
		free(tabela.vector);
	}
}

void main() {
	abonat a = creareAbonat(123, "Madalina Neagu", "abc", 240.55);
	abonat a1 = creareAbonat(456, " Marius Ghinea", "bcd", 159.66);
	abonat a2 = creareAbonat(789, "Alin Popa", "bgh", 710.5);
	abonat a3 = creareAbonat(765, "Georgescu Mihaela", "klm", 879.05);

	HT tabela;
	tabela.dim = 10;
	tabela.vector = (nod**)malloc(sizeof(nod*) * tabela.dim);
	for (int i = 0; i < tabela.dim; i++) {
		
		tabela.vector[i] = NULL;
	}

	inserareHash(tabela, a);
	inserareHash(tabela, a1);
	inserareHash(tabela, a2);
	inserareHash(tabela, a3);

	afisareHash(tabela);
}