#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbreCategories.h"

(struct catTree0)* loadArbre(char* fichier); {
	(struct catTree0)* arbre = (struct catTree0)* malloc(sizeof(struct catTree0));
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
	while (!feof(fp)) { //tant qu'on n'est pas à la fin du fichier
        ret = buf;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 20);
		*ret2 = '\0';
        strcpy(categorie,(char*) ret);
        if (strcmp(categorie,categorie2) != 0) {
        	(struct catTree1)* arbre1 = (struct catTree1)* malloc(sizeof(struct catTree1));
        	arbre->nbelements = arbre->nbelements +1;
        	arbre->fils[i] = arbre1;
        	arbre1->papa=arbre;
        	strcpy(arbre1->name,categorie);
        	i++;
        	j=0;
        	strcpy(categorie,categorie2);
        }
        ret = ret2+1;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 50);
		*ret2 = '\0';
        strcpy(subcategorie,(char*) ret);
        (struct catTree2)* arbre2 = (struct catTree2)* malloc(sizeof(struct catTree2));
        arbre1->nbelements=arbre1->nbelements +1;
        arbre1->subcat[j]=arbre2;
        arbre2->papa=arbre1;
        j++;
        strcpy((arbre2->cat)->nom,subcategorie);
        ret = ret2+1;
        ret2 = strchr(ret,'\n');
        *ret2 = '\0';
        seuil = atof(ret);
        (arbre2->cat)->seuil=seuil;
		fgets(buf,255,txtcat);
	}
	fclose(txtcat);
	reequilibreSeuil(arbre);
	return arbre;
}

int saveArbre((struct catTree0)* arbre) {
	FILE* fichier = NULL;	
	char categorie[20] = "";
	char subcategorie[20] = "";
	float prix;
	int i = 0;
	int j = 0;
	char* chaine=(char*) malloc(sizeof(char)*255);
	fichier = fopen("ensembleDesCategories.info","w+");
	for (i=0;i<arbre->nbelements;i++) {
		catTree1* ifils = arbre->fils[i];
		for (j=0;j<ifils->nbelements;j++) {
			strcpy(chaine,ifils->name);
			strcat(chaine,",");
			strcat(chaine,((ifils->subcat[j])->cat)->nom);
			strcat(chaine,",");
			strcat(chaine,((ifils->subcat[j])->cat)->seuil));
			strcat(chaine,"\n");
			strcat(chaine,"\0");
			fputs(chaine,fichier);
		}
	}
	fclose(fichier);
	printf("Sauvegarde effectuée");
	return 0;
}

int editTreeCat((struct catTree0)* arbre) {
	char categorie[20] = "";
	char subcategorie[20];
	float seuil;
	int did=0;
	printf("Les categories existantes et leurs sous categories sont : \n")
	for (i=0;i<arbre->nbelements;i++) {
		catTree1* ifils = arbre->fils[i];
		printf("%s\n",ifils->name);
		for (j=0;j<ifils->nbelements;j++) {
			printf("%s,%.2f\n",((ifils->subcat[j])->cat)->nom,((ifils->subcat[j])->cat)->seuil);
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
				scanf("%lf",&seuil);
				for (i=0;i<arbre->nbelements;i++) {
					catTree1* ifils = arbre->fils[i];
					if (strcmp(ifils->name,categorie)==0) {
						j=ifils->nbelements;
						(struct catTree2)* arbre2 = (struct catTree2)* malloc(sizeof(struct catTree2));
						ifils->subcat[j]=arbre2;
        				arbre2->papa=ifils;
        				strcpy((arbre2->cat)->nom,subcategorie);
        				did=1;
					}
				}
				if (did==0) {
					i=arbre->nbelements;
					(struct catTree1)* arbre1 = (struct catTree1)* malloc(sizeof(struct catTree1));
        			arbre->fils[i] = arbre1;
        			arbre->nbelements = arbre->nbelements +1;
        			arbre1->papa=arbre;
        			strcpy(arbre1->name,categorie);
        			j=ifils->nbelements;
					(struct catTree2)* arbre2 = (struct catTree2)* malloc(sizeof(struct catTree2));
					ifils->subcat[j]=arbre2;
        			arbre2->papa=ifils;
        			strcpy((arbre2->cat)->nom,subcategorie);
        		}
        		reequilibreSeuil(arbre);
        		editTreeCat();
				choixCorrect = 0;
				break;
			case 2:
				printf("Entrez la catégorie (créée si inexistante) : ");
				scanf("%s",categorie);
				printf("Entrez la sous-catégorie : ");
				scanf("%s",subcategorie);
				for (i=0;i<arbre->nbelements;i++) {
					catTree1* ifils = arbre->fils[i];
					if (strcmp(ifils->name,categorie)==0) {
						for (j=0;j<ifils->nbelements;j++) {
							if (strcmp(ifils->subcat[j]->cat->nom,subcategorie)==0) {
								free(ifils->subcat[j]->cat);
								free(ifils->subcat[j]);
								ifils->nbelements=(ifils->nbelements)-1;
								if (ifils->nbelements==0) {
									free(arbre->fils[i]);
									int k = 0;
									for (k=i;k<arbre->nbelements-1;k++) {
										arbre->fils[k]=arbre->fils[k+1];
										arbre->nbelements=(arbre->nbelements)-1
									}
								}
							}
						}
					}
				}
				reequilibreSeuil(arbre);
				editTreeCat();
				choixCorrect = 0;
				break;
			case 3: 
				printf("Entrez la catégorie (créé si inexistante) : ");
				scanf("%s",categorie);
				printf("Entrez la sous-catégorie : ");
				scanf("%s",subcategorie);
				printf("Entrez le seuil : ");
				scanf("%lf",&seuil);
				for (i=0;i<arbre->nbelements;i++) {
					catTree1* ifils = arbre->fils[i];
					if (strcmp(ifils->name,categorie)==0) {
						for (j=0;j<ifils->nbelements;j++) {
							if (strcmp(ifils->subcat[j]->cat->nom,subcategorie)==0) {
								ifils->subcat[j]->cat->seuil=seuil;
							}
						}
					}
				}
        		reequilibreSeuil(arbre);
        		editTreeCat();
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
int reequilibreSeuil((struct catTree0)* arbre) {
	float countsub = 0.;
	float count = 0.;
	for (i=0;i<arbre->nbelements;i++) {
		countsub = 0.;
		catTree1* ifils = arbre->fils[i];
		for (j=0;j<ifils->nbelements;j++) {
			countsub = countsub + ifils->subcat[j]->cat->seuil;
		}
		ifils->seuil=countsub;
		count = count + countsub;
	}
	arbre->seuil=count;
	return 0;
}


int main() {
	
	//il faut load le fichier comprennant le listing des cat et ss cat pour creer l'arbre
	//stocker le pointeur sur l'arbre principal
	//proposer de rajouter une categorie, ou de modifier le seuil d'une cat/sscat existante en modifiant l'arbre
	//


	//finir en restockant l'arbre modifié dans le fichier texte

	return 0;
}

