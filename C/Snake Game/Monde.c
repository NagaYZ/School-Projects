#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Case.h"
#include "Direction.h"
#include "Pomme.h"
#include "Serpent.h"
#include "Monde.h"

int touche_pas_pomme(Monde mon, int x, int y)
{
	int i;

	for(i=0; i<3; i++)/*3 pommes verifie que pas sur pomme*/
	{
		if(x == mon.position_pomme[i].x && y == mon.position_pomme[i].y)
			return 0;
	}
	return 1;
}

int touche_pas_serpent(Monde mon, int x, int y)
{
	Serpent tmp;
	assert(x>=0);
	assert(y>=0);
	if(mon.serpent->suivant != NULL)
		tmp = mon.serpent->suivant;
	else
		return 1;
	while(tmp != NULL)
	{
		if(x == tmp->case_occupee.x && y == tmp->case_occupee.y)
			return 0;
		tmp=tmp->suivant;
	}

	return 1;
}

int sortir_quadrillage(Monde mon, int x, int y)
{

	if((0 <= x && x<=mon.nb_ligne ) &&( 0 <= y && y<=mon.nb_colonne ))
		return 0;
	return 1;
}

void ajouter_pomme_monde(Monde *mon)
{
	int i;
	Pomme pomme;
	do
	{
		pomme=pomme_gen_alea(mon->nb_ligne,mon->nb_colonne);
	}
	while( !touche_pas_pomme(*mon, pomme.x, pomme.y) || !touche_pas_serpent(*mon, pomme.x, pomme.y) );

	for(i=0; i<3; i++)/*3 pommes verifie que pas sur pomme*/
	{
		if(mon->position_pomme[i].x ==-1 && mon->position_pomme[i].y==-1)
		{
			mon->position_pomme[i].x = pomme.x;
			mon->position_pomme[i].y = pomme.y;
		}
	}

}

Serpent init_serpent(Monde mon)
{
	/*initialiser tete du serpent*/
	Serpent serpent = alloueSerpent(DROITE, (mon.nb_ligne)/2, (mon.nb_colonne)/2);

	/*initialiser corps du serpent*/
	int i;
	Serpent tmp;
	tmp = serpent;

	for(i=0; i<3; ++i)
	{
		tmp->suivant  =  alloueSerpent(DROITE, tmp->case_occupee.x, tmp->case_occupee.y-1);
		tmp = tmp->suivant;
	}
	/*return le serpent*/
	return serpent;

}

Monde init_monde(int nb_pommes)
{
	int i;
	Monde mon;
	mon.nb_ligne = N;
	mon.nb_colonne = M;
	mon.serpent = NULL;
	assert(0<=nb_pommes && nb_pommes<=3);

	for(i = 0; i < 3; i++)
	{

		if (i<nb_pommes)
			mon.position_pomme[i]=pomme_gen_alea(mon.nb_ligne, mon.nb_colonne);
		else
		{
			mon.position_pomme[i].x=-1;
			mon.position_pomme[i].y=-1;
		}

	}
	mon.serpent = init_serpent(mon);
	return mon;
}

int deplacer_serpent(Monde *mon)
{
	Serpent tmp;
	tmp = mon->serpent;
	int x,y,tete;
	tete = 0;

	while(tmp != NULL)
	{
		x = tmp->case_occupee.x;
		y = tmp->case_occupee.y;

		switch(tmp->direction)
		{
			case HAUT:
				if((!(touche_pas_pomme(*mon, x-1, y)) || !(touche_pas_serpent(*mon, x-1, y)) || sortir_quadrillage(*mon, x-1, y)) && (tete == 0))
					return 0;
				tmp->case_occupee.x -= 1;
				break;
			case BAS:
				if((!(touche_pas_pomme(*mon, x+1, y)) || !(touche_pas_serpent(*mon, x+1, y)) || sortir_quadrillage(*mon, x+1, y)) && (tete == 0))
					return 0;
				tmp->case_occupee.x += 1;
				break;
			case GAUCHE:
				if((!(touche_pas_pomme(*mon, x, y-1)) || !(touche_pas_serpent(*mon, x, y-1)) || sortir_quadrillage(*mon, x, y-1)) && (tete == 0))
					return 0;
				tmp->case_occupee.y -=1;
				break;
			case DROITE :
				if((!(touche_pas_pomme(*mon, x, y+1)) || !(touche_pas_serpent(*mon, x, y+1)) || sortir_quadrillage(*mon, x, y+1)) && (tete == 0))
					return 0;
				tmp->case_occupee.y +=1;
				break;
		}
		tete++;
		tmp = tmp->suivant;/*cou*/

	}
	tmp = mon->serpent;
	/*On change la direction des cases du corps du serpent une case a la fois*/
	while(tmp->suivant != NULL)
	{
		if((tmp->suivant->direction) != (tmp->direction))
		{
			tmp->suivant->direction = tmp->direction;
			break;
		}
		tmp=tmp->suivant;
	}
	return 1;
}


int manger_pomme_serpent(Monde *mon)
{
	Serpent tmp;
	tmp = mon->serpent;
	int x,y,tete,i;
	tete=0;
	while(tmp != NULL)
	{
		x = tmp->case_occupee.x;
		y = tmp->case_occupee.y;
		switch(tmp->direction)
		{
			case HAUT :
				if(touche_pas_pomme(*mon, x-1, y)&& tete == 0)
					return 0;
				tmp->case_occupee.x -= 1;
				break;
			case BAS :
				if(touche_pas_pomme(*mon, x+1, y)&& tete == 0)
					return 0;
				tmp->case_occupee.x += 1;
				break;
			case GAUCHE :
				if(touche_pas_pomme(*mon, x, y-1)&& tete == 0)
					return 0;
				tmp->case_occupee.y -=1;
				break;
			case DROITE :
				if(touche_pas_pomme(*mon, x, y+1)&& tete == 0)
					return 0;
				tmp->case_occupee.y +=1;
				break;
		}
		tete++;
		tmp = tmp->suivant;/*cou*/
	}
	tmp = mon->serpent;
	for(i=0;i<3;i++)
	{
		if((mon->position_pomme[i].x == tmp->case_occupee.x)&&(mon->position_pomme[i].y == tmp->case_occupee.y))
		{
			mon->position_pomme[i].x=-1;
			mon->position_pomme[i].y=-1;
		}
	}	
	mon->score++;
	while(tmp->suivant != NULL)
	{
		tmp=tmp->suivant;
		if(tmp->suivant == NULL)/*SI ON ARRIVE SUR LA DERNIERE PARTIE DU SERPENT ON L'AGRANDIT*/
		{
			switch(tmp->direction)
			{
				case HAUT :
					tmp->suivant = alloueSerpent(tmp->direction, tmp->case_occupee.x+1, tmp->case_occupee.y);
					return 1;
				case BAS :
					tmp->suivant = alloueSerpent(tmp->direction, tmp->case_occupee.x-1, tmp->case_occupee.y);
					return 1;
				case GAUCHE :
					tmp->suivant = alloueSerpent(tmp->direction, tmp->case_occupee.x, tmp->case_occupee.y+1);
					return 1;
				case DROITE :
					tmp->suivant = alloueSerpent(tmp->direction, tmp->case_occupee.x, tmp->case_occupee.y-1);
					return 1;
			}
		}
	}
	return 1;
}

int mort_serpent(Monde *mon)
{
	int x,y;
	Serpent tmp;
	tmp = mon->serpent;
	x = tmp->case_occupee.x;
	y = tmp->case_occupee.y;

	switch(tmp->direction)
	{/*si serpent entre en collision avec son corps ou depasse limites du quadrillage*/
		case HAUT :
			if(!touche_pas_serpent(*mon, x-1, y) || sortir_quadrillage(*mon, x-1, y))
			{
				tmp->case_occupee.x -= 1;
				return 1;
			}
			break;
		case BAS :
			if(!touche_pas_serpent(*mon, x+1, y) || sortir_quadrillage(*mon, x+1, y))
			{
				tmp->case_occupee.x += 1;
				return 1;
			}
			break;
		case GAUCHE :
			if(!touche_pas_serpent(*mon, x, y-1) || sortir_quadrillage(*mon, x, y-1))
			{
				tmp->case_occupee.y -=1;
				return 1;
			}
			break;
		case DROITE :
			if(!touche_pas_serpent(*mon, x, y+1) || sortir_quadrillage(*mon, x, y+1))
			{
				tmp->case_occupee.y +=1;
				return 1;
			}
			break;
	}
	/*si serpent survit*/
	return 0;
}
