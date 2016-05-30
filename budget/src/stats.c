#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "fichiers.h"
#include "arbreCategories.h"

void accueilStats() {
    //Menu des statistiques

    printf("\n           ** Statistiques **\n\n\n");

	int choix=0,choixCorrect=0;
	int quitter = 0;
	while (choixCorrect == 0) {
        printf("   Que souhaitez-vous faire ?\n");
        printf("      1. Dépenses sur un mois\n");
        printf("      2. Revenir à l'accueil\n");
		printf("   Entrez votre choix : ");
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
	printf("  De quel mois souhaitez-vous consulter les statistiques ? (format mm/aaaa) ");
    scanf("%s",date);
    printf("\n\n\n");
	int mois,annee;
	char *ret = (char*) calloc(11,sizeof(char));
	strncpy(ret,date,2);
    mois = atoi(ret);
    ret = strchr(date,'/')+1;
    annee = atoi(ret);

    //On charge l'arbre des catégories existant :
    catTree0* arbre = (catTree0*) malloc(sizeof(catTree0));
    arbre = loadArbre("fichiersTries/ensembleDesCategories.info");
    char* fichier = (char*) malloc(sizeof(char)*50);

    int i,j,k;
    //Les actions suivantes sont effectuées pour chaque catégorie
    for (i=0;i<arbre->nbelements;i++) {    
    	printf("  Catégorie %s :\n", arbre->fils[i]->name);
    	float sommeCat = 0.;
        float seuilCat = 0;   //Le seuil pour la catégorie est la somme des seuils pour les sous-catégories

        //Les actions suivantes sont effectuées pour chaque sous-catégorie
    	for (j=0;j<arbre->fils[i]->nbelements;j++) {    
    		strcpy(fichier,"fichiersTries/");
    		strcat(fichier,arbre->fils[i]->name);
    		strcat(fichier,"/");
    		strcat(fichier,arbre->fils[i]->subcat[j]->nom);

            //On charge les opérations de la sous-catégorie considérée :
    		categorie* cat = loadCat(fichier,arbre->fils[i]->subcat[j]->nom);
    		float somme = 0.;
    		triSsCatDates(cat);
    		cat->seuil = arbre->fils[i]->subcat[j]->seuil;

            //On récupère les somme des montants pour la sous-catégorie
    		for (k=0;k<cat->nbelements;k++) {
    			if (cat->mois[k]==mois && cat->annee[k]==annee) {
    				somme = somme + cat->montant[k];
    			}
    		}
    		printf("      %s : %.2f\n", cat->nom, somme);

            //On affiche les informations concernant le seuil et sa situation par rapport au montant dépensé
            seuilCat = seuilCat + cat->seuil;
            if (cat->seuil != 0) {
        		if (somme > cat->seuil) {
        			printf("             Dépassement du seuil de : %.2f (seuil fixé à : %.2f)\n", somme-(cat->seuil),cat->seuil);
        		} else {
                    if (somme > (cat->seuil)*0.8) {
                           printf("             Vous êtes proche du seuil fixé à : %.2f\n",cat->seuil); 
                    } else {
                        printf("             Seuil fixé à : %.2f\n",cat->seuil);
                    }
        		}
            }
    		sommeCat = sommeCat + somme;
    	}
    	printf("    Les dépenses pour la catégorie %s ont été de : %.2f\n", arbre->fils[i]->name,sommeCat);
        
        //Informations sur le seuil de la catégorie
        if (seuilCat != 0) {
            if (sommeCat > seuilCat) {
                printf("     Dépassement du seuil pour la catégorie de : %.2f (seuil fixé à : %.2f)\n", sommeCat-seuilCat,seuilCat);
            } else {
                if (sommeCat > seuilCat*0.8) {
                    printf("     Vous êtes proche du seuil fixé à : %.2f pour cette catégorie\n",seuilCat); 
                } else {
                    printf("     Seuil fixé à : %.2f pour cette catégorie\n",seuilCat);
                }
            }
        }
        printf("\n");
    }
    //free(date);
    //free(ret);
    freeArbre(arbre);
}