#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Serviciu Serviciu;
typedef struct HT HT;
typedef struct nod nod;

struct Serviciu {
	unsigned int id;
	char* tip;
	char* numeClient;
	float suma;
	unsigned int timpEstimat;
};

Serviciu creareServiciu(unsigned int id, char* tip, char* numeClient, float suma, unsigned int timpEstimat) {
	Serviciu s;
	s.id = id;
	s.tip = (char*)malloc(sizeof(char) * strlen(tip) + 1);
	strcpy(s.tip, tip);
	s.numeClient = (char*)malloc(sizeof(char) * strlen(numeClient) + 1);
	strcpy(s.numeClient, numeClient);
	s.suma = suma;
	s.timpEstimat = timpEstimat;

	return s;
}

struct nod {
	Serviciu info;
	nod* next;
};

struct HT {
	int dim;
	nod** vector;
};

int functieHash(HT tabela, char* numeClient) {
	return numeClient[0] % tabela.dim;
}

int inserareHT(HT tabela, Serviciu s) {
	int poz = 0;
	if (tabela.vector) {
		poz = functieHash(tabela, s.numeClient);
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareServiciu(s.id, s.tip, s.numeClient, s.suma, s.timpEstimat);
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

void afisare(HT tabela) {
	if (tabela.vector) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vector[i]) {
				nod* aux = tabela.vector[i];
				while (aux) {
					printf("%d,%s,%s,%.2f,%d \n", aux->info.id, aux->info.tip, aux->info.numeClient, aux->info.suma, aux->info.timpEstimat);
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
						free(aux->info.tip);
						free(aux->info.numeClient);
						nod* temp = aux->next;
						free(aux);
						aux = temp;
					}
				}
			}


		}
	}

	int NrServicii(HT tabela, char* numeClient) {
		int contor = 0;
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vector[i]) {
				nod* aux = tabela.vector[i];
				while (aux) {
					if (strcmp(aux->info.numeClient, numeClient) == 0) {
						contor++;
					}
					aux = aux->next;
				}
				
			}

		}
		return contor;
	}

	void StergereServiciu(HT tabela) {
		if (tabela.vector) {
			for (int i = 0; i < tabela.dim; i++) {
				if (tabela.vector[i]) {
		
					nod* aux = tabela.vector[i];
					nod* prev = aux;
					if (aux->next == NULL) {
						tabela.vector[i] = NULL;
					}
					while (aux->next) {
						prev = aux;
						aux = aux->next;
					}
					free(aux->info.numeClient);
					free(aux->info.tip);
					free(aux);
					prev->next = NULL;
				}
			}
		}
	}

	int Contorizare(HT tabela, unsigned int timpEstimat) {
		int contor = 0;
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vector[i]) {
				nod* aux = tabela.vector[i];
				while (aux) {
					if (aux->info.timpEstimat >= timpEstimat) {
						contor++;
					}
					aux = aux->next;
				}
			}
		}
		return contor;
	}

	Serviciu* ServiciiPesteTimpEstimat(HT tabela, unsigned int timpEstimat) {
		int dim = Contorizare(tabela, timpEstimat);
		Serviciu* vector = (Serviciu*)malloc(sizeof(Serviciu) * dim);
		int index = 0;
		for (int i = 0; i < tabela.dim; i++) {
			nod* aux = tabela.vector[i];
			while (aux) {
				if (aux->info.timpEstimat >= timpEstimat) {
					vector[index] = aux->info;
					index++;
				}
				aux = aux->next;
			}
		}
		return vector;
	}

	void main() {
		Serviciu s;
		HT tabela;
		tabela.dim = 10;
		tabela.vector = (nod**)malloc(sizeof(nod*) * tabela.dim);
		for (int i = 0; i < tabela.dim; i++) {
			tabela.vector[i] = NULL;
		}

		char linieBuffer[100];
		char separator[] = ",";
		char* token;

		FILE* fisier = fopen("Text4.txt", "r");

		while (fgets(linieBuffer, sizeof(linieBuffer), fisier)) {
			token = strtok(linieBuffer, separator);
			s.id = atoi(token);

			token = strtok(NULL, separator);
			s.tip = (char*)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(s.tip,token);

			token = strtok(NULL, separator);
			s.numeClient = (char*)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(s.numeClient, token);

			token = strtok(NULL, separator);
			s.suma = atof(token);

			token = strtok(NULL, separator);
			s.timpEstimat = atoi(token);

			inserareHT(tabela, s);

			
		}

		fclose(fisier);

		afisare(tabela);

		printf("%d \n", NrServicii(tabela,"Marius"));

		///*StergereServiciu(tabela);

		//afisare(tabela);*/

		printf("%d\n", Contorizare(tabela, 50));

		Serviciu* vector = ServiciiPesteTimpEstimat(tabela, 50);
		for (int i = 0; i < Contorizare(tabela, 50); i++) {
			printf("%d,%s,%s,%.2f,%d \n", vector[i].id, vector[i].tip, vector[i].numeClient, vector[i].suma, vector[i].timpEstimat);
		}

		free(vector);

		dezalocare(tabela);
	}
