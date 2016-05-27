#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "releve.h"
#include "fichiers.h"

int saisirReleve() {
	FILE* fichier = NULL;	
	char date[10] = "";
	char moyen[7] = "";
	char dest[20] = "";
	double prix;
	char cat[20] = "";
	char cont='y';
	fichier = fopen("releve","a+");
	printf("Veuillez suivre les instructions suivantes : ");
	do {
		printf("Entrez une date de la forme : jj/mm/aaaa : ");
		scanf("%s",date);
		printf("Entrez le moyen de transaction parmis 'CB','Liquide' et 'Chèque' : ");
		scanf("%s",moyen);
		printf("Entrez le destinataire (Max 20 caractères sans espace) : ");
		scanf("%s",dest);
		printf("Entrez la somme dépensée : ");
		scanf("%lf",&prix);
		printf("Entrez la catégorie d'achat parmi les categories existantes : ");
		scanf("%s",cat);
		fprintf(fichier,"%s,%s,%s,%.2f,%s \n",date,moyen,dest,prix,cat);
		printf("Continuer? (y/n) : ");
		scanf("%s",&cont);

	} while (cont=='y');
	fclose(fichier);
	return 0;
}


void tri() {
	// Range les opérations dans les fichiers correspondant à leur catégorie

	struct releve rel;
	rel = load("releve");

	struct categorie cat[20];
	int nbcat = 0; //nb de categories dans cat
	int i,j,k;
	int trouve = 0;
	char categorie[20] = "";

	for (i=0;i<rel.nbelements;i++) { //On parcourt tous les éléments chargés
		strcpy(categorie,rel.categorie[i]);
		for (j=0;j<nbcat;j++) {
			if (strcmp(cat[j].nom,categorie) == 0) {
				k = cat[j].nbelements;
				cat[j].date[k] = (char*) malloc(sizeof(char)*11);
				strcpy(cat[j].date[k],rel.date[i]);    //Encore une fois : c'est strcpy et pas =... --'
				cat[j].type[k] = (char*) malloc(sizeof(char)*8);
				strcpy(cat[j].type[k],rel.type[i]);
				cat[j].endroit[k] = (char*) malloc(sizeof(char)*50);
				strcpy(cat[j].endroit[k],rel.endroit[i]);
				cat[j].montant[k] = rel.montant[i];
				(cat[j].nbelements)++;
				trouve = 1;
			}
		}
		if (trouve == 0) { //si la categorie n'existe pas encore dans cat
			strcpy(cat[nbcat].nom,categorie);
			cat[nbcat].date[0] = (char*) calloc(11,sizeof(char));
			strcpy(cat[nbcat].date[0],rel.date[i]);
			cat[nbcat].type[0] = (char*) calloc(8,sizeof(char));
			strcpy(cat[nbcat].type[0],rel.type[i]);
			cat[nbcat].endroit[0] = (char*) calloc(50,sizeof(char));
			strcpy(cat[nbcat].endroit[0],rel.endroit[i]);
			cat[nbcat].montant[0]=rel.montant[i];
			cat[nbcat].nbelements = 1;
			saveCat(categorie);
			nbcat++;
		}
		trouve = 0;
	}

	// À partir d'ici, les transactions sont classées et on n'a plus qu'à les sauvegarder dans les dossiers du nom de la categorie
	for (i=0;i<nbcat;i++) {
		save(&cat[i]);
	}
}