// Pas besoin de compiler celui-ci vu qu'il est inclu dans les autres

struct categorie {
	char nom[20];
	int seuil;
	// Est-ce qu'on met un seul ou trois tableaux ?
	char date[255][10];  // séparé en jour/mois ?
	char type[255][7]; // Type de transaction (carte, liquide, chèque)
	char endroit[255][50];  // Où les transactions ont été faites
	float montant[255];
} ;
