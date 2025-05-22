//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct Comanda Comanda;
//typedef struct nod nod;
//typedef struct ListaDubla ListaDubla;
//
//struct Comanda {
//	unsigned int id;
//	char* lansareComanda;
//	char* dataLivrare;
//	char* numeClient;
//	float valoareComanda;
//};
//
//struct nod {
//	Comanda info;
//	nod* prev;
//	nod* next;
//};
//
//struct ListaDubla {
//	nod* prim;
//	nod* ultim;
//};
//
//Comanda creareComanda(unsigned int id, char* lansareComanda, char* dataLivrare, char* numeClient, float valoareComanda) {
//	Comanda c;
//	c.id = id;
//	c.lansareComanda = malloc(sizeof(char) * strlen(lansareComanda) + 1);
//	strcpy(c.lansareComanda, lansareComanda);
//	c.dataLivrare = malloc(sizeof(char) * strlen(dataLivrare) + 1);
//	strcpy(c.dataLivrare, dataLivrare);
//	c.numeClient = malloc(sizeof(char) * strlen(numeClient) + 1);
//	strcpy(c.numeClient, numeClient);
//	c.valoareComanda = valoareComanda;
//
//	return c;
//}
//
//ListaDubla inserareInceput(ListaDubla lista, Comanda c) {
//	nod* nou = malloc(sizeof(nod));
//	nou->info = creareComanda(c.id, c.lansareComanda, c.dataLivrare, c.numeClient, c.valoareComanda);
//	nou->prev = NULL;
//	nou->next = NULL;
//	if (lista.prim == NULL) {
//		lista.prim = nou;
//		lista.ultim = nou;
//	}
//
//	else {
//		nou->next = lista.prim;;
//		lista.prim->prev = nou;
//		lista.prim = nou;
//
//	}
//
//	return lista;
//
//}
//
//ListaDubla inserareFinal(ListaDubla lista, Comanda c) {
//	nod* nou = malloc(sizeof(nod));
//	nou->info = creareComanda(c.id, c.lansareComanda, c.dataLivrare, c.numeClient, c.valoareComanda);
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
//
//	return lista;
//
//}
//
//void TraversareInceput(ListaDubla lista) {
//	nod* aux = lista.prim;
//	while (aux) {
//		printf("%d, %s, %s, %s, %.2f", aux->info.id, aux->info.lansareComanda, aux->info.dataLivrare, aux->info.numeClient, aux->info.valoareComanda);
//
//		printf("\n");
//		aux = aux->next;
//	}
//}
//
//void dezalocare(ListaDubla lista) {
//	nod* aux = lista.prim;
//	while (aux) {
//		free(aux->info.lansareComanda);
//		free(aux->info.dataLivrare);
//		free(aux->info.numeClient);
//		nod* temp = aux->next;
//		free(aux);
//		aux = temp;
//	}
//}
//
//	float MediaComenzilor(ListaDubla lista) {
//		float media = 0;
//		float suma = 0;
//		int contor = 0;
//		nod* aux = lista.prim;
//		while (aux) {
//			suma = suma + aux->info.valoareComanda;
//			contor++;
//			media = suma / contor;
//			aux = aux->next;
//		}
//		return media;
//	}
//	
//	int Contorizare(ListaDubla lista, char* numeClient_nou) {
//		int contor = 0;
//		nod* aux = lista.prim;
//		while (aux) {
//			if (strcmp(aux->info.numeClient, numeClient_nou) == 0) {
//				contor++;
//			}
//			aux = aux ->next;
//		}
//		return contor;
//	}
//
//	Comanda* ComandaAcelasiClient(ListaDubla lista, char* numeClient_nou) {
//		int dim = Contorizare(lista, numeClient_nou);
//		Comanda* vector = (Comanda*)malloc(sizeof(Comanda) * dim);
//		nod* aux = lista.prim;
//		int index = 0;
//		while (aux) {
//			if (strcmp(aux->info.numeClient, numeClient_nou) == 0) {
//				vector[index] = aux->info;
//				index++;
//			}
//			aux = aux->next;
//		}
//
//		return vector;
//	}
//
//
//
//void main() {
//	Comanda c;
//	ListaDubla lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//
//	char liniebuffer[100];
//	char separator[] = ",";
//	char* token;
//
//	FILE* pfile = fopen("Text3.txt", "r");
//
//	while (fgets(liniebuffer, sizeof(liniebuffer), pfile)) {
//		token = strtok(liniebuffer, separator);
//		c.id = atoi(token);
//
//		token = strtok(NULL, separator);
//		c.lansareComanda = (char*)malloc(sizeof(char) * strlen(token) + 1);
//		strcpy(c.lansareComanda, token);
//
//		token = strtok(NULL, separator);
//		c.dataLivrare = (char*)malloc(sizeof(char) * strlen(token) + 1);
//		strcpy(c.dataLivrare, token);
//
//		token = strtok(NULL, separator);
//		c.numeClient = (char*)malloc(sizeof(char) * strlen(token) + 1);
//		strcpy(c.numeClient, token);
//
//		token = strtok(NULL, separator);
//		c.valoareComanda = atof(token);
//
//	
//
//	lista = inserareFinal(lista, c);
//
//	free(c.lansareComanda);
//	free(c.dataLivrare);
//	free(c.numeClient);
//}
//
//	fclose(pfile);
//
//	TraversareInceput(lista);
//	
//
//	printf("Media este:  % .2f", MediaComenzilor(lista));
//
//	int dimensiune = Contorizare(lista, "Madalina");
//	printf("%d \n", dimensiune);
//
//	Comanda* vector = ComandaAcelasiClient(lista, "Madalina");
//
//	for (int i = 0; i < dimensiune; i++) {
//		printf("%d,%s,%s,%s,%.2f \n", vector[i].id, vector[i].lansareComanda, vector[i].dataLivrare, vector[i].numeClient, vector[i].valoareComanda);
//	}
//
//	
//	free(vector);
//
//	dezalocare(lista);
//}