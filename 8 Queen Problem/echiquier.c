#include <stdio.h>
#include <stdlib.h>

#include "echiquier.h"


int est_case_occupee(Position pos, Case c){

	if(pos & ((Position)1 << (c)))
		return 1;

	return 0;
}


void allumer_bit(Position *pos, Case i){
	(*pos)=(*pos)|((Position)1<<i);
}

void eteindre_bit(Position *pos, Case i){
    (*pos)=(*pos)&(~((Position)1<<i));
}

void placer_dame_position(Position *pos, Case c){
    *pos = *pos | ((Position)1 << c);
}

void affiche_ligne_bit(Position pos, Case c){
	Case i;
	pos = pos>>c;
	for(i = c; i < c+8; i++){
		if((pos&1)==1)
			printf("1 ");
		else
			printf("0 ");
		pos = pos >> 1;
	}
}

int afficher_position(Position pos){
	Case i;
	for(i = 56; i != 0; i=i-8){
		affiche_ligne_bit(pos, i);
		printf("\n");
	}
	affiche_ligne_bit(pos, 0);
	printf("\n");
}
