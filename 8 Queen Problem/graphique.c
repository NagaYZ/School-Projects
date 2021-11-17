#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <assert.h>

#include "graphique.h"

void init_plateau(){
	int couleur = 0;
	int i,j;
	for(i = 0; i < TAILLE * 3; i += 3){
		for(j = 0; j < TAILLE * 5; j += 5){
			if(couleur % 2 == 0)
				attron(COLOR_PAIR(1));
			else
				attron(COLOR_PAIR(2));

			mvprintw(i, j, "     ");
			mvprintw(i + 1, j, "     ");
			mvprintw(i + 2, j, "     ");

			attroff(COLOR_PAIR(1));
			attroff(COLOR_PAIR(2));
			couleur ++;
		}
		couleur ++;
		refresh();
	}
}

void afficher_dame(int x, int y){
	assert(x >= 0 && y >= 0);

	if(((x % 2 == 0) && (y % 2 == 0)) || ((x % 2 != 0) && (y % 2 != 0)))
		attron(COLOR_PAIR(3));
	else if(((x % 2 == 0) && (y % 2 != 0)) || ((x % 2 != 0) && (y % 2 == 0)))
		attron(COLOR_PAIR(4));
	
	mvprintw(x * 3 + 1, y * 5 + 2, "X");
	refresh();

	attroff(COLOR_PAIR(3));
	attroff(COLOR_PAIR(4));
}

void effacer_dame(int x, int y){
	assert(x >= 0 && y >= 0);
	
	if(((x % 2 == 0) && (y % 2 == 0)) || ((x % 2 != 0) && (y % 2 != 0)))
		attron(COLOR_PAIR(1));
	else if(((x % 2 == 0) && (y % 2 != 0)) || ((x % 2 != 0) && (y % 2 == 0)))
		attron(COLOR_PAIR(2));
	
	mvprintw(x * 3 + 1, y * 5 + 2, " ");
	refresh();

	attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
}