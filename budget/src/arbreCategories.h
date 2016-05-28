#include "fichier.h"
#ifndef ARBRECATEGORIES
#define ARBRECATEGORIES

typedef enum boolean {true,false};
//structure d'abre pour gerer les categories en 3 niveaux
struct catTree0 { //niveau 0, noeud principal rassemblant toutes les categories
	int nbelements;
	float seuil;
	catTree1* fils[20]; //maxi 20 categories
} ;

struct catTree1 { //niveau 1 de l'arbre
	catTree0 *papa;
	char* name[20];
	int nbelements;
	float seuil;
	catTree2* subcat[5]; //maxi 5 sous-categories par categories
} ;

struct catTree2 { //les feuilles seront les sous categories de la gestion de budget
	catTree1* papa;
	categorie* cat;
} ;

(struct catTree0)* loadArbre(char *fichier);

int saveArbre((struct catTree0)* arbre);

int editTreeCat((struct catTree0)* arbre);

int reequilibreSeuil((struct catTree0)* arbre);

#endif