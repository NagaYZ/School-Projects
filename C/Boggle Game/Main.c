#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "Jeu.h"
#include "Dico.h"
#include "Grille.h"
#include "Affichage.h"
#include "Test.h"

#define	X COLS / 2;
#define	Y LINES / 2;

int vies, score;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int touche;
	int i;
	/*GESTION DES ARGUMENTS*/
    for ( i = 1; i < argc; i++)
    {
     	if(strcmp(argv[i], "-test") == 0)
			test();
		else
			fprintf(stderr, "Mauvais Argument\n");
		exit(1);
	}

	initscr();
	start_color();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);

	/*INITIALISATION*/
	/*DICO*/
	Dico dico = NULL;
	Dico dico_mot_trouve = NULL;
	FILE *in = fopen("Mots", "r");
	if (in == NULL)
	{
		fprintf(stderr, "erreur a louverture du fichier\n");
		exit(1);
	}

	creer_arbre_fichier(in, &dico);
	
	/*GRILLE ET LISTE*/
	Mot liste = NULL;
	Grille grille = alloueGrille();
	Initialiser_lettre_proba(grille);
	Initialiser_grille(grille);	
	int j, i_coord_last_case_selected, j_coord_last_case_selected;

	vies=4;
	score=0;
	i=0;
	j=0;
	i_coord_last_case_selected=0;
	j_coord_last_case_selected=0;

	/*JEU COMMENCE*/
	while(vies != 0)
	{
		move(i,j);
		clear();

		afficher_lettre(grille);
		afficher_mot_en_cours(liste);
		attron(A_BOLD);
		mvprintw(i,j,"%c",grille->tab_lettre[i][j]);
		attroff(A_BOLD);

		mvprintw(LINES-1,COLS-10,"Score : %d",score);
		mvprintw(LINES-1,0,"Tentatives Restantes : %d",vies);


		touche = getch();

		switch (touche)
		{
			case KEY_RIGHT:
				if(j < L-1)
					j++;
				break;
			case KEY_UP:
				if(i > 0)
					i--;
				break;
			case KEY_LEFT:
				if(j > 0)
					j--;
				break;
			case KEY_DOWN:
				if(i < H-1)
					i++;
				break;
			case 32:/*ESPACE*/
				if(case_valide(grille, i, j, i_coord_last_case_selected, j_coord_last_case_selected)){

					ajouter_lettre(&liste, grille->tab_lettre[i][j], i, j);
					mettre_en_rouge(grille, i, j);					
					i_coord_last_case_selected = i;
					j_coord_last_case_selected = j;
				}
				break;
			case 10:/*ENTREE*/
				if(mot_valide(liste, dico, &dico_mot_trouve)){
					mvprintw(LINES-1,COLS-25,"Mot Correct");
					refresh();
					usleep(500000);
					score += pow(2, longueur_mot(liste) - 3);
				}
				else{	
					mvprintw(LINES-1,COLS-25,"Mot Incorrect");
					refresh();
					usleep(500000);		
					vies--;
				}

				while(liste != NULL)
					annuler_coup(grille, &liste);
				break;

			case 'a':
					annuler_coup(grille, &liste);
				break;
		}
		
		refresh();
	}
	afficher_jeu_fini(score);
	refresh();
	getch();
	endwin();
	free(dico);
	free(liste);
	free(dico_mot_trouve);
	free(grille);
	return 0;
}
