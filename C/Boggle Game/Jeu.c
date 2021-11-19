#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <ncurses.h>
#include "Jeu.h"

Mot allouerLettre(char c, int x, int y)
{
    assert(x<H && x>=0);
    assert(y<L && y>=0);
    assert(c);

    Mot liste = (Mot) malloc(sizeof(Liste_l));
    if(NULL != liste)
    {
        liste->lettre=c;
        liste->x=x;
        liste->y=y;
        liste->suivant=NULL;
        return liste;
    }
    fprintf(stderr, "allocation impossible\n" );
    exit(1);
}

void ajouter_lettre(Mot* liste, char c, int x, int y)
{
    assert(x<H && x>=0);
    assert(y<L && y>=0);
    assert(c);
    c = tolower(c);
    if(*liste == NULL)
        *liste = allouerLettre(c, x, y);
    else
    {
        Mot tmp;
        tmp=*liste;
        while(tmp->suivant != NULL)
        {
            tmp=tmp->suivant;
        }
        tmp->suivant = allouerLettre(c, x, y);
    }
}

int* retirer_derniere_lettre(Mot* liste)
{
    static int coord[2];/*sert a stocker les coordonnees de la derniere lettre*/

    Mot tmp, precedent;
    tmp = *liste;
    if(tmp->suivant == NULL){/*si on enleve la racine*/
        coord[0]=tmp->x;
        coord[1]=tmp->y;
        free(*liste);
        *liste=NULL;
        return coord;
    }
    while(tmp->suivant != NULL)
    {
        precedent = tmp;
        tmp = tmp->suivant;
    }

    coord[0]=tmp->x;
    coord[1]=tmp->y;
    precedent->suivant=NULL;
    free(tmp);
    tmp=NULL;
    return coord;
}
void annuler_coup(Grille grille, Mot* liste)
{
    assert(grille);
    if(*liste == NULL)
        return;

    int* coord;
    coord=retirer_derniere_lettre(liste);
    enlever_rouge(grille , coord[0], coord[1]);
}

int mot_valide(Mot liste, Dico dico, Dico* dico_mot_trouver){

    char buffer[H*L];
    int buffer_size;
    buffer_size=0;
    while(liste != NULL)
    {
        buffer[buffer_size]=liste->lettre;
        liste = liste->suivant;
        buffer_size++;
    }
    buffer[buffer_size]='\0';
    if(recherche_mot_dico(dico, buffer) && !recherche_mot_dico(*dico_mot_trouver, buffer)){
        ajout_mot_dico(dico_mot_trouver, buffer);
        return 1;
    }
    return 0;
}

int longueur_mot(Mot liste)
{
    int compteur;
    compteur=0;
    while(liste->suivant != NULL)
    {
        liste = liste->suivant;
        compteur++;
    }
    compteur++;
    return compteur;
}
