#include <ncurses.h>
#include "Direction.h"
#include "Case.h"
#include "Pomme.h"
#include "Serpent.h"
#include "Monde.h"

void afficher_quadrillage(Monde mon)
{
	int i,j;
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_WHITE);

	for(i = 0; i < mon.nb_ligne; i ++)
	{
		for(j = 0; j < mon.nb_colonne; j++)
		{
			attron(COLOR_PAIR(1));
			mvprintw(i, j, "  ");
			attroff(COLOR_PAIR(1));
			attroff(COLOR_PAIR(2));
		}
		refresh();
	}
}

void afficher_pomme(Pomme pom)
{
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	attron(COLOR_PAIR(3));
	mvprintw(pom.x, pom.y * 2, "  ");
	refresh();
	attroff(COLOR_PAIR(3));
	refresh();
}

void afficher_serpent(Serpent serpent)
{
	int x, y, tete;
	Serpent tmp = serpent;
	tete=0;
	refresh();
	init_color(COLOR_CYAN, 255, 140,0);  /*marron-orange*/
	init_pair(4, COLOR_CYAN, COLOR_CYAN);
	init_color(COLOR_RED, 150, 250,100);  /*kaki*/
	init_pair(5, COLOR_RED, COLOR_RED);

	while(tmp != NULL)
	{	refresh();
		x = tmp->case_occupee.x;
		y = tmp->case_occupee.y;
		if(tete==0)
		{
			attron(COLOR_PAIR(5));
			mvprintw(x, y * 2, "  ");
			attroff(COLOR_PAIR(5));
    	}
    	else
		{
	      attron(COLOR_PAIR(4));
	      mvprintw(x, y * 2, "  ");
	      attroff(COLOR_PAIR(4));
    	}
		tete++;


		tmp = tmp->suivant;
	}
}

void afficher_monde(Monde mon)
{
	int i;
	afficher_quadrillage(mon);
	for(i=0; i<3 ; i++)
	{
		if(mon.position_pomme[i].x != -1)
			afficher_pomme(mon.position_pomme[i]);
	}

	afficher_serpent(mon.serpent);
}
