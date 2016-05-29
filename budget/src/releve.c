#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "releve.h"
#include "fichiers.h"
#include <string.h>
#include "arbreCategories.h"

int saisirReleve() {
	FILE* fichier = NULL;	
	char date[10] = "";
	char moyen[7] = "";
	char dest[20] = "";
	double prix;
	char cat[20] = "";
	char sscat[20] = "";
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
		printf("Entrez la sous-catégorie d'achat parmi les sous-categories existantes : ");
		scanf("%s",sscat);
		fprintf(fichier,"%s,%s,%s,%.2f,%s,%s\n",date,moyen,dest,prix,cat,sscat);
		printf("Continuer? (y/n) : ");
		scanf("%s",&cont);
	} while (cont=='y');
	fclose(fichier);
	return 0;
}

void tri() {
	// Range les opérations dans les fichiers correspondant à leur catégorie

	struct releve *rel;
	rel = load("releve");

	catTree0 *arbre = (catTree0*) malloc(sizeof(catTree0));
	//arbre->nbelements = 0;
	//arbre->seuil = 0.;
	arbre = loadArbre("fichiersTries/ensembleDesCategories.info");

	int i,j,k;
	int trouvecat = 0,trouvesscat = 0;
	//char* categorie = (char*) malloc(sizeof(char)*20);
	//char* sscategorie = (char*) malloc(sizeof(char)*20);
	char categorie[20];
	char sscategorie[20];

	for (i=0;i<rel->nbelements;i++) { //On parcourt tous les éléments chargés
		strcpy(categorie,rel->categorie[i]);
		strcpy(sscategorie,rel->sscategorie[i]);
		for (j=0;j<arbre->nbelements;j++) {
			if (strcmp(arbre->fils[j]->name,categorie) == 0) {
				for (k=0;k<arbre->fils[j]->nbelements;k++) {
					if (strcmp(arbre->fils[j]->subcat[k]->nom,sscategorie) == 0) {
						int n = arbre->fils[j]->subcat[k]->nbelements;
						arbre->fils[j]->subcat[k]->date[n] = (char*) malloc(11*sizeof(char));
						strcpy(arbre->fils[j]->subcat[k]->date[n],rel->date[i]);  
						arbre->fils[j]->subcat[k]->type[n] = (char*) malloc(sizeof(char)*8);
						strcpy(arbre->fils[j]->subcat[k]->type[n],rel->type[i]);
						arbre->fils[j]->subcat[k]->endroit[n] = (char*) malloc(sizeof(char)*50);
						strcpy(arbre->fils[j]->subcat[k]->endroit[n],rel->endroit[i]);
						arbre->fils[j]->subcat[k]->montant[n] = rel->montant[i];
						(arbre->fils[j]->subcat[k]->nbelements)++;
						trouvesscat = 1;
					}
				}
				if (trouvesscat == 0) {
					arbre->fils[j]->subcat[arbre->fils[j]->nbelements] = (struct categorie*) malloc(sizeof(struct categorie));
					arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->nbelements = 1;
					arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->seuil = 0.;
					strcpy(arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->nom,sscategorie);
					arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->date[0] = (char*) malloc(sizeof(char)*11);
					strcpy(arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->date[0],rel->date[i]);    //Encore une fois : c'est strcpy et pas =... --'
					arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->type[0] = (char*) malloc(sizeof(char)*8);
					strcpy(arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->type[0],rel->type[i]);
					arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->endroit[0] = (char*) malloc(sizeof(char)*50);
					strcpy(arbre->fils[j]->subcat[arbre->fils[j]->nbelements]->endroit[0],rel->endroit[i]);
					arbre->fils[j]->subcat[k]->montant[0] = rel->montant[i];
					arbre->fils[j]->nbelements++;
				}
				trouvecat = 1;
			}
		}
		if (trouvecat == 0) { //si la categorie n'existe pas encore dans cat
			arbre->fils[arbre->nbelements] = (catTree1*) malloc(sizeof(catTree1));
			strcpy(arbre->fils[arbre->nbelements]->name,categorie);
			arbre->fils[arbre->nbelements]->seuil = 0.;
			arbre->fils[arbre->nbelements]->subcat[0] = (struct categorie*) malloc(sizeof(struct categorie));
			arbre->fils[arbre->nbelements]->subcat[0]->seuil = 0.;
			strcpy(arbre->fils[arbre->nbelements]->subcat[0]->nom,sscategorie);
			arbre->fils[arbre->nbelements]->subcat[0]->date[0] = (char*) calloc(11,sizeof(char));
			strcpy(arbre->fils[arbre->nbelements]->subcat[0]->date[0],rel->date[i]);
			arbre->fils[arbre->nbelements]->subcat[0]->type[0] = (char*) calloc(8,sizeof(char));
			strcpy(arbre->fils[arbre->nbelements]->subcat[0]->type[0],rel->type[i]);
			arbre->fils[arbre->nbelements]->subcat[0]->endroit[0] = (char*) calloc(50,sizeof(char));
			strcpy(arbre->fils[arbre->nbelements]->subcat[0]->endroit[0],rel->endroit[i]);
			arbre->fils[arbre->nbelements]->subcat[0]->montant[0]=rel->montant[i];
			arbre->fils[arbre->nbelements]->subcat[0]->nbelements = 1;
			arbre->fils[arbre->nbelements]->nbelements = 1;
			arbre->nbelements++;
		}
		trouvecat = 0,trouvesscat = 0;
	}

	// À partir d'ici, les transactions sont classées et on n'a plus qu'à les sauvegarder dans les dossiers du nom de la categorie
	for (i=0;i<arbre->nbelements;i++) {
		triCatDates(arbre->fils[i]);
	}

	saveArbre(arbre);
	/*
	for (i=0;i<arbre->nbelements;i++) {  //Libération de la mémoire
		for (j=0;j<arbre->fils[i]->nbelements;j++) {
			for (k=0;k<arbre->fils[i]->subcat[j]->nbelements;k++) {
				free(arbre->fils[i]->subcat[j]->date[j]);
				free(arbre->fils[i]->subcat[j]->type[j]);
				free(arbre->fils[i]->subcat[j]->endroit[j]);
			}
		}
	}*/
}