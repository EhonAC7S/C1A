#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE* fichier = NULL;
	char date[10] = "";
	char moyen[7] = "";
	char dest[10] = "";
	double prix;
	char cat[12] = "";
	char cont='y';
	int i = 0;
	char c;
	fichier = fopen("releve","r");
	if (fichier==NULL) {
		printf("Entrez vos transactions avant !");
	}
	else {
//		while (cont == 'y') {
//			fscanf(fichier,"%s,%s,%s,%lf,%s \n",date,moyen,dest,&prix,cat);
//			//fscanf(fichier,"%s,",date);
//			printf("|%s|,%s|,%s|,%.2f|,%s| \n|",date,moyen,dest,prix,cat);
//			//printf("%s \n",date);
//			printf("Continuer? (y/n) : ");
//			scanf("%s",&cont);
//		} //ne fonctione pas correctement
		c=fgetc(fichier);
		do {
			while (c!=',') {
				date[i++]=c;
				fgetc(fichier);
			}
			i=0;
			while ((c=fgetc(fichier))!=',') {
				moyen[i++] = c;
			}
			i=0;
			while ((c=fgetc(fichier))!=',') {
				dest[i++] = c;
				//i++;
			}
			fscanf(fichier,"%lf,",&prix);
			i=0;
			while ((c=fgetc(fichier))!='\n') {
				cat[i++] = c;
				//i++;
			}
			printf("%s,%s,%s,%.2f,%s \n",date,moyen,dest,prix,cat);
		} 
		while ((c=fgetc(fichier))!=EOF);
	}
	fclose(fichier);
	return ;
}
