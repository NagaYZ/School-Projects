#ifndef __attaque__
#define __attaque__

#include "echiquier.h"

int calculer_cases_attaques(Position *pos, Case c);
/*
 * Description :
 *		modifie la position pointée par pos pour qu'elle contienne
 *		exactement les cases attaquées par une dame située sur la case c.
 * Parametre :
 *		Un pointeur vers une variable de type Position
 *		Une variable de type énuméré Case
 * Retour :
 		1 si le calcul s'est bien effectué
 		0 sinon
*/

int test_bin_egaux(Position p1, Position p2);
/*
 * Description :
 *		Test si deux entiers binaires ont au moins une case commune égale à 1
 * Parametre :
 *		Deux variable Position.
 * Retour :
 		1 Si une des cases communes est allumé à 1.
 		0 sinon
*/

int est_sans_attaque_mutuelle(Position pos);
/*
 * Description :
 *		Test si les dames attaquent ou non les autres pions placé dans
 *		pos.
 * Parametre :
 *		Une variable pos contenant les dames à tester
 * Retour :
 		1 si les dames ne s'attaquent pas entre elles
 		0 sinon
*/
#endif
