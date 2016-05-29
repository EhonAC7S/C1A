#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichiers.h"
#include "arbreCategories.h"

catTree0* loadArbre(char* fichier) {
	catTree0* arbre = (catTree0*) malloc(sizeof(catTree0));
	FILE* txtcat;
	txtcat = fopen(fichier,"r");
	int i=0;
	int j=0;
	char buf[255];
	char *ret;
	char *ret2;
	char categorie[20] = "";
	char categorie2[20] = "";
	char subcategorie[20];
	float seuil;
	catTree1* arbre1;
	struct categorie* sscat;
	while (!feof(txtcat)) { //tant qu'on n'est pas à la fin du fichier
        ret = buf;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 20);
		*ret2 = '\0';
        strcpy(categorie,(char*) ret);
        if (strcmp(categorie,categorie2) != 0) {
        	catTree1* arbre1 = (catTree1*) malloc(sizeof(catTree1));
        	arbre->nbelements = arbre->nbelements +1;
        	arbre->fils[i] = arbre1;
        	strcpy(arbre1->name,categorie);
        	i++;
        	j=0;
        	strcpy(categorie,categorie2);
        }
        ret = ret2+1;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 50);
		*ret2 = '\0';
        strcpy(subcategorie,(char*) ret);
        sscat = (struct categorie*) malloc(sizeof(categorie));
        arbre1->nbelements=arbre1->nbelements +1;
        arbre1->subcat[j]=sscat;
        j++;
        strcpy(sscat->nom,subcategorie);
        ret = ret2+1;
        ret2 = strchr(ret,'\n');
        *ret2 = '\0';
        seuil = atof(ret);
        sscat->seuil=seuil;
		fgets(buf,255,txtcat);
	}
	fclose(txtcat);
	reequilibreSeuil(arbre);
	return arbre;
}

int saveArbre(catTree0* arbre) {
	FILE* fichier = NULL;	
	char categorie[20] = "";
	char subcategorie[20] = "";
	float prix;
	char prixstr[7] = "";
	int i = 0;
	int j = 0;
	char* chaine=(char*) malloc(sizeof(char)*255);
	fichier = fopen("ensembleDesCategories.info","w+");
	for (int i=0;i<arbre->nbelements;i++) {
		catTree1* ifils = (arbre->fils[i]);
		for (int j=0;j<ifils->nbelements;j++) {
			strcpy(chaine,(ifils->name));
			strcat(chaine,",");
			strcat(chaine,(ifils->subcat[j])->nom);
			strcat(chaine,",");
			sprintf(prixstr, "%f",(ifils->subcat[j])->seuil);
			strcat(chaine,prixstr);
			strcat(chaine,"\n\0");
			fputs(chaine,fichier);
		}
	}
	fclose(fichier);
	printf("Sauvegarde effectuée");
	return 0;
}

int editTreeCat(catTree0* arbre) {
	char categorie[20] = "";
	char subcategorie[20];
	float seuil;
	int did=0;
	struct categorie* sscat;
	printf("Les categories existantes et leurs sous categories sont : \n");
	for (int i=0;i<arbre->nbelements;i++) {
		catTree1* ifils = arbre->fils[i];
		printf("%s\n",ifils->name);
		for (int j=0;j<ifils->nbelements;j++) {
			printf("%s,%.2f\n",(ifils->subcat[j])->nom,(ifils->subcat[j])->seuil);
		}
	}
	int choix=0,choixCorrect=0;
	printf("\n          *** Gestion de Catégories ***\n\n\n");
	printf(" Que souhaitez-vous faire ?\n");
	printf("    1. Ajouter une sous-catégorie\n");
	printf("    2. Supprimer une sous-catégorie\n");
	printf("    3. Changer le seuil d'une sous-categorie\n");
	printf("    4. Quitter la gestion des catégories\n");
	while (choixCorrect == 0) {
		printf(" Entrez votre choix : ");
		scanf("%d",&choix);
		printf("\n\n");
		switch (choix) {
			case 1:
				printf("Entrez la catégorie (créé si inexistante) : ");
				scanf("%s",categorie);
				printf("Entrez la sous-catégorie : ");
				scanf("%s",subcategorie);
				printf("Entrez le seuil : ");
				scanf("%f",&seuil);
				for (int i=0;i<arbre->nbelements;i++) {
					catTree1* ifils = arbre->fils[i];
					if (strcmp(ifils->name,categorie)==0) {
						int j=ifils->nbelements;
						sscat = (struct categorie*) malloc(sizeof(categorie));
						ifils->subcat[j]=sscat;
        				strcpy(sscat->nom,subcategorie);
        				did=1;
					}
				}
				if (did==0) {
					int i=arbre->nbelements;
					catTree1* arbre1 = (catTree1*) malloc(sizeof(catTree1));
        			arbre->fils[i] = arbre1;
        			arbre->nbelements = arbre->nbelements +1;
        			strcpy(arbre1->name,categorie);
        			int j=(arbre->fils[i])->nbelements;
					sscat = (struct categorie*) malloc(sizeof(categorie));
					arbre->fils[i]->subcat[j]=sscat;
        			strcpy(sscat->nom,subcategorie);
        		}
        		reequilibreSeuil(arbre);
        		editTreeCat(arbre);
				choixCorrect = 0;
				break;
			case 2:
				printf("Entrez la catégorie : ");
				scanf("%s",categorie);
				printf("Entrez la sous-catégorie : ");
				scanf("%s",subcategorie);
				for (int i=0;i<arbre->nbelements;i++) {
					catTree1* ifils = arbre->fils[i];
					if (strcmp(ifils->name,categorie)==0) {
						for (int j=0;j<ifils->nbelements;j++) {
							if (strcmp((ifils->subcat[j])->nom,subcategorie)==0) {
								free(ifils->subcat[j]);
								ifils->nbelements=(ifils->nbelements)-1;
								if (ifils->nbelements==0) {
									free(arbre->fils[i]);
									int k = 0;
									for (k=i;k<arbre->nbelements-1;k++) {
										arbre->fils[k]=arbre->fils[k+1];
										arbre->nbelements=(arbre->nbelements)-1;
									}
								}
							}
						}
					}
				}
				reequilibreSeuil(arbre);
				editTreeCat(arbre);
				choixCorrect = 0;
				break;
			case 3: 
				printf("Entrez la catégorie : ");
				scanf("%s",categorie);
				printf("Entrez la sous-catégorie : ");
				scanf("%s",subcategorie);
				printf("Entrez le seuil : ");
				scanf("%f",&seuil);
				for (int i=0;i<arbre->nbelements;i++) {
					catTree1* ifils = arbre->fils[i];
					if (strcmp((ifils->name),categorie)==0) {
						for (int j=0;j<(ifils->nbelements);j++) {
							if (strcmp((ifils->subcat[j])->nom,subcategorie)==0) {
								(ifils->subcat[j])->seuil=seuil;
							}
						}
					}
				}
        		reequilibreSeuil(arbre);
        		editTreeCat(arbre);
				choixCorrect = 0;
				break;
			case 4:
				choixCorrect = 1;
				break;
			default:
				break;
		}
	}
}
int reequilibreSeuil(catTree0* arbre) {
	int i=0;
	int j=0;
	float countsub = 0.;
	float count = 0.;
	for (i=0;i<(arbre->nbelements);i++) {
		countsub = 0.;
		catTree1* ifils = arbre->fils[i];
		for (j=0;j<(ifils->nbelements);j++) {
			countsub = countsub + (ifils->subcat[j])->seuil;
		}
		ifils->seuil=countsub;
		count = count + countsub;
	}
	arbre->seuil=count;
	return 0;
}


int gestionCategories() {
	
	catTree0* arbre = loadArbre("ensembleDesCategories.info"); //il faut load le fichier comprennant le listing des cat et ss cat pour creer l'arbre
	editTreeCat(arbre);
	//proposer de rajouter une categorie, ou de modifier le seuil d'une cat/sscat existante en modifiant l'arbre
	saveArbre(arbre); //finir en restockant l'arbre modifié dans le fichier texte
	return 0;
}
