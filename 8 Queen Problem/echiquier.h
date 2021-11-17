#ifndef __echiquier__
#define __echiquier__

typedef enum{
    A1,B1,C1,D1,E1,F1,G1,H1,
    A2,B2,C2,D2,E2,F2,G2,H2,
    A3,B3,C3,D3,E3,F3,G3,H3,
    A4,B4,C4,D4,E4,F4,G4,H4,
    A5,B5,C5,D5,E5,F5,G5,H5,
    A6,B6,C6,D6,E6,F6,G6,H6,
    A7,B7,C7,D7,E7,F7,G7,H7,
    A8,B8,C8,D8,E8,F8,G8,H8
}Case;

typedef long long Position;



int est_case_occupee(Position pos, Case c);
/*
 * Description :
 *		La fonction parcours chaque bit de l'entier pos
 *		pour vérifier si une case est occupée par une dame ou non.
 * Parametre :
 *		Une variable pos de type Position
 *		Une variable c de type énuméré Case
 * Retour :
 *		1 si la case c de la position pos est
 *		occupée par une dame.
 *		0 sinon
*/
void allumer_bit(Position *pos, Case i);
/*
 * Description :
 *		La fonction allume un bit d'un entier binaire.
 * Parametre :
 *		Un pointeur vers une variable de type Position
 *		Une variable de type énuméré Case
 * Retour :
 		void
*/

void eteindre_bit(Position *pos, Case i);
/*
 * Description :
 *		La fonction eteins un bit d'un entier binaire.
 * Parametre :
 *		Un pointeur vers une variable de type Position
 *		Une variable de type énuméré Case
 * Retour :
 *		void
*/

void placer_dame_position(Position *pos, Case c);
/*
 * Description :
 *		modifie la position pointée par pos pour qu'elle y ajoute
 *		une dame sur la case i.
 * Parametre :
 *		Un pointeur vers une variable de type Position
 *		Une variable de type énuméré Case
 * Retour :
 *		void
*/

void affiche_ligne_bit(Position pos, Case c);
/*
 * Description :
 *		affiche dans le terminale 8 bits d'un entier pos à 64 bits
 *		selon la case choisi.
 * Parametre :
 *		Une variable pos de type position à afficher.
 *		Variable c de type Case.
 * Retour :
 *		void
*/

int afficher_position(Position pos);

/*
 * Description :
 *		affiche un entier binaire à 64 bits, l'affichage
 *		respectera la norme d'un échiquier (A1, A2... H8)
 * Parametre :
 *		Une variable pos de type position à afficher.
 *		Variable c de type Case.
 * Retour :
 		1 si l'affichage s'est bien effectué
 		0 sinon
*/

#endif
