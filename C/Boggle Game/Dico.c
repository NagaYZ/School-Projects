#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dico.h"

Dico alloueDico(char lettre) {
    Dico nouveau = malloc(sizeof(Dico_mot));

    if (nouveau == NULL) {
        fprintf(stderr, "allocation impossible");
        exit(1);
    }
    nouveau->lettre = lettre;
    nouveau->fg = nouveau->fd = nouveau->fils = NULL;
    return nouveau;
}

void creer_arbre_fichier(FILE* in, Dico* dico)
{
    assert(in);

    char buffer[128];

    while(!feof(in)){
        fscanf(in, "%s", buffer);
        ajout_mot_dico(dico,buffer);
    }
    fclose(in);
}

void ajout_mot_dico(Dico* dico, char *m){

    if((*dico) == NULL)
        (*dico) = alloueDico(*m);

    if((*dico)->lettre == '\0' && *m=='\0')
        return;

    if((*dico)->lettre == *m)
        return ajout_mot_dico(&((*dico)->fils), m+1);

    if((*dico)->lettre > *m)
        return ajout_mot_dico(&((*dico)->fg), m);

    return ajout_mot_dico(&((*dico)->fd), m);
}

int recherche_mot_dico(Dico dico, char* mot)
{
    if(dico == NULL)
        return 0;

    if(dico->lettre == '\0' && *mot=='\0')
        return 1;

    if(dico->lettre == *mot)
        return recherche_mot_dico(dico->fils, mot+1);

    if(dico->lettre > *mot)
        return recherche_mot_dico(dico->fg, mot);

    return recherche_mot_dico(dico->fd, mot);
}
