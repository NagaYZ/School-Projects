#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include "plateau.h"

#define SIZE 512


/*print WIN in the black square when the game is won*/
void display_win();

/*display the image and the black_square*/
void display_game(Plateau P,MLV_Image* image);

/*convert and return a coordinate to represent a square. example: x = 384 -> x = 3*/
int pixel_vers_case(int x);

#endif