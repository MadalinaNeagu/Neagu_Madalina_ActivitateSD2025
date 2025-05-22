//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
//#include <string.h>
//
//typedef struct Farmacie Farmacie;
//typedef struct ListaDubla ListaDubla;
//typedef struct nod nod;
//
//struct Farmacie {
//	char* denumire;
//	float suprafata;
//	unsigned char nrAngajati;
//	char* programLucru;
//};
//
//struct ListaDubla {
//	nod* prim;
//	nod* ultim;
//};
//
//struct nod {
//	Farmacie info;
//	nod* next;
//	nod* prev;
//};
//
//Farmacie creareFarmacie(char* denumire, float suprafata, unsigned char nrAngajati, char* programLucru) {
//	Farmacie f;
//	f.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
//	strcpy(f.denumire, denumire);
//	f.suprafata = suprafata;
//	f.nrAngajati = nrAngajati;
//	f.programLucru = (char*)malloc(sizeof(char) * strlen(programLucru) + 1);
//	strcpy(f.programLucru, programLucru);
//
//	return f;
//}
//
//ListaDubla inserareInceput(ListaDubla lista, Farmacie f) {
//	nod* nou = (nod*)malloc(sizeof(nod));
//	nou->info = creareFarmacie(f.denumire, f.suprafata, f.nrAngajati, f.programLucru);
//	nou->next = NULL;
//	nou->prev = NULL;
//	if (lista.prim == NULL) {
//		lista.prim = nou;
//		lista.ultim = nou;
//	}
//	else {
//		nou->next = lista.prim;
//		lista.prim ->prev = nou;
//		lista.prim = nou;
//
//	}
//	return lista;
//}
//
//ListaDubla inserareFinalt(ListaDubla lista, Farmacie f) {
//	nod* nou = (nod*)malloc(sizeof(nod));
//	nou->info = creareFarmacie(f.denumire, f.suprafata, f.nrAngajati, f.programLucru);
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
//
//	}
//	return lista;
//}
//
//void afisare(ListaDubla lista) {
//	if (lista.prim) {
//		nod* aux = lista.prim;
//		while (aux) {
//			printf("%s,%.2f,%u,%s \n", aux->info.denumire, aux->info.suprafata, aux->info.nrAngajati, aux->info.programLucru);
//			aux = aux->next;
//		}
//
//	}
//		else {
//			printf("Lista este goala");
//	}
//}
//
//void dezalocare(ListaDubla lista) {
//	if (lista.prim) {
//		nod* aux = lista.prim;
//		while (aux) {
//			free(aux->info.denumire);
//			free(aux->info.programLucru);
//			nod* temp = aux->next;
//			free(aux);
//			aux = temp;
//		}
//	}
//}
//
//int NrFarmacii(ListaDubla lista, char* ora) {
//	int contor = 0;
//	nod* aux = lista.prim;
//	while (aux) {
//		if (strcmp(aux->info.programLucru,ora)==0) {
//			contor++;
//		}
//		aux = aux->next;
//	}
//	return contor;
//}
//
//void main() {
//	Farmacie f;
//	ListaDubla lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//
//	char linieBuffer[100];
//	char separator[] = ",";
//	char* token;
//
//	FILE* fisier = fopen("Text5.txt", "r");
//
//	while (fgets(linieBuffer, sizeof(linieBuffer), fisier)) {
//		token = strtok(linieBuffer, separator);
//		f.denumire = (char*)malloc(sizeof(char) * strlen(token) + 1);
//		strcpy(f.denumire, token);
//
//		token = strtok(NULL, separator);
//		f.suprafata = atof(token);
//
//		token = strtok(NULL, separator);
//		f.programLucru = (char*)malloc(sizeof(char) * strlen(token) + 1);
//		strcpy(f.programLucru, token);
//
//		token = strtok(NULL, separator);
//		f.nrAngajati = atoi(token);
//
//		
//
//		lista = inserareInceput(lista, f);
//	}
//
//	fclose(fisier);
//
//	afisare(lista);
//
//	printf("%d \n", NrFarmacii(lista, "16"));
//
//}
