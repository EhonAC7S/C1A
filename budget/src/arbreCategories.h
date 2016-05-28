#include "fichier.h"
#ifndef ARBRECATEGORIES
#define ARBRECATEGORIES

typedef enum bool {true,false};
//structure d'abre pour gerer les categories en 3 niveaux
struct catTree0 { //niveau 0, noeud principal rassemblant toutes les categories
	int nbelements;
	int seuil;
	catTree1* fils[20]; //maxi 20 categories
} ;

struct catTree1 { //niveau 1 de l'arbre
	catTree0 *papa;
	char* name[20];
	int nbelements;
	int seuil;
	catTree2* subcat[5]; //maxi 5 sous-categories par categories
} ;

struct catTree2 { //les feuilles seront les sous categories de la gestion de budget
	catTree1* papa;
	categorie* cat;
} ;


