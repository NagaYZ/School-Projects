#ifndef __PLATEAU__
#define __PLATEAU__

#define NB_COL 4
#define NB_LIG 4

typedef struct carre{
	int lig;
	int col;
} Carre ;

typedef struct plateau {
 	Carre bloc[NB_COL][NB_LIG] ;
} Plateau ;

/*init le plateau*/
void InitialisationPlateau(Plateau *P);

/*swap two square*/
void swapCarre(Plateau *P, int x1, int y1, int x2 , int y2);

/*return 1 if game is won*/
int Win(Plateau P);

/*return 1 if click is on a valid square and not the black square*/
int clicValide(Plateau P, int x, int y, int x_case_noir, int y_case_noir);

/*return the coordinate of a random valid square*/
int* randomCarrePossible(Plateau P,int column,int row);

/*swap the black square with a random valid square, 120 times and return the coordinates(x,y) of the black square*/
int* shufflePlateau(Plateau *P);
#endif