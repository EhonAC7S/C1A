#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichiers.h"

/*
Un fichier par type de dépense ? -> les ranger dans un dossier

Début du fichier : seuil à ne par dépasser (par semaine ou mois) ;
        -> alerte lorsque l'on s'approche du seuil d'un certain pourcentage
                    dépense totale actuelle

Un fichier pour les revenus avec en début de fichier la somme présente sur le compte
*/

int save(struct releve cat) {
	FILE *fp;

	fp = fopen(cat.nom,"w");
	//On utilise fputs("",fp); pour écrire des trucs
	int i;
	char chaine[255];
	while (cat.montant[i]!=0.) {//for (i=0;i<sizeof(cat.date);i++) {
		strcpy(chaine,cat.date[i]);
		strcat(chaine,",");
		strcat(chaine,cat.type[i]);
		strcat(chaine,",");
		strcat(chaine,cat.endroit[i]);
		strcat(chaine,",");
		char str[20];
		sprintf(str, "%.2f", cat.montant[i]);
		strcat(chaine,str);
		strcat(chaine,"\n");
		fputs(chaine,fp);
		i++;
	}
	fclose(fp);

	return 0;
}

struct releve load(char *fichier) {   //renvoie la structure contenant la catégorie chargée depuis le fichier donné
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
	char dates[10];
	fgets(buf,255,fp);  //Les fgets doivent être faits avant de vérifier que l'on n'est pas à la fin du fichier (-> seg fault sinon)
	while (!feof(fp)) { //tant qu'on n'est pas à la fin du fichier
		strncpy(dates,buf,10); //copie les 10 premiers caractères de buf dans cat.dates[i]
		strcat(dates,"\0");
		strcpy(cat.date[i],dates);
        	ret = strchr(buf,',')+1;
        	ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 20);
		*ret2 = '\0';
        	strcpy(cat.type[i],(char*) ret);
        	ret = ret2+1;
        	ret2 = strchr(ret,',');  //ou : memchr(ret, (int) ',', 50);
		*ret2 = '\0';
        	strcpy(cat.endroit[i],(char*) ret);
        	ret = ret2+1;
        	ret2 = strchr(ret,',');
		*ret2 = '\0';
        	cat.montant[i] = atof(ret);
		ret = ret2+1;
        	ret2 = memchr(ret,(int)'\n', 50);
		strcpy(cat.categorie[i],(char*) ret);
        	i++;
		fgets(buf,255,fp);
	}
	fclose(fp);
	return cat;
}

int tri(struct releve rel) {
	struct categorie cat[20];
	int nbcat = 0; //nb de categories dans cat
	int i,j,k;
	int trouve = 0;
	char *categorie;
	for (i=0;i<sizeof(rel.date);i++) { //On parcourt tous les éléments chargés
		strcpy(categorie,rel.categorie[i]);
		for (j=0;j<nbcat;j++) {
			if (strcmp(cat[j].nom,categorie) == 0) {
				k = cat[j].nbelements+1;
				cat[j].date[k]=rel.date[i];
				cat[j].type[k]=rel.type[i];
				cat[j].endroit[k]=rel.endroit[i];
				cat[j].montant[k]=rel.montant[i];
				cat[j].nbelements++;
				trouve = 1;
			}
		}
		if (trouve == 0) { //si la categorie n'existe pas encore dans cat
			cat[nbcat].nom = categorie;
			cat[nbcat].date[cat[nbcat].nbelements+1]=rel.date[i];
			cat[nbcat].type[cat[nbcat].nbelements+1]=rel.type[i];
			cat[nbcat].endroit[cat[nbcat].nbelements+1]=rel.endroit[i];
			cat[nbcat].montant[cat[nbcat].nbelements+1]=rel.montant[i];
			cat[nbcat].nbelements++;
			nbcat++;
		}
		trouve = 0;
	}
	// À partir d'ici, les transactions sont classées et on n'a plus qu'à les sauvegarder dans les dossiers du nom de la categorie
	for (i=0;i<nbcat;i++) {
		save(cat[i]);
	}
	return 0;
}
