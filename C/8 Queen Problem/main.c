#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "echiquier.h"
#include "attaque.h"
#include "graphique.h"

int main(void){

	Position pos = 0;
	Case c;

	int touche;
	int clic_x, clic_y;
	int case_x, case_y;
	int nb_dame = 0;
	MEVENT ev;

	initscr();
	start_color();
	curs_set(0);

	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_WHITE);

	init_plateau();

	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

	while(1){
		
		touche = getch();
		
		if(touche == KEY_MOUSE && getmouse(&ev) == OK){
			clic_x = ev.y;
			clic_y = ev.x;
			case_x = ( clic_x - (clic_x % 3) ) / 3;
			case_y = ( clic_y - (clic_y % 5) ) / 5;

			if(case_x >= 0 && case_x <= 7 && case_y >= 0 && case_y <= 7){
				c = ((TAILLE - 1 - case_x) * 8) + case_y;
				if(est_case_occupee(pos, c) == 0 && nb_dame != 8){
					allumer_bit(&pos, c);
					afficher_dame(case_x, case_y);
					nb_dame ++;
				}
				else if(est_case_occupee(pos, c) == 1){
					eteindre_bit(&pos, c);
					effacer_dame(case_x, case_y);	
					nb_dame --;
				}
			}
		}

		if(est_sans_attaque_mutuelle(pos) == 0){
			attron(COLOR_PAIR(5));
			mvprintw(0, 41, "PLACEMENT ILLEGAL !");
			attroff(COLOR_PAIR(5));
		}
		else{
			attron(COLOR_PAIR(2));
			mvprintw(0, 41, "                   ");
			attroff(COLOR_PAIR(2));
		}

		if(nb_dame == 8 && est_sans_attaque_mutuelle(pos) == 1){
			attron(COLOR_PAIR(6));
			mvprintw(11, 45, "V I C T O I R E  !");
			refresh();
			usleep(5000000);
			break;
		}

		refresh();
		usleep(5000);
	}
	
	getch();
	endwin();
	return 0;
}
