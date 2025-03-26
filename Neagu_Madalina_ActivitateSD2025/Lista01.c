#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct nod nod;
typedef struct student student;

struct student {
	float inaltime;
	char* nume;
	int varsta;
};

student crearestudent(float inaltime, const char* nume, int varsta) {
	student s;
	s.inaltime = inaltime;
	s.nume = malloc(sizeof(char) + strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.varsta = varsta;

	return s;

}

struct nod {
	student info;
	nod* next;
};

nod* inserareInceput(nod* adresacap, student s) {
	nod* nou = malloc(sizeof(nod));
	nou->info = crearestudent(s.inaltime, s.nume, s.varsta);
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

nod* inserareFinal(nod* adresacap, student s) {
	nod* nou = malloc(sizeof(nod));
	nou->info = crearestudent(s.inaltime, s.nume, s.varsta);
	nou->next = NULL;

	if (adresacap == NULL) {
		adresacap = nou;
	}

	else {
		nod* aux = adresacap;
		while (aux->next!= NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}

	return adresacap;
}

void afisare(nod* adresacap) {
	nod* aux = adresacap;
	while (aux!= NULL) {
		printf("%.2f, %s, %d \n", aux->info.inaltime, aux->info.nume, aux->info.varsta);
		aux = aux->next;
	}
}

void main() {
	student s = crearestudent(1.62, "Madalina", 22);
	student s1 = crearestudent(1.70, "Marius", 25);
	student s2 = crearestudent(1.67, "Alexandra", 30);
	student s3 = crearestudent(1.74, "Emil", 28);

	nod* adresacap = NULL;
	adresacap = inserareInceput(adresacap, s);
	adresacap = inserareInceput(adresacap, s1);
	adresacap = inserareInceput(adresacap, s2);

	afisare(adresacap);

	adresacap = inserareFinal(adresacap, s3);

	afisare(adresacap);
}