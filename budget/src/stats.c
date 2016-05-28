#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "fichiers.h"

void accueilStats() {
	int choix=0,choixCorrect=0;
	int quitter = 0;
	printf("\n\n   À quelle type de statistiques souhaitez-vous avoir accès ?\n");
	printf(" 1. Dépenses sur un mois\n");
	printf(" 2. Revenir à l'accueil\n");
	printf(" 3. Quitter\n");
	while (choixCorrect == 0) {
		printf(" Entrez votre choix : ");
		scanf("%d",&choix);
		printf("\n\n");
		switch (choix) {
			case 1:
				depenses();
				choixCorrect = 1;
				break;
			case 2:
				accueil();
				choixCorrect = 1;
				break;
			case 3:
				choixCorrect = 1;
				quitter = 1;
				break;
			default:
				break;
		}
	}
	if (quitter == 0) {
		accueil();
	}
}


void depenses() {
	//Affiche les dépenses faites pour chaque chatégorie pour un mois

	char *date = (char*) malloc(sizeof(char)*8);
	printf("De quel mois souhaitez-vous consulter les statistiques ? (format mm/aaaa)\n");
    scanf("%s",date);
	int mois,annee;
	char *ret = (char*) calloc(11,sizeof(char));
	strncpy(ret,date,2);
    mois = atoi(ret);
    ret = strchr(date,'/')+1;
    annee = atoi(ret);
    free(ret); free(date);

    FILE *fp;

	char *fichier;
	fichier = (char*) malloc(sizeof(char)*50);
	strcpy(fichier,"fichiersTries/categories");

	fp = fopen(fichier,"r");
	char buf[255];

	fgets(buf,255,fp);
	char *nom = (char*) malloc(20*sizeof(char));

	while (!feof(fp)) {
		strcpy(nom,buf);
		
		fgets(buf,255,fp);
	}

	fclose(fp);
}