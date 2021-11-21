#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"

void InitialisationPlateau(Plateau *P) {
	int i,j ;
 	for ( i= 0 ; i < NB_LIG ; i++) {
		for ( j = 0 ; j < NB_COL ; j++) {
			((P->bloc)[i][j]).lig = i ;
			((P->bloc)[i][j]).col = j ;
		}
	}
}
void swapCarre(Plateau *P, int x1, int y1, int x2 , int y2){

	/*swap two square*/

	int x_tmp = P->bloc[x1][y1].lig;
	int y_tmp = P->bloc[x1][y1].col;

	P->bloc[x1][y1].lig = P->bloc[x2][y2].lig;
	P->bloc[x1][y1].col = P->bloc[x2][y2].col;

	P->bloc[x2][y2].lig = x_tmp ;
	P->bloc[x2][y2].col = y_tmp ;

}
int Win(Plateau P){

	/*return 1 if win*/
	
	int i,j ;
 	for ( i= 0 ; i < NB_LIG ; i++) {
		for ( j = 0 ; j < NB_COL ; j++) {
			if(P.bloc[i][j].lig != i || P.bloc[i][j].col != j)
				return 0;
		}
	}
	return 1;
}

int clicValide(Plateau P, int x, int y, int x_case_noir, int y_case_noir){
	/*return 1 if mouse click is valid*/
	/*if click on black square then return 0*/
	if(P.bloc[x][y].lig == 3 && P.bloc[x][y].col == 3)
		return 0;

	int i,j;
	/*check if square is adjacent to the black square (right,left,up,down)*/
	for(j = y_case_noir-1; j <= y_case_noir+1 ; j++){
		for(i = x_case_noir -1; i<= x_case_noir +1; i++){
			/*get valid square*/
			if( i >=0 && j >=0 && i < NB_COL && j < NB_LIG && !(j == y_case_noir && i == x_case_noir)
				&& !(j == y_case_noir-1 && i == x_case_noir+1) && !(j == y_case_noir+1 && i == x_case_noir+1)
					&& !(j == y_case_noir+1 && i == x_case_noir-1) &&!(j == y_case_noir-1 && i == x_case_noir-1)) {
					if(x == i && y == j)
						return 1;
			}
		}
	}
	return 0;
}

int* randomCarrePossible(Plateau P,int column,int row){

	/*return the coordinates of a random valid square*/
	int x1=-1,y1=-1;
	int x2=-1,y2=-1;
	int x3=-1,y3=-1;
	int x4=-1,y4=-1;
	int i,j,k=1;
	int random;
	static int coord[2];/*to store x and y coordinates of a valid square*/

	/*get adjacent square to the black square (right,left,up,down)*/
	for(j = row-1; j <= row+1 ; j++){
		for(i = column -1; i<= column +1; i++){
			/*get adjacent square*/
			if( i >=0 && j >=0 && i < NB_COL && j < NB_LIG && !(j == row && i == column)
				&& !(j == row-1 && i == column+1) && !(j == row+1 && i == column+1)
					&& !(j == row+1 && i == column-1) &&!(j == row-1 && i == column-1)) {
					/*up to four adjacent square*/
					if(k == 1){
						x1 = j;
						y1 = i;
					}
					else if(k == 2){
						x2 = j;
						y2 = i;
					}
					else if(k == 3){
						x3 = j;
						y3 = i;
					}
					else if(k == 4){
						x4 = j;
						y4 = i;
					}
					k++;
			}
		}
	}

	/*get a random valid square*/
	if(x4 != -1){/*if 4 valid square, black square in the middle*/
		random = rand() % 4 ;
		switch(random){
			case 0:coord[0] = x1; coord[1] = y1;break;
			case 1:coord[0] = x2; coord[1] = y2;break;
			case 2:coord[0] = x3; coord[1] = y3;break;
			case 3:coord[0] = x4; coord[1] = y4;break;
		}

	}
	else if(x3 !=- 1){/*if 3 valid square, black square on sides*/
		random = rand() % 3 ;
		switch(random){
			case 0:coord[0] = x1; coord[1] = y1;break;
			case 1:coord[0] = x2; coord[1] = y2;break;
			case 2:coord[0] = x3; coord[1] = y3;break;
		}
	}
	else if(x2 != -1){/*if 2 valid square, black square in corners*/
		random = rand() % 2 ;
		switch(random){
			case 0:coord[0] = x1; coord[1] = y1;break;
			case 1:coord[0] = x2; coord[1] = y2;break;
		}	
	}

	return coord;
}

int* shufflePlateau(Plateau *P){

	/*swap black square with valid square ,120 times*/
	/*and return the new coordinates(x,y) of the black square*/

 	int* coord;/*to store coordinates of the black square*/

	int diff_120 = 0;
	int x_case_noir = 3;
	int y_case_noir = 3;
	/*swap 120 times*/
	while(diff_120++ != 120){

		coord = randomCarrePossible(*P, x_case_noir, y_case_noir);
		swapCarre(P,x_case_noir,y_case_noir,coord[0],coord[1]);
		/*new black square coordinates*/
		x_case_noir = coord[0];
		y_case_noir = coord[1];

	}

	return coord;
	
}


