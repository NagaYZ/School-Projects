#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Case.h"
#include "Pomme.h"

Pomme pomme_gen_alea(int n,int m)
{
	Pomme pomme;

	pomme.x=rand() %n;
	pomme.y=rand() %m;

	return pomme;
}
