#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fichiers.h"

/*
Projet de C
Fonctionnalités du programme :
    - classifier dépenses et revenus : charges immobilières, habillement... (sous-catégories possibles)
    - fournir statistiques sur les dépenses/revenus mensuels (eventuellement graphiques)
            -> chercher une librairie du type matplotlib pour python
    - définir un budget max par poste de dépense et être allerté dès qu'on s'approche du seuil
    - sauvegarder les données dans des fichiers
*/

int main (int argc, char *argv[])  {
	struct releve rel;
	rel = load("test");
	tri(rel);
	return 0;
}
