#ifndef __JEU__
#define __JEU__
#include "Grille.h"
#include "Dico.h"

/*liste chainee simple pour ajouter les lettres choisie une a une ainsi que leurs coordonnee.
et pouvoir facilement retirer le dernier element lorsqu'on annule un coup*/
typedef struct liste_l{
	char lettre;
	int x;
	int y;
	struct liste_l *suivant;
}Liste_l, *Mot;

Mot allouerLettre(char c, int x, int y);

void ajouter_lettre(Mot* liste, char c, int x, int y);/*ajoute une lettre a la liste*/

int* retirer_derniere_lettre(Mot* liste);/*retire le dernier element de la liste et renvoie ses coordonnee dans un tableau. (coord[0]=x,coord[1]=y)*/

void annuler_coup(Grille grille, Mot* liste); /*retire le dernier element de liste_lettre et enleve la rouge pour cet element*/

int mot_valide(Mot liste, Dico dico, Dico* dico_mot_trouve);/*regarde si le mot est dans le dico grace a la fonction recherche et si il na pas deja ete trouver, renvoie 1 si le mot est valide*/

int longueur_mot(Mot liste);/*Retourne la longueur du mot valider*/
#endif
