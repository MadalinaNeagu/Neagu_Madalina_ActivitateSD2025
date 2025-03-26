#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include < malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct masina masina;
typedef struct nod nod;

struct masina {
	char* marca;
	float kilometrii;
	int anFabricatie;

};

masina creareMasina(char* marca, float kilometrii, int anFabricatie) {
	masina m;
	m.marca = malloc(sizeof(char) + strlen(marca) + 1);
	strcpy(m.marca, marca);
	m.kilometrii = kilometrii;
	m.anFabricatie = anFabricatie;

	return m;
}

struct nod {
	masina info;
	nod* next;
};

nod* inserareInceput(nod* adresacap, masina m) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareMasina(m.marca, m.kilometrii, m.anFabricatie);
	nou->next = NULL;

	if (adresacap == NULL) {
		adresacap = nou;
	}
	else {
		nou->next = adresacap;
		adresacap = nou;
	}

	return adresacap;
}

nod* inserareFinal(nod* adresacap, masina m) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareMasina(m.marca, m.kilometrii, m.anFabricatie);
	nou->next = NULL;

	if (adresacap == NULL) {
		adresacap = nou;
	}

	else {
		nod* aux = adresacap;
		while (aux->next != NULL) {
			aux = aux->next;

		}

		aux->next = nou;
	}

	return adresacap;
}

void afisare(nod* adresacap) {
	nod* aux = adresacap;
	while (aux != NULL) {
		printf("%s, %.3f, %d \n", aux->info.marca, aux->info.kilometrii, aux->info.anFabricatie);
		aux = aux->next;
	}
}

void main() {
	masina m = creareMasina("Toyota", 12.000, 2012);
	masina m1 = creareMasina("BMW", 15.000, 2024);
	masina m2 = creareMasina("Mercedes", 250.000, 2010);
	masina m3 = creareMasina("Alfa Romeo", 8.000, 2023);


	nod* adresacap = NULL;
	adresacap = inserareFinal(adresacap, m);
	adresacap = inserareFinal(adresacap, m1);
	adresacap = inserareFinal(adresacap, m2);

	afisare(adresacap);

	adresacap = inserareInceput(adresacap, m3);

	afisare(adresacap);

}

