#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#define TAILLE 8

void init_plateau();
/*
 * Description :
 *		Initialise le plateau de jeu sur la fenetre graphique
 * Pas de parametre
 * Pas de valeur de retour
*/

void afficher_dame(int x, int y);
/*
 * Description :
 *		Affiche une dame aux coordonnes x et y sur le plateau
 * Parametre :
 *		Un entier x
 *		Un entier y
 * Pas de valeur de retour
*/

void effacer_dame(int x, int y);
/*
 * Description :
 *		Efface une dame aux coordonnes x et y sur le plateau
 * Parametre :
 *		Un entier x
 *		Un entier y
 * Pas de valeur de retour
*/
#endif
