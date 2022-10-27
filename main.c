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



int main() {

    int colonne, ligne;

    Grille grille;
    initGrille(grille);
    jouer(grille, 'X', &colonne, &ligne);
    printf("%i %i", colonne, ligne);

    return 0;
}
