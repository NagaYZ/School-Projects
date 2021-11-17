#ifndef __SERPENT__
#define __SERPENT__

typedef struct corp_serpent{
	Direction direction;
	Case case_occupee;
	struct corp_serpent* suivant;
}Corp_serpent, *Serpent;

Serpent alloueSerpent(Direction di, int x, int y);

#endif
