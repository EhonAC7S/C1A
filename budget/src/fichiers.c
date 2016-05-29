#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fichiers.h"
#include "arbreCategories.h"

int save(catTree1* cat) {
	//Sauvegarde les données d'une catégorie (notamment utilisé par la fonction tri())

	char* dossier = (char*) malloc(sizeof(char)*50);
	strcpy(dossier,"fichiersTries/");
	strcat(dossier,cat->name);
	mkdir(dossier, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	printf("%s\n", dossier);

	int i;
	for (i=0;i<cat->nbelements;i++) {
		FILE *fp;
		char *fichier;
		fichier = (char*) malloc(sizeof(char)*50);
		strcpy(fichier,dossier);
		strcat(fichier,"/");
		strcat(fichier,cat->subcat[i]->nom);
		fp = fopen(fichier,"w+");
		printf("%s\n", fichier);

		int j;
		char *chaine= (char*) malloc(sizeof(char)*255);

		for (j=0;j<cat->subcat[i]->nbelements;j++) {
			strcpy(chaine,cat->subcat[i]->date[j]);
			strcat(chaine,",");
			strcat(chaine,cat->subcat[i]->type[j]);
			strcat(chaine,",");
			strcat(chaine,cat->subcat[i]->endroit[j]);
			strcat(chaine,",");
			char str[20];
			sprintf(str, "%.2f",cat->subcat[i]->montant[j]);
			strcat(chaine,str);
			strcat(chaine,"\n");
			fputs(chaine,fp);
		}

		fclose(fp);
		free(fichier);
		free(chaine);
	}
	//free(cat);    //vérifier que ça fonctionne bien
	return 0;
}



releve* load(char *fichier) {   
	//Renvoie une structure contenant tous les éléments du relevé

	releve *cat = (releve*) malloc(sizeof(releve)); //structure que l'on crée
	FILE *fp;

	fp = fopen(fichier,"r");

	int i=0;
	char buf[255];
	char *ret;
	char *ret2;
	char *dates;
	dates = (char*) calloc(11,sizeof(char));
	fgets(buf,255,fp);  //Les fgets doivent être faits avant de vérifier que l'on n'est pas à la fin du fichier (-> seg fault sinon)

	while (!feof(fp)) { //tant qu'on n'est pas à la fin du fichier
		strncpy(dates,buf,10); //copie les 10 premiers caractères de buf dans dates
		strncpy(dates,buf,10); //copie les 10 premiers caractères de buf dans cat.dates[i]
		strcat(dates,"\0");
		cat->date[i] = (char*) malloc(sizeof(char)*11);
		strcpy(cat->date[i],dates);
        ret = strchr(buf,',')+1;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 20);
		*ret2 = '\0';
		cat->type[i] = (char*) malloc(sizeof(char)*8);
        strcpy(cat->type[i],(char*) ret);
        ret = ret2+1;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 50);
		*ret2 = '\0';
		cat->endroit[i] = (char*) malloc(sizeof(char)*50);
        strcpy(cat->endroit[i],(char*) ret);
        ret = ret2+1;
        ret2 = strchr(ret,',');
		*ret2 = '\0';
        cat->montant[i] = atof(ret);
		ret = ret2+1;
        ret2 = memchr(ret,(int)',', 50);
		*ret2 = '\0';
		cat->categorie[i] = (char*) malloc(sizeof(char)*20);
		strcpy(cat->categorie[i],(char*) ret);
		ret = ret2+1;
		ret2 = memchr(ret,(int)'\n', 50);
		*ret2 = '\0';
		cat->sscategorie[i] = (char*) malloc(sizeof(char)*20);
		strcpy(cat->sscategorie[i],(char*) ret);
        i++;
		fgets(buf,255,fp);
	}

	fclose(fp);
	cat->nbelements = i;
	free(dates);
	return cat;
}

struct categorie triChrono(struct categorie *cat, int i) {
	//Inverse deux valeurs dans une categorie

	int mt,a,j,m;								//montant, année, jour, mois
	char *d = (char*) malloc(sizeof(char)*11);  //date
	char *t = (char*) malloc(sizeof(char)*8);	//type
	char *e = (char*) malloc(sizeof(char)*50);	//endroit

	a = cat->annee[i+1];
	cat->annee[i+1] = cat->annee[i];
	cat->annee[i] = a;

	j = cat->jour[i+1];
	cat->jour[i+1] = cat->jour[i];
	cat->jour[i] = j;

	m = cat->mois[i+1];
	cat->mois[i+1] = cat->mois[i];
	cat->mois[i] = m;

	strcpy(d,cat->date[i+1]);
	strcpy(cat->date[i+1],cat->date[i]);
	strcpy(cat->date[i],d);

	strcpy(t,cat->type[i+1]);
	strcpy(cat->type[i+1],cat->type[i]);
	strcpy(cat->type[i],t);

	strcpy(e,cat->endroit[i+1]);
	strcpy(cat->endroit[i+1],cat->endroit[i]);
	strcpy(cat->endroit[i],e);

	mt = cat->montant[i+1];
	cat->montant[i+1] = cat->montant[i];
	cat->montant[i] = mt;

	free(d);
	free(t);
	free(e);
}


void triSsCatDates(struct categorie *cat) {
	//Trie chronologiquement les opérations de la sous-catégorie donnée en argument
	int i;
	char *ret;
	char *ret2;
	char *dateJ;
	for (i=0;i<cat->nbelements;i++) {   //Cette boucle remplit les attribut jour,mois et annee de cat
		dateJ = (char*) calloc(11,sizeof(char));
		ret = (char*) calloc(11,sizeof(char));
		ret2 = (char*) calloc(11,sizeof(char));
		strcpy(dateJ,cat->date[i]);

        strncpy(ret,dateJ,2);
        cat->jour[i] = atoi(ret);

        ret = strchr(dateJ,'/')+1;
        ret2 = strchr(ret,'/');
        *ret2 = '\0';
        cat->mois[i] = atoi(ret);

        ret = ret2+1;
        cat->annee[i] = atoi(ret);
        //printf("%d/%d/%d\n", cat->jour[i], cat->mois[i], cat->annee[i]);
	}
	//free(ret);    //ces libérations de mémoire ne fonctionnent pas
	//free(ret2);
	//free(dateJ);
	int j=0;      //Nous permet de faire les boucles jusqu'à ce que tout le tableau soit trié
	while (j==0) {
		j=1;
		for (i=0;i<cat->nbelements-1;i++) {    //algorithme de tri par années
			if (cat->annee[i+1]<cat->annee[i]) {
				//printf("%d/%d\n",cat->annee[i+1],cat->annee[i]);
				triChrono(cat,i);
				//printf("%d/%d\n",cat->annee[i+1],cat->annee[i]);
				j=0;
			}
		}
	}
	j=0;
	while (j==0) {
		j=1;
		for (i=0;i<cat->nbelements-1;i++) {    //algorithme de tri par mois
			if (cat->mois[i+1]<cat->mois[i] && cat->annee[i+1]==cat->annee[i]) {
				//printf("%d/%d\n",cat->mois[i+1],cat->mois[i]);
				triChrono(cat,i);
				//printf("%d/%d\n",cat->mois[i+1],cat->mois[i]);
				j=0;
			}
		}
	}
	j=0;
	while (j==0) {
		j=1;
		for (i=0;i<cat->nbelements-1;i++) {    //algorithme de tri par jour
			if (cat->jour[i+1]<cat->jour[i] && cat->mois[i+1]==cat->mois[i] && cat->annee[i+1]==cat->annee[i]) {
				//printf("%d/%d\n",cat->jour[i+1],cat->jour[i]);
				triChrono(cat,i);
				//printf("%d/%d\n",cat->jour[i+1],cat->jour[i]);
				j=0;
			}
		}
	}
}

void triCatDates(catTree1 *cat) {
	//Trie chronologiquement les opérations de la catégorie donnée en argument, ie de toutes ses sous-catégories
	int i;
	for (i=0;i<cat->nbelements;i++) {
		triSsCatDates(cat->subcat[i]);
	}
	save(cat);
}