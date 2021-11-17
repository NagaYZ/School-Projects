#include <stdio.h>
#include <stdlib.h>
#include "Direction.h"
#include "Case.h"
#include "Serpent.h"

Serpent alloueSerpent(Direction di, int x, int y)
{
	Serpent serpent = (Corp_serpent*) malloc( sizeof(Corp_serpent) );
	if(serpent != NULL){
		serpent->direction = di;
		serpent->case_occupee.x = x;
		serpent->case_occupee.y = y;
		serpent->suivant = NULL;
	}
	return serpent;
}
