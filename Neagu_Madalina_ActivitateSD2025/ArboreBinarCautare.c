#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Rezervare Rezervare;
typedef struct nod nod;

struct Rezervare {
	unsigned int id;
	char* hotel;
	unsigned char nrCamere;
	char* nume;
	float suma;
};


Rezervare creareRezervare(unsigned int id, char* hotel, unsigned char nrCamere, char* nume, float suma) {
	Rezervare r;
	r.id = id;
	r.hotel = (char*)malloc(sizeof(char) * (strlen(hotel) + 1));
	strcpy(r.hotel, hotel);
	r.nrCamere = nrCamere;
	r.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(r.nume, nume);
	r.suma = suma;

	return r;
}

struct nod {
	Rezervare info;
	nod* stang;
	nod* drept;
};

nod* creareNod(Rezervare r, nod* stang, nod* drept) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareRezervare(r.id, r.hotel, r.nrCamere, r.nume, r.suma);
	nou->stang = stang;
	nou->drept = drept;

	return nou;
}

nod* inserareArb(nod* rad, Rezervare r) {
	if (rad) {
		if (r.id < rad->info.id) {
			rad->stang = inserareArb(rad->stang, r);
		}
		else if (r.id > rad->info.id) {
			rad->drept = inserareArb(rad->drept, r);
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(r, NULL, NULL);
	}
	return rad;
}


void preordine(nod* rad) {
	if (rad) {
		printf("%u %s %u %s %.2f \n", rad->info.id, rad->info.hotel, rad->info.nrCamere, rad->info.nume, rad->info.suma);
		preordine(rad->stang);
		preordine(rad->drept);
	}
}

void inordine(nod* rad) {
	if (rad) {

		inordine(rad->stang);
		printf("%u %s %u %s %.2f \n", rad->info.id, rad->info.hotel, rad->info.nrCamere, rad->info.nume, rad->info.suma);
		inordine(rad->drept);
	}
}

void postordine(nod* rad) {
	if (rad) {

		postordine(rad->stang);
		postordine(rad->drept);
		printf("%u %s %u %s %.2f \n", rad->info.id, rad->info.hotel, rad->info.nrCamere, rad->info.nume, rad->info.suma);
	}
}

void dezalocare(nod* rad) {
	if (rad) {
		nod* ArbStang = rad->stang;
		nod* ArbDrept = rad->drept;
		free(rad->info.nume);
		free(rad->info.hotel);
		free(rad);
		dezalocare(ArbStang);
		dezalocare(ArbDrept);

	}
}

int sumaCamereFrunze(nod* rad) {
	int suma = 0;
	if (rad) {
		if (rad->stang == NULL && rad->drept == NULL) {
			suma += rad->info.nrCamere;
		}
		suma += sumaCamereFrunze(rad->stang);
		suma += sumaCamereFrunze(rad->drept);
	}
	return suma;
}

int maxim(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int inaltime(nod* rad) {
	if (rad) {
		return 1 + maxim(inaltime(rad->stang), inaltime(rad->drept));
	}
	else {
		return 0;
	}
}


void main() {
	Rezervare r;
	nod* rad = NULL;

	char liniebuffer[100];
	char sep[] = ",\n";
	char* token;

	FILE* f = fopen("Text7.txt", "r");

	while (fgets(liniebuffer, 100, f)) {
		token = strtok(liniebuffer, sep);
		r.id = atoi(token);

		token = strtok(NULL, sep);
		r.hotel = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(r.hotel, token);

		token = strtok(NULL, sep);
		r.nrCamere = atoi(token);

		token = strtok(NULL, sep);
		r.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(r.nume, token);

		token = strtok(NULL, sep);
		r.suma = atof(token);

		rad = inserareArb(rad, r);
		free(r.hotel);
		free(r.nume);
	}
	fclose(f);

	preordine(rad);
	inordine(rad);

	int sumaCamere = sumaCamereFrunze(rad);
	printf("%d\n", sumaCamere);

	int h = inaltime(rad);
	printf("%d\n", h);


	dezalocare(rad);
}



