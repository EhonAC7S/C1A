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

<<<<<<< HEAD
int save(struct categorie *cat);

struct releve load(char *fichier);

int tri();
=======
int tri();

int save(struct categorie cat);

struct releve load(char *fichier);

int saisirReleve();
>>>>>>> b0d4f13d253cfa0fd5c96f0c1667e1778f663b66

#endif
