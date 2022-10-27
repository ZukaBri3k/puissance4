#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//on définit les dimensions de la grille si l'on veut la modifier ainsi que les constantes
#define NB_LIGNE 6
#define NB_COLONNE 7
const char VIDE = ' ';
const char PION_A = 'X';
const char PION_B = 'O';
const int COLONNE_DEP = NB_COLONNE / 2;

//déclaration du type de grille ainsi que des fonctions et procédures
typedef char Grille[NB_LIGNE][NB_COLONNE];
void initGrille(Grille grille);
void afficherGrille(Grille t, char  pion, int colonne);
bool grillePleine(Grille grille);
int trouverLigne(Grille grille, int colonne);
int choisirColonne(Grille grille, char pion, int colonne);
void jouer(Grille grille, char pion, int *colonne, int *ligne);

//procédure d'initialisation de la grille
void initGrille(Grille grille) {
    int i,j;
    //on parcours les lignes de la grille
    for (i=0;i<NB_LIGNE;i++) {
        //on parcours les colonnes de la grille
        for (j = 0; j < NB_COLONNE; j++){
            //on assigne la valeur vide
            grille[i][j] = VIDE;
        }
    }
    grille[5][0] = 'O';
    grille[4][0] = 'O';
    grille[3][0] = 'O';
    grille[2][0] = 'O';
    grille[1][0] = 'O';
    grille[0][0] = 'O';
    grille[5][1] = 'O';

}

//procédure d'affichage de la grille
void afficherGrille(Grille t, char pion, int colonne){
    //permet de centrer le pion au dessus de la grille en fonction de la colonne
    for (int i = 1; i < colonne; ++i) {
        printf("    ");
    }
    printf("  %c\n\n",pion);
    //permet d'afficher une ligne en fonction du nombre de colonne de la grille et de la grille
    for (int i=0;i<NB_LIGNE;i++) {
        printf("=");
        for (int j = 0; j < NB_COLONNE; j++){
            printf("====");
        }
        printf("\n");
        for (int j = 0; j < NB_COLONNE; j++){
            printf("= %c ", t[i][j]);
        }
        printf("=\n");
    }
    printf("=");
    for (int j = 0; j < NB_COLONNE; j++){
        printf("====");
    }
    printf("\n");
}

//permet de tester si la grille est pleine
bool grillePleine(Grille grille) {
    bool pleine = true;
    int i = 0, j = 0;
    //on parcours la grille tant que l'on n'a pas trouvé de VIDE
    while (i < NB_LIGNE && pleine == true) {
        while (j < NB_COLONNE && pleine == true) {
            //Si l'on trouve un VIDE on stop la boucle
            if (grille[i][j] == ' '){
                pleine = false;
            }
            j++;
        }
        i++;
    }
    //renvoie true si la grille est pleine sinon renvoie false
    if (pleine == true){
        return true;
    } else {
        return false;
    }
}

//permet de trouver la première ligne vide d'une colonne
int trouverLigne(Grille grille, int colonne){
    int ligneVide = -1, i = 0;
    bool estRemplie = false;
    //on parcours la colonne tant que l'on n'a pas trouvé de caractère différent de VIDE
    while(i < NB_LIGNE && estRemplie == false) {
        //si l'on en trouve un on définit la dernière ligne vide de la colonne comme étant la précédente
        if(grille[i][colonne-1] != ' '){
            ligneVide = i-1;
            estRemplie = true;
        }
        i++;
    }
    //si la ligne vide est toujours à -1 et que l'on n'a pas trouvé de caractères autre que VIDE on retourne la
    //première ligne de la grille
    if(ligneVide == -1 && estRemplie == false){
        return NB_LIGNE-1;
    }else {
        //sinon on retourne la ligne trouvée
        return ligneVide;
    }
}

//permet de laisser l'utilisateur de choisir sa colonne
int choisirColonne(Grille grille, char pion, int colonne){
    char choix;
    bool continuer = true;
    int numLigne;
    do {
        //laisse l'utilisateur choisir sa colonne
        afficherGrille(grille, pion, colonne);
        printf("Utilisez 'q' et 'd' pour deplacer votre pion\n");
        scanf("%c", &choix);

        //on vérifie que l'utilisateur ne dépasse pas les limites de la grille
        if(choix == 'q' && colonne > 1){
            colonne -= 1;
        }else if(choix == 'd' && colonne < NB_COLONNE){
            colonne += 1;
        }
        //on cherche la ligne disponible dans la colonne
        numLigne = trouverLigne(grille, colonne);
        //si la colonne est pleine on laisse tourner la boucle
        if(choix == ' ' && numLigne != -1){
            continuer = false;
        } else {
            //sinon on stop la boucle
            continuer = true;
        }

    } while (continuer == true);
    return colonne;
}



int main() {

    int colonne, ligne;

    Grille grille;
    initGrille(grille);
    jouer(grille, 'X', &colonne, &ligne);
    printf("%i %i", colonne, ligne);

    return 0;
}
