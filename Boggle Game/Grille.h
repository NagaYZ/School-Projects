#ifndef __GRILLE__
#define __GRILLE__
#define H 4
#define L 4
#define POURCENTAGE 100
typedef struct grille_lettre{
	char proba_lettre[POURCENTAGE];/*TABLEAU CONTENANT LES PROBABILITES DES LETTRES (ex: si la lettre 'E' a 11% de chance dapparaitre alors le tableau contiendra 11 fois la lettre 'E'*/
	char tab_lettre[H][L]; /*tableau de lettre représentant la grille*/
	int tab_lettre_rouge[H][L]; /*valeur de 0 ou 1 si la case [i][j] est en rouge*/
}Grille_lettre,*Grille;

Grille alloueGrille();

void Initialiser_lettre_proba(Grille grille);/*rempli le tableau proba_lettre de lettre suivant leur probabilite*/

void Initialiser_grille(Grille grille);/*rempli le tableau tab_lettre de lettre tirer aleatoirement dans proba_lettre*/

void mettre_en_rouge(Grille grille, int x, int y);

void enlever_rouge(Grille grille, int x, int y);

int case_valide(Grille grille, int x1, int y1, int x2, int y2);	/*Renvoie 1 si la case est valide (pas deja ajoutee et si adjacente)*/

#endif
