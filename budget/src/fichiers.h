#ifndef FICHIERS
#define FICHIERS

typedef struct categorie categorie;
struct categorie {
	char nom[20];
	int nbelements;
	float seuil;
	char *date[255];
	int jour[255];  //sert à triCatDates
	int mois[255];
	int annee[255];
	char *type[255];
	char *endroit[255];  // C'est le destinaire
	float montant[255];
} ;
typedef struct releve releve;
struct releve {
	int nbelements;
	char *categorie[255];
	char *sscategorie[255];
	float seuil;
	char *date[255];
	char *type[255]; // Type de transaction (carte, liquide, chèque)
	char *endroit[255];  // C'est le destinaire
	float montant[255];
} ;

releve *load(char *fichier);

categorie *loadCat(char *fichier);

categorie triChrono(categorie *cat, int i);

void triSsCatDates(categorie *cat);

#endif
