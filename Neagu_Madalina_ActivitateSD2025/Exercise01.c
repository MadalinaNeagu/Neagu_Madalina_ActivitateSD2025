//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Proiect Proiect;
//typedef struct nod nod;
//typedef struct ListaDubla ListaDubla;
//
//struct Proiect {
//	unsigned int cod;
//	char* titlu;
//	char* beneficiar;
//	unsigned char nrExecutanti;
//	float buget;
//
//};
//
//Proiect creareProiect(unsigned int cod, char* titlu, char* beneficiar, unsigned char nrExecutanti, float buget) {
//	Proiect p;
//	p.cod = cod;
//	p.titlu = (char*)malloc(sizeof(char) * strlen(titlu) + 1);
//	strcpy(p.titlu, titlu);
//	p.beneficiar = (char*)malloc(sizeof(char) * strlen(beneficiar) + 1);
//	strcpy(p.beneficiar, beneficiar);
//	p.nrExecutanti = nrExecutanti;
//	p.buget = buget;
//
//	return p;
//}
//
//struct nod {
//	Proiect info;
//	nod* next;
//	nod* prev;
//};
//
//struct ListaDubla {
//	nod* prim;
//	nod* ultim;
//};
//
//ListaDubla inserareInceput(ListaDubla lista, Proiect p) {
//	nod* nou = (nod*)malloc(sizeof(nod));
//	nou->info = creareProiect(p.cod, p.titlu, p.beneficiar, p.nrExecutanti, p.buget);
//	nou->next = NULL;
//	nou->prev = NULL;
//	if (lista.prim == NULL) {
//		lista.prim = nou;
//		lista.ultim = nou;
//	}
//	else {
//		nou->next = lista.prim;
//		lista.prim->prev = nou;
//		lista.prim = nou;
//	}
//
//	return lista;
//}
//
//
//ListaDubla inserareFinal(ListaDubla lista, Proiect p) {
//	nod* nou = (nod*)malloc(sizeof(nod));
//	nou->info = creareProiect(p.cod, p.titlu, p.beneficiar, p.nrExecutanti, p.buget);
//	nou->next = NULL;
//	nou->prev = NULL;
//	if (lista.prim == NULL) {
//		lista.prim = nou;
//		lista.ultim = nou;
//	}
//	else {
//		nou->prev = lista.ultim;
//		lista.ultim->next = nou;
//		lista.ultim = nou;
//	}
//
//	return lista;
//}
//
//void afisare(ListaDubla lista) {
//	if (lista.prim) {
//		nod* aux = lista.prim;
//		while (aux) {
//			printf("%d,%s,%s,%d,%.2f \n", aux->info.cod, aux->info.titlu, aux->info.beneficiar, aux->info.nrExecutanti, aux->info.buget);
//			aux = aux->next;
//		}
//	}
//	else {
//		printf("Lista este goala");
//	}
//	
//}
//
//void dezalocare(ListaDubla lista) {
//	nod* aux = lista.prim;
//	if (lista.prim != NULL) {
//		while (aux) {
//			nod* temp = aux->next;
//			free(aux->info.titlu);
//			free(aux->info.beneficiar);
//			free(aux);
//			aux = temp;
//		}
//
//	}
//}
//
//float FondInvestitii(ListaDubla lista,char* beneficiarnou) {
//	float suma = 0;
//	nod* aux = lista.prim;
//	while (aux) {
//		if (strcmp(aux->info.beneficiar, beneficiarnou) == 0) {
//			suma = suma + aux->info.buget;
//
//		}
//		aux = aux->next;
//	}
//	return suma;
//
//
//}
//
//void ModificaBuget(ListaDubla lista, float procent, int dim, int* cod) {
//	for (int i = 0; i < dim; i++) {
//		nod* aux = lista.prim;
//		while (aux) {
//			if (cod[i] == aux->info.cod) {
//				aux->info.buget = procent * aux->info.buget;
//			}
//			aux = aux->next;
//		}
//	}
//}
//
//int Contorizare(ListaDubla lista, float buget) {
//	int contor = 0;
//	nod* aux = lista.prim;
//	while (aux) {
//		if (aux->info.buget >= buget) {
//			contor++;
//
//		}
//		aux = aux->next;
//	}
//	return contor;
//}
//
//Proiect* ProiectePesteBuget(ListaDubla lista, float buget) {
//	int dim = Contorizare(lista, buget);
//	Proiect* vector = (Proiect*)malloc(sizeof(Proiect) * dim);
//	nod* aux = lista.prim;
//	int index = 0;
//	while (aux) {
//		if (aux->info.buget >= buget) {
//			vector[index] = aux->info;
//			index++;
//			}
//		aux = aux->next;
//	}
//	return vector;
//}
//
//void main() {
//	Proiect p;
//	ListaDubla lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//
//	char linieBuffer[100];
//	char separator[] = ",";
//	char* token;
//
//	FILE* f = fopen("Text2.txt", "r");
//
//	while (fgets(linieBuffer, 100, f)) {
//		token = strtok(linieBuffer, separator);
//		p.cod = atoi(token);
//
//		token = strtok(NULL, separator);
//		p.titlu = (char*)malloc(sizeof(char) * strlen(token) + 1);
//		strcpy(p.titlu, token);
//
//
//		token = strtok(NULL, separator);
//		p.beneficiar = (char*)malloc(sizeof(char) * strlen(token) + 1);
//		strcpy(p.beneficiar, token);
//
//		token = strtok(NULL, separator);
//		p.nrExecutanti = atoi(token);
//
//		token = strtok(NULL, separator);
//		p.buget = atof(token);
//
//		lista = inserareInceput(lista,p);
//
//	
//	}
//
//	fclose(f);
//
//	afisare(lista);
//
//	printf("%.2f\n",FondInvestitii(lista, "Madalina"));
//
//	int coduri[2] = { 35,12 };
//	ModificaBuget(lista, 0.5, 2, coduri);
//
//	afisare(lista);
//
//	int dimensiune = Contorizare(lista, 100000);
//	printf("%d \n", dimensiune);
//
//	Proiect* vector = ProiectePesteBuget(lista, 100000);
//
//	for (int i = 0; i < dimensiune; i++) {
//		printf("%d,%s,%s,%d,%.2f \n", vector[i].cod, vector[i].titlu, vector[i].beneficiar, vector[i].nrExecutanti, vector[i].buget);
//	}
//
//	
//	free(vector);
//
//	dezalocare(lista);
//
//
//}