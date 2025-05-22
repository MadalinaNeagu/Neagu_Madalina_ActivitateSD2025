#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct dispozitivMobil dispozitivMobil;
typedef struct nod nod;

struct dispozitivMobil {
	unsigned int id;
	char* sistem;
	float pret;
	char* defecte;
	int nrZile;
};

struct nod {
	dispozitivMobil info;
	nod* next;
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
void afisareDiispozitiv(dispozitivMobil dm) {
	printf("%u %s %.2f %s %u \n", dm.id, dm.sistem, dm.pret, dm.defecte, dm.nrZile);

}
//stiva
//*stiva=cap
void push(nod** stiva, dispozitivMobil dm) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initializare(dm.id, dm.sistem, dm.pret, dm.defecte, dm.nrZile);
	nou->next = NULL;//in stiva next est intotdeauna cap sau *stiva
	if (*stiva == NULL) {
		*stiva = nou;
	}
	else {
		//inseram la incepu 
		nou->next = *stiva;
		*stiva = nou;
	}
}

//extragere
int pop(nod** stiva, dispozitivMobil* extras) {
	if (*stiva == NULL) {
		return -1;
	}
	else {
		//am salvat nodul extras
		*extras = initializare((*stiva)->info.id, (*stiva)->info.sistem, (*stiva)->info.pret, (*stiva)->info.defecte, (*stiva)->info.nrZile);
		nod* temp = *stiva;
		*stiva = (*stiva)->next;
		free(temp->info.defecte);
		free(temp->info.sistem);
		free(temp);
		return 0;
	}

}

//coada
void put(nod** prim, nod** ultim, dispozitivMobil dm) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initializare(dm.id, dm.sistem, dm.pret, dm.defecte, dm.nrZile);
	nou->next = NULL;
	if (*prim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}

}

//extragere
int get(nod** prim, nod** ultim, dispozitivMobil* extras) {
	if (*prim == NULL) {
		return -1;
		*ultim = NULL;
	}
	else {
		*extras = initializare((*prim)->info.id, (*prim)->info.sistem, (*prim)->info.pret, (*prim)->info.defecte, (*prim)->info.nrZile);
		nod* temp = *prim;
		*prim = (*prim)->next;
		free(temp->info.defecte);
		free(temp->info.sistem);
		free(temp);
		return 0;
	}
}

void afisare(nod* stiva) {
	while (stiva) {
		afisareDiispozitiv(stiva->info);
		stiva = stiva->next;
	}
}

dispozitivMobil cauta(nod** stiva, unsigned int id) {
	//nod* stivanoua = NULL;
	while ((*stiva)->info.id != id) {
		dispozitivMobil ext;
		pop(stiva, &ext);

	}
	return (*stiva)->info;

}

nod* muatare(nod** stiva, unsigned int id) {
	nod* stivanoua = NULL;
	while ((*stiva)->info.id != id) {
		dispozitivMobil ext;
		pop(stiva, &ext);
		push(&stivanoua, ext);
	}
	return stivanoua;

}



void main() {
	dispozitivMobil dm = initializare(12, "IOS", 23.33, "folie", 1);
	dispozitivMobil dm1 = initializare(178, "IOS", 124.33, "display", 1);
	afisareDiispozitiv(dm);

	dispozitivMobil* pdm = &dm;
	dispozitivMobil* pdm1 = &dm1;
	afisareDiispozitiv(*pdm);
	//(*pdm).id = 88;
	//afisareDiispozitiv(dm);


	dispozitivMobil** ppdm = &pdm;
	afisareDiispozitiv(*(*ppdm));
	*ppdm = pdm1;
	afisareDiispozitiv(*(*ppdm));
	nod* stiva = NULL;
	push(&stiva, dm);
	push(&stiva, dm1);
	printf("-----------------------------\n");
	afisare(stiva);

	dispozitivMobil ext;
	pop(&stiva, &ext);
	printf("-----------------------------\n");
	afisare(stiva);
	printf("-----------------------------\n");
	afisareDiispozitiv(ext);

	nod* prim = NULL;
	nod* ultim = NULL;
	put(&prim, &ultim, dm1);
	put(&prim, &ultim, dm);
	put(&prim, &ultim, dm);
	printf("-----------------------------\n");

	afisare(prim);
	printf("-----------------------------\n");

	get(&prim, &ultim, &ext);
	afisare(prim);

	dispozitivMobil dm2 = initializare(14, "IOS", 23.33, "folie", 1);
	dispozitivMobil dm3 = initializare(74, "IOS", 23.33, "folie", 1);

	push(&stiva, dm);
	push(&stiva, dm1);
	push(&stiva, dm2);
	push(&stiva, dm3);

	printf("-----------------------------\n");
	afisare(stiva);
	//dispozitivMobil cautat = cauta(&stiva, 178);
	//printf("-----------------------------\n");
	//afisare(stiva);

	//printf("-----------------------------\n");
	//afisareDiispozitiv(cautat);

	printf("-----------------------------\n");
	nod* stivaNoua = muatare(&stiva, 178);
	afisare(stivaNoua);

}