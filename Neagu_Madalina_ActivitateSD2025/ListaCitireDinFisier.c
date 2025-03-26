#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct student student;
typedef struct nod nod;

struct student {
	char* nume;
	float nota;
	int grupa;
	char* materie;
};

student creareStudent(char* nume, float nota, int grupa, char* materie) {
	student s;
	s.nume = malloc(sizeof(char) + strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.nota = nota;
	s.grupa = grupa;
	s.materie = malloc(sizeof(char) + strlen(materie) + 1);
	strcpy(s.materie, materie);

	return s;
}

struct nod {
	student info;
	nod* next;
};

nod* inserareFinal(nod* adresacap, student s) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareStudent(s.nume, s.nota, s.grupa, s.materie);
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

void dezalocare(nod* adresacap) {
	nod* aux = adresacap;
	while (aux) {
		free(aux->info.nume);
		free(aux->info.materie);
		nod* temp = aux->next;
		free(aux);
		aux = temp;
	}
}

void afisare(nod* adresacap) {
	nod* aux = adresacap;
	while (aux != NULL) {
		printf("%s,%.2f, %d,%s \n", aux->info.nume, aux->info.nota, aux->info.grupa, aux->info.materie);
		aux = aux->next;
	}
}

void main() {
	/*student s = creareStudent("Madalina", 10.00, 1117, "SDD");
	student s1 = creareStudent("Marius", 9.50, 1116, "Java");
	student s2 = creareStudent("Elena", 8.75, 1113, "POO");*/

	//nod* adrcap = NULL;
	//adrcap=	inserareFinal(adrcap, s);
	//adrcap=	inserareFinal(adrcap, s1);
	//adrcap=	inserareFinal(adrcap, s2);

	//afisare(adrcap);

	//citire din fisier

	student s;
	nod* adresacap = NULL;

	char buffer[100];
	char separator[] = ",";
	char* token;

	FILE* fisier = fopen("Text.txt", "r");

	while (fgets(buffer, sizeof(buffer), fisier)) {
		token = strtok(buffer, separator);
		s.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(s.nume, token);

		token = strtok(NULL, separator);
		s.nota = atof(token);

		token = strtok(NULL, separator);
		s.grupa = atoi(token);

		token = strtok(NULL, separator);
		s.materie = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(s.materie, token);

		adresacap = inserareFinal(adresacap, s);

		free(s.nume);
		free(s.materie);


	}

	fclose(fisier);

	afisare(adresacap);

	dezalocare(adresacap);
}

