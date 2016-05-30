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
	//Création du dossier de la catégorie si celui-ci n'existe pas
	mkdir(dossier, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	int i;
	//Les opérations qui suivent sont effectuées pour chaque sous-catégorie
	for (i=0;i<cat->nbelements;i++) {
		FILE *fp;
		char *fichier;
		fichier = (char*) malloc(sizeof(char)*50);
		strcpy(fichier,dossier);
		strcat(fichier,"/");
		strcat(fichier,cat->subcat[i]->nom);
		fp = fopen(fichier,"w+");

		int j;
		char *chaine= (char*) malloc(sizeof(char)*255);

		//L'enregistrement des données respecte le format : jj/mm/annee,typeTransaction,destinataire,montant
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
	
	return 0;
}



releve* load(char *fichier) {   
	//Renvoie une structure contenant tous les éléments du relevé

	//On crée la structure qui va contenir toutes les opérations
	releve *cat = (releve*) malloc(sizeof(releve)); 

	FILE *fp;
	fp = fopen(fichier,"r");

	int i=0;
	char buf[255];
	char *ret;
	char *ret2;
	char *dates;
	dates = (char*) calloc(11,sizeof(char));

	fgets(buf,255,fp);  
	//On parcourt le fichier releve ligne par ligne pour récupérer toutes les opérations
	while (!feof(fp)) { 
		//Traitement de la date :
		strncpy(dates,buf,10); 
		strcat(dates,"\0");
		cat->date[i] = (char*) malloc(sizeof(char)*11);

		//Traitement du type :
		strcpy(cat->date[i],dates);
        ret = strchr(buf,',')+1;
        ret2 = strchr(ret,',');  
		*ret2 = '\0';
		cat->type[i] = (char*) malloc(sizeof(char)*8);
        strcpy(cat->type[i],(char*) ret);

        //Traitement du destinataire :
        ret = ret2+1;
        ret2 = strchr(ret,',');
		*ret2 = '\0';
		cat->endroit[i] = (char*) malloc(sizeof(char)*50);
        strcpy(cat->endroit[i],(char*) ret);

        //Traitement du montant :
        ret = ret2+1;
        ret2 = strchr(ret,',');
		*ret2 = '\0';
        cat->montant[i] = atof(ret);

        //Traitement de la catégorie :
		ret = ret2+1;
        ret2 = memchr(ret,',', 50);
		*ret2 = '\0';
		cat->categorie[i] = (char*) malloc(sizeof(char)*20);
		strcpy(cat->categorie[i],(char*) ret);

		//Traitement de la sous-catégorie :
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


struct categorie *loadCat(char *fichier,char *nom) {   
	//Renvoie une structure contenant tous les éléments d'une sous-catégorie

	//Structure contenant les éléments du fichier que l'on va lire (i.e. les opérations de la sous-catégorie)
	struct categorie *cat = (struct categorie*) malloc(sizeof(struct categorie));; 
	strcpy(cat->nom,nom);
	FILE *fp;

	fp = fopen(fichier,"r");
	int i=0;
	char buf[255];
	char *ret;
	char *ret2;
	char *dates;
	dates = (char*) calloc(11,sizeof(char));

	fgets(buf,255,fp);
	//On parcourt le fichier releve ligne par ligne pour récupérer toutes les opérations
	while (!feof(fp)) {
		//Traitement de la date :
		strncpy(dates,buf,10);
		strcat(dates,"\0");
		cat->date[i] = (char*) malloc(sizeof(char)*11);
		strcpy(cat->date[i],dates);

		//Traitement du type :
        ret = strchr(buf,',')+1;
        ret2 = strchr(ret,','); 
		*ret2 = '\0';
		cat->type[i] = (char*) malloc(sizeof(char)*8);
        strcpy(cat->type[i],(char*) ret);

        //Traitement du destinataire :
        ret = ret2+1;
        ret2 = strchr(ret,',');
		*ret2 = '\0';
		cat->endroit[i] = (char*) malloc(sizeof(char)*50);
        strcpy(cat->endroit[i],(char*) ret);

        //Traitement du montant :
        ret = ret2+1;
		ret2 = memchr(ret,(int)'\n', 50);
		*ret2 = '\0';
        cat->montant[i] = atof(ret);
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
	//Cette inversion doit être faite pour tous les attributs de la structure donnée en argument

	int mt,a,j,m;								//montant, année, jour, mois
	char *d = (char*) malloc(sizeof(char)*11);  //date
	char *t = (char*) malloc(sizeof(char)*8);	//type
	char *e = (char*) malloc(sizeof(char)*50);	//endroit

	//Inversion des années :
	a = cat->annee[i+1];
	cat->annee[i+1] = cat->annee[i];
	cat->annee[i] = a;

	//Inversion des mois :
	m = cat->mois[i+1];
	cat->mois[i+1] = cat->mois[i];
	cat->mois[i] = m;

	//Inversion des jours :
	j = cat->jour[i+1];
	cat->jour[i+1] = cat->jour[i];
	cat->jour[i] = j;

	//Inversion des dates :
	strcpy(d,cat->date[i+1]);
	strcpy(cat->date[i+1],cat->date[i]);
	strcpy(cat->date[i],d);

	//Inversion des types :
	strcpy(t,cat->type[i+1]);
	strcpy(cat->type[i+1],cat->type[i]);
	strcpy(cat->type[i],t);

	//Inversion des destinataires :
	strcpy(e,cat->endroit[i+1]);
	strcpy(cat->endroit[i+1],cat->endroit[i]);
	strcpy(cat->endroit[i],e);

	//Inversion des montants :
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

	//On remplit les attribut jour,mois et annee de cat
	for (i=0;i<cat->nbelements;i++) {   
		dateJ = (char*) calloc(11,sizeof(char));
		ret = (char*) calloc(11,sizeof(char));
		ret2 = (char*) calloc(11,sizeof(char));
		strcpy(dateJ,cat->date[i]);

		//Détermination du jour :
        strncpy(ret,dateJ,2);
        cat->jour[i] = atoi(ret);

        //Détermination du mois :
        ret = strchr(dateJ,'/')+1;
        ret2 = strchr(ret,'/');
        *ret2 = '\0';
        cat->mois[i] = atoi(ret);

        //Détermination de l'année :
        ret = ret2+1;
        cat->annee[i] = atoi(ret);
	}

	int j=0;      //Nous permet de faire les boucles jusqu'à ce que tout le tableau soit trié
	//Tri par année
	while (j==0) {
		j=1;
		for (i=0;i<cat->nbelements-1;i++) {  
			if (cat->annee[i+1]<cat->annee[i]) {
				triChrono(cat,i);
				j=0;
			}
		}
	}

	j=0;
	//Tri par mois à année constante
	while (j==0) {
		j=1;
		for (i=0;i<cat->nbelements-1;i++) {  
			if (cat->mois[i+1]<cat->mois[i] && cat->annee[i+1]==cat->annee[i]) {
				triChrono(cat,i);
				j=0;
			}
		}
	}

	j=0;
	//Tri par jour à mois et année constants
	while (j==0) {
		j=1;
		for (i=0;i<cat->nbelements-1;i++) {    
			if (cat->jour[i+1]<cat->jour[i] && cat->mois[i+1]==cat->mois[i] && cat->annee[i+1]==cat->annee[i]) {
				triChrono(cat,i);
				j=0;
			}
		}
	}
}

void triCatDates(catTree1 *cat) {
	//Trie chronologiquement les opérations de la catégorie donnée en argument, 
	//i.e. de toutes ses sous-catégories
	
	int i;
	//L'algorithme de tri est implémenté dans une autre fonction ; on l'appelle pour chaque sous-catégorie
	for (i=0;i<cat->nbelements;i++) {
		triSsCatDates(cat->subcat[i]);
	}
	save(cat);
}