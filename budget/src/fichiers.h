#ifndef FICHIERS
#define FICHIERS

//enum transac {cb="CB",l="liquide",ch="cheque"};  //type de transaction

struct categorie {
	char nom[20];
	int nbelements;
	int seuil;
	char date[255][11];
	char type[255][8];
	char endroit[255][50];  // Où les transactions ont été faites
	float montant[255];
} ;

struct releve {
	char nom[20];
	int nbelements;
	char categorie[255][20];
	int seuil;
	char date[255][11];
	char type[255][8]; // Type de transaction (carte, liquide, chèque)
	char endroit[255][50];  // Où les transactions ont été faites
	float montant[255];
} ;

int save(struct categorie cat);

struct releve load(char *fichier);

#endif
