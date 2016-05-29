#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "fichiers.h"
#include "arbreCategories.h"

void accueilStats() {
	int choix=0,choixCorrect=0;
	int quitter = 0;
	while (choixCorrect == 0) {
        printf("\n\n   À quelle type de statistiques souhaitez-vous avoir accès ?\n");
        printf(" 1. Dépenses sur un mois\n");
        printf(" 2. Revenir à l'accueil\n");
		printf(" Entrez votre choix : ");
		scanf("%d",&choix);
		printf("\n\n");
		switch (choix) {
			case 1:
				depenses();
				break;
			case 2:
				choixCorrect = 1;
				break;
			default:
				break;
		}
	}
}

void depenses() {
	//Affiche les dépenses faites pour chaque chatégorie pour un mois

	char *date = (char*) malloc(sizeof(char)*8);
	printf("De quel mois souhaitez-vous consulter les statistiques ? (format mm/aaaa)\n");
    scanf("%s",date);
    printf("\n\n\n");
	int mois,annee;
	char *ret = (char*) calloc(11,sizeof(char));
	strncpy(ret,date,2);
    mois = atoi(ret);
    ret = strchr(date,'/')+1;
    annee = atoi(ret);
    //free(ret); 
    //free(date);
    //FILE *fp;

    catTree0* arbre = (catTree0*) malloc(sizeof(catTree0));
    arbre = loadArbre("fichiersTries/ensembleDesCategories.info");
    char* fichier = (char*) malloc(sizeof(char)*50);

    int i,j,k;
    for (i=0;i<arbre->nbelements;i++) {
    	printf("Catégorie %s :\n", arbre->fils[i]->name);
    	float sommeCat = 0.;
    	for (j=0;j<arbre->fils[i]->nbelements;j++) {
    		categorie* cat;
    		strcpy(fichier,"fichiersTries/");
    		strcat(fichier,arbre->fils[i]->name);
    		strcat(fichier,"/");
    		strcat(fichier,arbre->fils[i]->subcat[j]->nom);
    		cat = loadCat(fichier,arbre->fils[i]->subcat[j]->nom);
    		float somme = 0.;
    		triSsCatDates(cat);
    		cat->seuil = arbre->fils[i]->subcat[j]->seuil;
    		for (k=0;k<cat->nbelements;k++) {
    			if (cat->mois[k]==mois && cat->annee[k]==annee) {
    				somme = somme + cat->montant[k];
    			}
    		}
    		printf("    %s : %.2f\n", cat->nom, somme);
    		if (somme > cat->seuil) {
    			printf("           Dépassement du seuil de : %.2f (seuil fixé à : %.2f)\n", somme-(cat->seuil),cat->seuil);
    		} else {
    			printf("           Seuil fixé à : %.2f\n",cat->seuil);
    		}
    		sommeCat = sommeCat + somme;
    	}
    	printf("  Les dépenses pour la catégorie %s ont été de : %.2f\n", arbre->fils[i]->name,sommeCat);
    }
    free(date);
    free(ret);
    freeArbre(arbre);
}