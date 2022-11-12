#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//on définit les dimensions de la grille si l'on veut la modifier ainsi que les constantes
#define NB_LIGNE 6
#define NB_COLONNE 7
const char VIDE = ' ';
const char INCONNU = ' ';
const char PION_A = 'X';
const char PION_B = 'O';
const int COLONNE_DEP = (NB_COLONNE / 2) + 1;

//déclaration du type de grille ainsi que des fonctions et procédures
typedef char Grille[NB_LIGNE][NB_COLONNE];
void initGrille(Grille grille);
void afficherGrille(Grille t, char  pion, int colonne);
bool grillePleine(Grille grille);
int trouverLigne(Grille grille, int colonne);
int choisirColonne(Grille grille, char pion, int colonne);
void jouer(Grille grille, char pion, int *colonne, int *ligne);
bool estVainqueur(Grille g, int ligne, int colonne);
void finDePartie(char pionGagnant);

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
    printf("Utilisez 'q' et 'd' pour deplacer votre pion\n");
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


        scanf("%c", &choix);

        //on vérifie que l'utilisateur ne dépasse pas les limites de la grille
        if(choix == 'q' && colonne > 1){
            colonne -= 1;
            afficherGrille(grille, pion, colonne);
        }else if(choix == 'd' && colonne < NB_COLONNE){
            colonne += 1;
            afficherGrille(grille, pion, colonne);
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

//permet faire jouer le tour du joueur
void jouer(Grille grille, char pion, int *colonne, int *ligne){
    //on laisse le joueur choisir sa colonne
    *colonne = choisirColonne(grille, pion, COLONNE_DEP);
    *ligne = trouverLigne(grille, *colonne);
    //quand la colonne choisie est valide on ajoute le pion du joueur dans la grille
    grille[*ligne][*colonne-1] = pion;
}

bool estVainqueur(Grille grille, int ligne, int colonne) {
    int pionConsecu = 1, i = ligne, j = colonne - 1;
    char caracRef = grille[ligne][colonne - 1];
    char pionCourrant = caracRef;

    //test d'un puissance 4 en ligne
    while(pionCourrant == caracRef && pionConsecu < 4 && j < NB_COLONNE - 1) {
        j++;
        pionCourrant = grille[i][j];
        if(pionCourrant == caracRef) {
            pionConsecu++;
        }
    }
    pionCourrant = caracRef;
    j = colonne - 1;
    while(pionCourrant == caracRef && pionConsecu < 4 && j >= 0) {
        j--;
        pionCourrant = grille[i][j];
        if(pionCourrant == caracRef) {
            pionConsecu++;
        }
    }
    //si aucun puissance 4 horizontal detecte on recherche verticalement
    if(pionConsecu != 4) {
        pionConsecu = 1;
        pionCourrant = caracRef;
        i = ligne;
        j = colonne - 1;

        while(pionCourrant == caracRef && pionConsecu < 4 && i < NB_LIGNE - 1) {
            i++;
            pionCourrant = grille[i][j];
            if(pionCourrant == caracRef) {
                pionConsecu++;
            }
        }
        pionCourrant = caracRef;
        i = ligne;
        while(pionCourrant == caracRef && pionConsecu < 4 && i >= 0) {
            i--;
            pionCourrant = grille[i][j];
            if(pionCourrant == caracRef) {
                pionConsecu++;
            }
        }
    }
    //on recherche un puissance 4 dans la diagonale vers la droite
    if(pionConsecu != 4) {
        pionConsecu = 1;
        pionCourrant = caracRef;
        j = colonne - 1;
        i = ligne;

        while(pionCourrant == caracRef && pionConsecu < 4 && i < NB_LIGNE - 1 && j < NB_COLONNE - 1){
            i++;
            j++;
            pionCourrant = grille[i][j];
            if(pionCourrant == caracRef) {
                pionConsecu++;
            }
        }
        pionCourrant = caracRef;
        j = colonne - 1;
        i = ligne;

        while(pionCourrant == caracRef && pionConsecu < 4 && i > 0 && j > 0){
            i--;
            j--;
            pionCourrant = grille[i][j];
            if(pionCourrant == caracRef) {
                pionConsecu++;
            }
        }
    }
    //on recherche un puissance 4 sur la diagonale droite
    if(pionConsecu != 4) {
        i = ligne;
        j = colonne - 1;
        pionConsecu = 1;
        pionCourrant = caracRef;

        while(pionCourrant == caracRef && pionConsecu < 4 && i < NB_LIGNE - 1 && j > 0) {
            i++;
            j--;
            pionCourrant = grille[i][j];
            if(pionCourrant == caracRef){
                pionConsecu++;
            }
        }

        i = ligne;
        j = colonne - 1;
        pionCourrant = caracRef;

        while(pionCourrant == caracRef && pionConsecu < 4 && i > 0 && j < NB_COLONNE - 1) {
            i--;
            j++;
            pionCourrant = grille[i][j];
            if(pionCourrant == caracRef){
                pionConsecu++;
            }
        }
    }

    if(pionConsecu == 4) {
        return true;
    } else {
        return false;
    }

}

void finDePartie(char pionGagnant) {
    if(pionGagnant == INCONNU) {
        printf("Match nul !\n");
    } else {
        printf("Le joueur gagnant est le pion %c\n", pionGagnant);
    }
}

int main() {
    char vainqueur;
    int colonne, ligne;
    Grille g;

    initGrille(g);
    vainqueur = INCONNU;
    afficherGrille(g, 'X', COLONNE_DEP);

    while(vainqueur == INCONNU && grillePleine(g) == false) {
        jouer(g, PION_A, &colonne, &ligne);
        afficherGrille(g, PION_B, COLONNE_DEP);
        if(estVainqueur(g, ligne, colonne) == true) {
            vainqueur = PION_A;
        } else if(grillePleine(g) == false) {
            jouer(g, PION_B, &colonne, &ligne);
            afficherGrille(g, PION_A, COLONNE_DEP);
            if(estVainqueur(g, ligne, colonne) == true) {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);

    return 0;
}
