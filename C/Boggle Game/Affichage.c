#include <ncurses.h>
#include "Affichage.h"

void afficher_lettre(Grille grille)
{
    int i,j;
    init_pair(1, COLOR_RED, COLOR_BLACK);
    for(i=0; i < H; i++){
        for(j=0; j < L; j++)
        {
            if(grille->tab_lettre_rouge[i][j] == 1)
            {
                attron(COLOR_PAIR(1));
                attron(A_BOLD);
                mvprintw(i,j,"%c",grille->tab_lettre[i][j]);
                attroff(COLOR_PAIR(1));
                attroff(A_BOLD);
            }
            else
                mvprintw(i,j,"%c",grille->tab_lettre[i][j]);
        }
    }
    refresh();
}
void afficher_mot_en_cours(Mot liste)
{
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
    mvprintw(LINES-3,0,"Votre mot est : %s", buffer);
}
void afficher_jeu_fini(int score)
{
    clear();
    mvprintw(LINES/2,COLS/2,"Score FINAL : %d",score);
    refresh();
}
