#include <stdlib.h>
#include <stdio.h>
#include "menus.h"

void accueil() {
    int choix;
    printf("    Bienvenue sur notre application de gestion de budgets. \n\n\n");
    printf("1. Calcul des transactions\n");
    printf("2. Paramètres\n");
    printf("3. Quitter le programme\n");
    printf("Entrez une valeur : ");
    scanf("%d\n\n\n",&choix);
    //system("clear");   // system("cls"); avec Windows   //Nécessite un terminal pour fonctionner
    switch(choix) {
        case 1 :
            transactions();
            break;
        case 2 :
            parametres();
            break;
        case 3 :
            break;
        default :
            accueil();
    }
}

void transactions() {

}

void parametres() {
}
