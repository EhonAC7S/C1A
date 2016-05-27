#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include "fichiers.h"


int save(struct categorie *cat) {
	//Sauvegarde les données d'une catégorie (notamment utilisé par la fonction tri())

	FILE *fp;

	//mkdir("fichierTries",EEXIST);  //ne fait rien si le dossier existe, renvoie une erreur de segmentation sinon...

	char *fichier;
	fichier = (char*) malloc(sizeof(char)*50);
	strcpy(fichier,"fichiersTries/");
	strcat(fichier,cat->nom);

	fp = fopen(fichier,"w+");
	//On utilise fputs("",fp); pour écrire des trucs
	int i;
	char *chaine=(char*) malloc(sizeof(char)*255);

	for (i=0;i<cat->nbelements;i++) {//for (i=0;i<sizeof(cat.date);i++) {
		strcpy(chaine,cat->date[i]);
		strcat(chaine,",");
		strcat(chaine,cat->type[i]);
		strcat(chaine,",");
		strcat(chaine,cat->endroit[i]);
		strcat(chaine,",");
		char str[20];
		sprintf(str, "%.2f",cat->montant[i]);
		strcat(chaine,str);
		strcat(chaine,"\n");
		fputs(chaine,fp);
	}

	fclose(fp);
	free(fichier);
	free(chaine);
	return 0;
}


struct releve load(char *fichier) {   
	//Renvoie une structure contenant tous les éléments du relevé

	struct releve cat; //structure que l'on crée
	strcpy(cat.nom,fichier);
	FILE *fp;

	fp = fopen(fichier,"r");
	// fgetc() pour lire des caractères, fgets( char *buf, int n, FILE *fp ) pour des chaines
	// fgets() lit n caractères ou jusqu'au \n
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
		cat.date[i] = (char*) malloc(sizeof(char)*11);
		strcpy(cat.date[i],dates);
        ret = strchr(buf,',')+1;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 20);
		*ret2 = '\0';
		cat.type[i] = (char*) malloc(sizeof(char)*8);
        strcpy(cat.type[i],(char*) ret);
        ret = ret2+1;
        ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 50);
		*ret2 = '\0';
		cat.endroit[i] = (char*) malloc(sizeof(char)*50);
        strcpy(cat.endroit[i],(char*) ret);
        ret = ret2+1;
        ret2 = strchr(ret,',');
		*ret2 = '\0';
        cat.montant[i] = atof(ret);
		ret = ret2+1;
        ret2 = memchr(ret,(int)'\n', 50);
		*ret2 = '\0';
		cat.categorie[i] = (char*) malloc(sizeof(char)*20);
		strcpy(cat.categorie[i],(char*) ret);
        i++;
		fgets(buf,255,fp);
	}

	fclose(fp);
	cat.nbelements = i;

	return cat;
}

int saveCat(char *cat) {
	FILE *fp;

	fp = fopen("fichiersTries/categories","w+");
	strcat(cat,"\n");
	fputs(cat,fp);

	fclose(fp);
	return 0;
}



/*
int creerCatgorieUt() {
	FILE* fichier = NULL;
	double seuil;
	char cat[20] = "";
	char souscat[20] = "";
	char cont='y';
	char chaine[1000] = "";
	fichier = fopen("catégorie.info","a+");
	while (fgets(chaine, 1000, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
        }
 
        fclose(fichier);
	printf("Veuillez suivre les instructions suivantes : ");
	do {
		printf(" ");
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
}*/
	//revoir la conception de la gestion de l'architecture des categories! plutot voir cela comme un arbre a 3 niveaux
	//gestion de la sauvegarde d'un arbre en memoire dans un fichier texte (parcours en profondeur)

