#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "Direction.h"
#include "Case.h"
#include "Pomme.h"
#include "Serpent.h"
#include "Monde.h"
#include "Affichage.h"

#define	X COLS / 2;
#define	Y LINES / 2;
#define DELAI 1000000 /*1 seconde*/

int main()
{
	srand(time(NULL));
	int touche;
	initscr();
	start_color();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	Monde mon=init_monde(3);
	afficher_monde(mon);

	while(!mort_serpent(&mon))
	{
		clear();
		if(manger_pomme_serpent(&mon))
		{
			ajouter_pomme_monde(&mon);
		}

		deplacer_serpent(&mon);

		afficher_monde(mon);
		touche = getch();

		switch (touche)
		{
			case 'd' :
			if(mon.serpent->direction != GAUCHE)
				mon.serpent->direction = DROITE;
			break;
			case KEY_RIGHT:
			if(mon.serpent->direction != GAUCHE)
				mon.serpent->direction = DROITE;
			break;
			case 'z':
			if(mon.serpent->direction != BAS)
				mon.serpent->direction = HAUT;
			break;
			case KEY_UP:
			if(mon.serpent->direction != BAS)
				mon.serpent->direction = HAUT;
			break;
			case 'q':
			if(mon.serpent->direction != DROITE)
				mon.serpent->direction = GAUCHE;
			break;
			case KEY_LEFT:
			if(mon.serpent->direction != DROITE)
				mon.serpent->direction = GAUCHE;
			break;
			case 's':
			if(mon.serpent->direction != HAUT)
				mon.serpent->direction = BAS;
			break;
			case KEY_DOWN:
			if(mon.serpent->direction != HAUT)
				mon.serpent->direction = BAS;
			break;
		}
		mvprintw(LINES-1,COLS-10,"Score : %d",mon.score);
		refresh();
		usleep(DELAI/4);

	}
	refresh();
	getch();
	endwin();
	return 0;
}
