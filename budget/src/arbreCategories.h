#include "fichiers.h"
#ifndef ARBRECATEGORIES
#define ARBRECATEGORIES

typedef enum {true,false} boolean;
//structure d'abre pour gerer les categories en 3 niveaux
typedef struct catTree0 { //niveau 0, noeud principal rassemblant toutes les categories
	int nbelements;
	float seuil;
	catTree1* fils[20]; //maxi 20 categories
} catTree0 ;

typedef struct catTree1 { //niveau 1 de l'arbre
	catTree0 *papa;
	char* name[20];
	int nbelements;
	float seuil;
	catTree2* subcat[5]; //maxi 5 sous-categories par categories
} catTree1 ;

typedef struct catTree2 { //les feuilles seront les sous categories de la gestion de budget
	catTree1* papa;
	categorie* cat;
} catTree2 ;

typedef struct categorie {
	char nom[20];
	int nbelements;
	float seuil;
	char *date[255];
	int jour[255];  //sert à triCatDates
	int mois[255];
	int annee[255];
	char *type[255];
	char *endroit[255];  // Où les transactions ont été faites
	float montant[255];
} categorie ;

catTree0* loadArbre(char *fichier);

int saveArbre(catTree0* arbre);

int editTreeCat(catTree0* arbre);

int reequilibreSeuil(catTree0* arbre);

#endif