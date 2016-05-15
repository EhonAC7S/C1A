#include <stdio.h>
#include <string.h>
#include "fichiers.h"

/* Foarmat des fichiers : ils doivent contenir :
    date de la dépense
    montant
    endroit
    id ?

Un fichier par type de dépense ? -> les ranger dans un dossier

Début du fichier : seuil à ne par dépasser (par semaine ou mois) ;
        -> alerte lorsque l'on s'approche du seuil d'un certain pourcentage
                    dépense totale actuelle

Un fichier pour les revenus avec en début de fichier la somme présente sur le compte
*/

int save(char fichier[]) {
    FILE *fp;

    fp = fopen(fichier,"w");
    //On utilise fputs("",fp); pour écrire des trucs
    fclose(fp);

    return 0;
}

struct categorie load(char fichier[]) {   //renvoie la structure contenant la catégorie chargée depuis le fichier donné
	struct categorie cat; //structure que l'on crée
	strcpy(cat.nom,fichier);
    FILE *fp;

    fp = fopen(fichier,"r");
    // fgetc() pour lire des caractères, fgets( char *buf, int n, FILE *fp ) pour des chaines
    // fgets() lit n caractères ou jusqu'au \n
    int i=0;
    char buf[255];
    char *ret;
    char *ret2;
    while (!feof(fp)) { //tant qu'on n'est pas à la fin du fichier
    	printf("Hey");
        fgets(buf,2515,fp);
        strncpy(cat.date[i],buf,10); //copie les 10 premiers caractères de buf dans cat.dates[i]
        ret = strchr(buf, 11);
        ret2 = memchr(ret, ',', 20);
        strcpy(cat.type[i],ret[0,ret2-ret]);
        ret = ret2;
        ret2 = memchr(ret, ',', 50);
        strcpy(cat.endroit[i],ret[0,ret2-ret]);
        ret = ret2;
        ret2 = memchr(ret, '\n', 20);
        cat.montant[i] = (float) ret[0,ret2-ret];
        i++;
    }
    fclose(fp);

    return cat;
}
