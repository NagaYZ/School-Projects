#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "Grille.h"

Grille alloueGrille()
{
    Grille grille = (Grille)malloc(sizeof(Grille_lettre));
    if(NULL != grille)
    {
        return grille;
    }
    return NULL;
}

void Initialiser_lettre_proba(Grille grille)
{
    assert(grille);
    int i, compteur;
    compteur=0;

    for(i = 0; i < 11; i++)
    {
        grille->proba_lettre[compteur] = 'E';
        compteur++;
    }

    for(i = 0; i < 8; i++)
    {
        grille->proba_lettre[compteur] = 'T';
        compteur++;
    }

    for(i = 0; i < 7; i++)
    {
        grille->proba_lettre[compteur] = 'A';
        compteur++;
        grille->proba_lettre[compteur] = 'I';
        compteur++;
        grille->proba_lettre[compteur] = 'N';
        compteur++;
        grille->proba_lettre[compteur] = 'O';
        compteur++;
        grille->proba_lettre[compteur] = 'S';
        compteur++;
    }

    for(i = 0; i < 6; i++)
    {
        grille->proba_lettre[compteur] = 'R';
        compteur++;
    }

    for(i = 0; i < 5; i++)
    {
        grille->proba_lettre[compteur] = 'H';
        compteur++;
    }

    for(i = 0; i < 4; i++)
    {
        grille->proba_lettre[compteur] = 'D';
        compteur++;
        grille->proba_lettre[compteur] = 'L';
        compteur++;
    }

    for(i = 0; i < 3; i++)
    {
        grille->proba_lettre[compteur] = 'C';
        compteur++;
        grille->proba_lettre[compteur] = 'M';
        compteur++;
        grille->proba_lettre[compteur] = 'U';
        compteur++;
    }

    for(i = 0; i < 2; i++)
    {
        grille->proba_lettre[compteur] = 'B';
        compteur++;
        grille->proba_lettre[compteur] = 'F';
        compteur++;
        grille->proba_lettre[compteur] = 'G';
        compteur++;
        grille->proba_lettre[compteur] = 'P';
        compteur++;
        grille->proba_lettre[compteur] = 'W';
        compteur++;
        grille->proba_lettre[compteur] = 'Y';
        compteur++;
    }

    grille->proba_lettre[compteur] = 'J';
    compteur++;
    grille->proba_lettre[compteur] = 'K';
    compteur++;
    grille->proba_lettre[compteur] = 'Q';
    compteur++;
    grille->proba_lettre[compteur] = 'V';
    compteur++;
    grille->proba_lettre[compteur] = 'X';
    compteur++;
    grille->proba_lettre[compteur] = 'Z';    
}

void Initialiser_grille(Grille grille)
{
    assert(grille);
    int i,j;
    for(i = 0; i<H ; i++)
    {
        for(j = 0; j<L ; j++)
        {
            grille->tab_lettre[i][j] = grille->proba_lettre[rand()%POURCENTAGE];
            grille->tab_lettre_rouge[i][j]=0;
        }
    }
}
void mettre_en_rouge(Grille grille, int x, int y)
{
    assert(x<H && x>=0);
    assert(y<L && y>=0);
    assert(grille);
    grille->tab_lettre_rouge[x][y] = 1;
}

void enlever_rouge(Grille grille, int x, int y)
{
    assert(x<H && x>=0);
    assert(y<L && y>=0);
    assert(grille);
    grille->tab_lettre_rouge[x][y] = 0;
}

int case_valide(Grille grille, int x1, int y1, int x2, int y2)
{
    assert(x1<H && x1>=0);
    assert(y1<L && y1>=0);
    assert(x2<H && x2>=0);
    assert(y2<L && y2>=0);
    assert(grille);

    int x_diff,y_diff;
    if(grille->tab_lettre_rouge[x1][y1] == 0)
    {
       if(x1 != x2 || y1 != y2)
       {
            if(grille->tab_lettre_rouge[x2][y2] == 1)
            {
                x_diff = x1 - x2;
                y_diff = y1 - y2;               
                if((x_diff <= -2 || x_diff >= 2 ) || (y_diff <= -2 || y_diff >= 2 ))
                    return 0;
            }
       }
       return 1;
       
    }
    return 0;
}
