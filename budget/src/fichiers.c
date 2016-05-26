#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichiers.h"


int save(struct categorie cat) {
	//Sauvegarde les données d'une catégorie (notamment utilisé par la fonction tri())

	FILE *fp;
	
	char *fichier;
	strcpy(fichier,"fichiersTries/");
	strcat(fichier,cat.nom);

	fp = fopen(fichier,"w");
	//On utilise fputs("",fp); pour écrire des trucs
	int i=0;
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
		*ret2 = '\0';
		strcpy(cat.categorie[i],(char*) ret);
        	i++;
		fgets(buf,255,fp);
	}

	fclose(fp);
	cat.nbelements = i;

	return cat;
}


int tri() {
	// Range les opérations dans les fichiers correspondant à leur catégorie

	struct releve rel;
	rel = load("releve");

	struct categorie cat[20];
	int nbcat = 0; //nb de categories dans cat
	int i,j,k;
	int trouve = 0;
	char categorie[20];

	for (i=0;i<rel.nbelements;i++) { //On parcourt tous les éléments chargés
		strcpy(categorie,rel.categorie[i]);
		for (j=0;j<nbcat;j++) {
			if (strcmp(cat[j].nom,categorie) == 0) {
				k = cat[j].nbelements;
				strcpy(cat[j].date[k],rel.date[i]);    //Encore une fois : c'est strcpy et pas =... --'
				strcpy(cat[j].type[k],rel.type[i]);
				strcpy(cat[j].endroit[k],rel.endroit[i]);
				cat[j].montant[k] = rel.montant[i];
				(cat[j].nbelements)++;
				trouve = 1;
			}
		}
		if (trouve == 0) { //si la categorie n'existe pas encore dans cat
			strcpy(cat[nbcat].nom,categorie);
			strcpy(cat[nbcat].date[cat[nbcat].nbelements],rel.date[i]);
			strcpy(cat[nbcat].type[cat[nbcat].nbelements],rel.type[i]);
			strcpy(cat[nbcat].endroit[cat[nbcat].nbelements],rel.endroit[i]);
			cat[nbcat].montant[cat[nbcat].nbelements]=rel.montant[i];
			cat[nbcat].nbelements++;
			nbcat++;
		}
		trouve = 0;
	}

	// À partir d'ici, les transactions sont classées et on n'a plus qu'à les sauvegarder dans les dossiers du nom de la categorie
	for (i=0;i<nbcat;i++) {
		save(cat[i]);
	}

	return 0;   //On peut changer ça et mettre void à la fonctions je pense...
}

int saisirReleve() {
	FILE* fichier = NULL;	
	char date[10] = "";
	char moyen[7] = "";
	char dest[20] = "";
	double prix;
	char cat[20] = "";
	char cont='y';
	fichier = fopen("releve","a+");
	printf("Veuillez suivre les instructions suivantes : ");
	do {
		printf("Entrez une date de la forme : jj/mm/aaaa : ");
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

