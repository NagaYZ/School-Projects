#include "attaque.h"
#include <stdlib.h>
#include <stdio.h>
#include "echiquier.h"

int calculer_cases_attaques(Position *pos, Case c){
	Case i;


	if(((c+1) % 8)!=0){  /* cas où le pion n'est pas a l'extremité droite */
		for(i = c; i%8 != 0; i--){
			allumer_bit(pos, i-1);
		}
	}
	if((c-1)%8 != 0){
		for(i = c; (i+1)%8 != 0; i++){  /* Cas où le pion n'est pas à */
			allumer_bit(pos, i+1);		/* l'extremité gauche*/
		}
	}
	if(c > 7){						/* Cas où le pion n'est pas à l'extremité */
		for(i = c; i > 7; i-=8){	/* Bas */
			allumer_bit(pos, i-8);
		}
	}
	if(c < 56){						/* Cas où le pion n'est pas à l'extremité */
		for(i = c; i < 56; i+=8)	/* haut */
			allumer_bit(pos, i+8);
	}

	if((c+1) % 8 != 0 && c > 7){ 			/*Cas de la diagonale sud-est*/
		for(i = c; (i+1)%8 != 0; i = i-7)
			allumer_bit(pos, i-7);
	}
	if((c%8)!=0 && c > 7){					/*Cas de la diagonale sud-ouest */
		for(i = c; (i%8)!=0; i-=9)
			allumer_bit(pos, i-9);
	}

	if((c+1) % 8 != 0 && c < 56){			/* Cas de la diagonale nord-est */
		for(i = c; (i+1)%8 != 0 && i < 56; i+=9)
			allumer_bit(pos, i+9);
	}

	if((c%8)!=0 && c < 56){			/* Cas de la diagonale nord-ouest */
		for(i = c; (i%8)!=0  && i < 56; i+=7)
			allumer_bit(pos, i+7);
	}
	*pos = *pos & ~((Position)1 << c);

	return 1;
}


int test_bin_egaux(Position p1, Position p2){
	if(!(p1&p2))
		return 0;
	return 1;
}

int est_sans_attaque_mutuelle(Position pos){

	int i;
	Position attaque;
	attaque = 0;

	/****** Partie initialisation du tableau de Position *****/
	for(i = 0; i < 64; i++){

		if(est_case_occupee(pos, i)){
			calculer_cases_attaques(&attaque, i);
		}
	}

	if(!test_bin_egaux(attaque, pos))
		return 1;

	return 0;
}
