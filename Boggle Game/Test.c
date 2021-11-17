#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Test.h"
#include "Jeu.h"
#include "Grille.h"
#include "Dico.h"

int test_ajout_lettre()
{
    Mot liste = NULL;
    ajouter_lettre(&liste,'b',0,0);
    ajouter_lettre(&liste,'c',0,0);
    ajouter_lettre(&liste,'d',0,0);

    if(liste->lettre == 'b' && liste->suivant->lettre=='c' && liste->suivant->suivant->lettre=='d')
        return 1;
    else
        return 0;
}

int test_longueur_mot()
{
    Mot liste = NULL;
    ajouter_lettre(&liste,'b',0,0);
    ajouter_lettre(&liste,'c',0,0);
    if(longueur_mot(liste) == 2)
        return 1;
    else
        return 0;
}

int test_retirer_derniere_lettre()
{
    Mot liste = NULL;
    ajouter_lettre(&liste,'b',0,0);
    ajouter_lettre(&liste,'c',0,0);
    ajouter_lettre(&liste,'d',0,0);
    retirer_derniere_lettre(&liste);

    if(liste->lettre == 'b' && liste->suivant->lettre == 'c' && liste->suivant->suivant == NULL)
        return 1;
    else
        return 0;
}

int test_ajout_mot_dico()
{
    Dico dico = NULL;
    ajout_mot_dico(&dico,"ba");
    if(recherche_mot_dico(dico,"ba"))
        return 1;

    return 0;
}

int test_recherche_mot_dico()
{
    Dico dico = NULL;
    ajout_mot_dico(&dico,"ba");
    if(recherche_mot_dico(dico,"ba"))
        return 1;

    return 0;
}

int test_mot_valide()
{
    Dico dico = NULL;
    Dico dico_found = NULL;
    Mot liste = NULL;
    ajout_mot_dico(&dico, "lol");
    ajouter_lettre(&liste,'l',0,0);
    ajouter_lettre(&liste,'o',0,1);
    ajouter_lettre(&liste,'l',0,2);

    if(mot_valide(liste , dico, &dico_found))
       
            return 1;
    return 0;    
}
void test()
{
    if (test_ajout_lettre())
        printf("test_ajout_lettre : success \n");
    else
        printf("test_ajout_lettre : failed \n");

    if (test_longueur_mot())
        printf("test_longueur_mot : success \n");
    else
        printf("test_longueur_mot : failed \n");

    if(test_retirer_derniere_lettre())
        printf("test_retirer_derniere_lettre : success \n");
    else
        printf("test_retirer_derniere_lettre : failed \n");

    if(test_ajout_mot_dico())
        printf("test_ajout_mot_dico : success \n");
    else
        printf("test_ajout_mot_dico : failed \n");

    if(test_recherche_mot_dico())
        printf("test_recherche_mot_dico : success \n");
    else
        printf("test_recherche_mot_dico : failed \n");

     if(test_mot_valide())
        printf("test_mot_valide : success \n");
    else
        printf("test_mot_valide : failed \n");

}
