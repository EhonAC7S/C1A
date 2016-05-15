struct categorie {
	char nom[20];
	int seuil;
	// Est-ce qu'on met un seul ou trois tableaux ?
	char date[255][10];  // séparé en jour/mois ?
	char type[255][7]; // Type de transaction (carte, liquide, chèque)
	char endroit[255][50];  // Où les transactions ont été faites
	float montant[255];
} ;

#ifndef FICHIERS
#define FICHIERS

int save(char fichier[]);

struct categorie load(char fichier[]);

#endif
