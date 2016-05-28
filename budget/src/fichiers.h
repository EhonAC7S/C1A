#ifndef FICHIERS
#define FICHIERS

//enum transac {cb="CB",l="liquide",ch="cheque"};  //type de transaction

struct categorie {
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
} ;

struct releve {
	int nbelements;
	char *categorie[255];
	float seuil;
	char *date[255];
	char *type[255]; // Type de transaction (carte, liquide, chèque)
	char *endroit[255];  // Où les transactions ont été faites
	float montant[255];
} ;

int save(struct categorie *cat);

struct releve load(char *fichier);

int saveCat(char *cat);

struct categorie triChrono(struct categorie *cat, int i);

void triCatDates(struct categorie *cat);

#endif
