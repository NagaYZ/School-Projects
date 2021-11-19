#ifndef __MONDE__
#define __MONDE__
#define N 32
#define M 64

typedef struct Monde
{
	int nb_ligne;
	int nb_colonne;
	Serpent serpent;
	Pomme position_pomme[3];/*3 pommes*/
	int score;
}Monde;

int touche_pas_pomme(Monde mon, int x, int y);
int touche_pas_serpent(Monde mon, int x, int y);
int sortir_quadrillage(Monde mon, int x, int y);
void ajouter_pomme_monde(Monde *mon);
Serpent init_serpent(Monde mon);
Monde init_monde(int nb_pommes);
int deplacer_serpent(Monde *mon);
int manger_pomme_serpent(Monde *mon);
int mort_serpent(Monde *mon);

#endif
