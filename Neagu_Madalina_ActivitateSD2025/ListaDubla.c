#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct nod nod;
typedef struct student student;
typedef struct listaDubla listaDubla;

struct student {
	char* nume;
	float inaltime;
	int nrNote;
	int* note;
};

student creareStudent(char* nume, float inaltime, int nrNote, int* note) {
	student s;
	s.nume = malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.inaltime = inaltime;
	s.nrNote = nrNote;
	s.note = (int*)malloc(sizeof(int) * nrNote);
	for (int i = 0; i < s.nrNote; i++) {
		s.note[i] = note[i];
	}

	return s;


}

struct nod {
	student info;
	nod* next;
	nod* prev;
};

struct listaDubla {
	nod* prim;
	nod* ultim;
};

listaDubla InserareInceput(listaDubla lista, student s) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareStudent(s.nume, s.inaltime, s.nrNote, s.note);
	nou->next = lista.prim;
	nou->prev = NULL;
	if (lista.prim == NULL) {
		lista.prim = nou;
		lista.ultim = nou;
	}

	else {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou;
	}

	return lista;
}

listaDubla InserarelaFinal(listaDubla lista, student s) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareStudent(s.nume, s.inaltime, s.nrNote, s.note);
	nou->next = NULL;
	nou->prev = NULL;
	if (lista.prim == NULL) {
		lista.prim = nou;
		lista.ultim = nou;
	}

	else {
		nou->prev = lista.ultim;
		lista.ultim->next = nou;
		lista.ultim = nou;
	}

	return lista;
}

void travsersareInceput(listaDubla lista) {
	nod* aux = lista.prim;
	while (aux) {
		printf("%s,%.2f,%d \n", aux->info.nume, aux->info.inaltime, aux->info.nrNote);
		for (int i = 0; i < aux->info.nrNote; i++) {
			printf("%d \n", aux->info.note[i]);
		}

		printf("\n");
		aux = aux->next;
	}
}

void dezalocare(listaDubla lista) {
	nod* aux = lista.prim;
	while (aux) {
		free(aux->info.nume);
		free(aux->info.note);
		nod* temp = aux->next;
		free(aux);
		aux = temp;
	}
}

void main() {
	student s;
	listaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	char linieBuffer[100];
	char separator[] = ",";
	char* token;

	FILE* pfile = fopen("Text1.txt", "r");

	while (fgets(linieBuffer, sizeof(linieBuffer), pfile)) {
		token = strtok(linieBuffer, separator);
		s.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(s.nume, token);

		token = strtok(NULL, separator);
		s.inaltime = atof(token);

		token = strtok(NULL, separator);
		s.nrNote = atoi(token);

		s.note = (int*)malloc(sizeof(int) * s.nrNote);
		for (int i = 0; i < s.nrNote; i++) {
			token = strtok(NULL, separator);
			s.note[i] = atoi(token);

		}

		lista = InserareInceput(lista, s);

		lista = InserarelaFinal(lista, s);

		free(s.nume);
		free(s.note);
	}

	fclose(pfile);

	travsersareInceput(lista);

}