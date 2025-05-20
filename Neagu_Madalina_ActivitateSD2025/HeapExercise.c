#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dispozitivMobil dispozitivMobil;
typedef struct heap heap;

struct dispozitivMobil {
	unsigned int id;
	char* sistem;
	float pret;
	char* defecte;
	int nrZile;//prioritatea
};

dispozitivMobil initializare(unsigned int id, char* sistem, float pret, char* defecte, int nrZile) {
	dispozitivMobil dm;
	dm.id = id;
	dm.sistem = (char*)malloc(sizeof(char) * (strlen(sistem) + 1));
	strcpy(dm.sistem, sistem);
	dm.pret = pret;
	dm.defecte = (char*)malloc(sizeof(char) * (strlen(defecte) + 1));
	strcpy(dm.defecte, defecte);
	dm.nrZile = nrZile;

	return dm;
}

struct heap {
	int dim;
	dispozitivMobil* vector;
};

void filtrare(heap hp, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < hp.dim && hp.vector[indexSt].nrZile>hp.vector[indexRad].nrZile) {
		indexRad = indexSt;
	}
	if (indexDr < hp.dim && hp.vector[indexDr].nrZile>hp.vector[indexRad].nrZile) {
		indexRad = indexDr;
	}
	if (indexRad != index) {
		dispozitivMobil aux = hp.vector[indexRad];
		hp.vector[indexRad] = hp.vector[index];
		hp.vector[index] = aux;
		filtrare(hp, indexRad);//0
	}
}

heap inserare(heap hp, dispozitivMobil dm) {

	dispozitivMobil* copie = (dispozitivMobil*)malloc(sizeof(dispozitivMobil) * (hp.dim + 1));
	for (int i = 0; i < hp.dim; i++) {
		copie[i] = hp.vector[i];
	}
	copie[hp.dim] = initializare(dm.id, dm.sistem, dm.pret, dm.defecte, dm.nrZile);
	free(hp.vector);
	hp.dim++;
	hp.vector = copie;
	for (int i = (hp.dim / 2) - 1; i >= 0; i--) {
		filtrare(hp, i);
	}
	return hp;
}



heap extragere(heap hp, dispozitivMobil* dm) {
	dispozitivMobil aux = hp.vector[0];
	hp.vector[0] = hp.vector[hp.dim - 1];
	hp.vector[hp.dim - 1] = aux;
	dispozitivMobil* copie = (dispozitivMobil*)malloc(sizeof(dispozitivMobil) * (hp.dim - 1));
	for (int i = 0; i < hp.dim - 1; i++) {
		copie[i] = hp.vector[i];
	}
	//salvam elementul scos
	*dm = initializare(hp.vector[hp.dim - 1].id, hp.vector[hp.dim - 1].sistem, hp.vector[hp.dim - 1].pret, hp.vector[hp.dim - 1].defecte, hp.vector[hp.dim - 1].nrZile);
	free(hp.vector);
	hp.dim--;
	hp.vector = copie;

	filtrare(hp, 0);

	return hp;
}


//afisare 

void afisareHeap(heap h) {
	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			printf("%u %s %.2f %s %u \n", h.vector[i].id, h.vector[i].sistem, h.vector[i].pret, h.vector[i].defecte, h.vector[i].nrZile);
		}
	}
}

//dezalocare
void dezalocareHEap(heap h) {
	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			free(h.vector[i].sistem);
			free(h.vector[i].defecte);
		}
		free(h.vector);
	}
}

int numarsSistem(heap h, char* sistemCautat) {
	int contor = 0;
	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			if (strcmp(sistemCautat, h.vector[i].sistem) == 0) {
				contor++;
			}
		}
	}
	return contor;
}

void actulizareDefecte(heap h, int idCautat, char* defecttNou) {

	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			if (h.vector[i].id == idCautat) {
				free(h.vector[i].defecte);
				h.vector[i].defecte = (char*)malloc(sizeof(char) * (strlen(defecttNou) + 1));
				strcpy(h.vector[i].defecte, defecttNou);
			}
		}
	}

}

void main() {
	dispozitivMobil dm;
	heap h;
	h.dim = 0;
	h.vector = NULL;

	char liniebuffer[100];
	char sep[] = ",\n";
	char* token;

	FILE* f = fopen("Text6.txt", "r");

	while (fgets(liniebuffer, 100, f)) {
		token = strtok(liniebuffer, sep);
		dm.id = atoi(token);

		token = strtok(NULL, sep);
		dm.sistem = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(dm.sistem, token);

		token = strtok(NULL, sep);
		dm.pret = atof(token);

		token = strtok(NULL, sep);
		dm.defecte = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(dm.defecte, token);

		token = strtok(NULL, sep);
		dm.nrZile = atoi(token);

		h = inserare(h, dm);
		free(dm.sistem);
		free(dm.defecte);
	}
	fclose(f);

	afisareHeap(h);

	int nrIOS = numarsSistem(h, "IOS");
	printf("%d\n", nrIOS);

	actulizareDefecte(h, 18, "REPARAT!!!!");
	afisareHeap(h);
	dispozitivMobil dmExtras;
	h = extragere(h, &dmExtras);
	printf("\nAfisare heap dupa extragere: \n");
	afisareHeap(h);

	printf("%u %s %.2f %s %u \n", dmExtras.id, dmExtras.sistem, dmExtras.pret, dmExtras.defecte, dmExtras.nrZile);

	dezalocareHEap(h);
}