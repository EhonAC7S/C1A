#include "fichiers.h"
#ifndef ARBRECATEGORIES
#define ARBRECATEGORIES

typedef enum {true,false} boolean;

typedef struct catTree1 catTree1;
struct catTree1 { //niveau 1 de l'arbre
	char name[20];
	int nbelements;
	float seuil;
	categorie* subcat[5]; //maxi 5 sous-categories par categories
} ;

typedef struct catTree0 catTree0;
struct catTree0 { //niveau 0, noeud principal rassemblant toutes les categories
	int nbelements;
	float seuil;
	catTree1* fils[20]; //maxi 20 categories
} ;

catTree0* loadArbre(char *fichier);

int saveArbre(catTree0* arbre);

int editTreeCat(catTree0* arbre);

int reequilibreSeuil(catTree0* arbre);

int gestionCategories();

int save(catTree1 *cat);

void triCatDates(catTree1 *cat);

#endif