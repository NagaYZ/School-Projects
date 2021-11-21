#ifndef __QUADTREE__
#define __QUADTREE__

#include <MLV/MLV_all.h>
#include "calcul.h"

/*Color Quadtree structure, x,y are the NO coordinates of the node, zone its size(height/width)
rgba are the color...
each node has 4 children , initialized to NULL*/
typedef struct color_quadtree{
	int x;
	int y;
	int zone;/* zone (1,512) <=> size of the square, 1 = single pixel*/
	unsigned char r;/*red (0,255)*/
	unsigned char g;/*green (0,255)*/
	unsigned char b;/*blue (0,255)*/
	unsigned char a;/*alpha (0,255)*/
	struct color_quadtree* NO;
	struct color_quadtree* NE;
	struct color_quadtree* SE;
	struct color_quadtree* SO;
}*ColorQuadtree;

/*BW Quadtree structure, x,y are the NO coordinates of the node, zone its size(height/width)
BLACK is the color , 1 for BLACK and 0 for WHITE, added -1 for NODE to distinguish node/leaf when minimizing the quadtree
each node has 4 children , initialized to NULL*/
typedef struct bw_quadtree{
	int x;
	int y;
	int zone;/* zone (1,512) <=> size of the square*/
	int BLACK;/* 1 BLACK , 0 WHITE, -1 NODE*/
	struct bw_quadtree* NO;
	struct bw_quadtree* NE;
	struct bw_quadtree* SE;
	struct bw_quadtree* SO;
}*BWQuadtree;/*!< BW = BlackWhite*/


/**Allocate a bw quadtree , and initialize its parameter x,y,zone,color (1 or 0) , 
and all children to NULL*/
BWQuadtree allocate_bw_quad(int x ,int y,int zone, int color);

/**Allocate a color quadtree , and initialize its parameter x,y,zone,r,g,b,a , and all children to NULL*/
ColorQuadtree allocate_color_quad(int x ,int y,int zone, unsigned char r,unsigned char g, unsigned char b, unsigned char alpha);

/*convert rgba value of a quadtree to black or white, 
return 1 if black , 0 if white */
int convert_color_to_bw(ColorQuadtree c);
/*minimize a bw quadtree, if all the leaves of a node have the same color 
then the node is equal to one of its children*/
void minimise_bw_quad(BWQuadtree* quad);

/*minimize a color quadtree, if all the leaves of a node have the same color 
then the node is equal to one of its children*/
void minimise_color_quad(ColorQuadtree* quad);

/*return 1 if a quadtree is equal to another*/
int same_color_quadtree(ColorQuadtree quad,ColorQuadtree quad2);

/*free completely a color quad*/
void free_color_quad(ColorQuadtree* a);

/*free completely a bw quad*/
void free_bw_quad(BWQuadtree* a);

/*return 1 if all the leaf of a bw quadtree are of the same color*/
int bw_node_all_leaf_same_color(BWQuadtree quad);

/*return 1 if all the leaf of a color quadtree are of the same color*/
int color_node_all_leaf_same_color(ColorQuadtree quad);

/*create and display , step by step the creation of a color quadtree from a colored image
can be very slow*/
void build_color_quad_image(ColorQuadtree *quad,MLV_Image* image,int circle);

/*create and display , step by step the creation of a bw quadtree from a bw image
can be very slow*/
void build_bw_quad_image(BWQuadtree *quad,MLV_Image* image,int circle);

/*compare each leaf of a color quad, and return the one with the worst error*/
ColorQuadtree worst_error_zone_color(ColorQuadtree quad, ColorQuadtree* pire_zone,MLV_Image* image);

/*compare each leaf of a bw quad, and return the one with the worst error*/
BWQuadtree worst_error_zone_bw(BWQuadtree quad, BWQuadtree* pire_zone,MLV_Image* image);



/*
open file in.gmn and use build_mini_bw_quad_file_aux to create a minimised bw quadtree
void build_mini_bw_quad_from_file(BWQuadtree* quad, char* in);

read file and build a black and white quadtree from a file
void build_mini_bw_quad_file_aux(struct bit_read* b, BWQuadtree* quad, FILE* in);

open file in.gmc and use build_mini_color_quad_file_aux to creata a minimised color quadtree
void build_mini_color_quad_from_file(ColorQuadtree* quad, char* in);
*read file and build a minimised color quadtree from a file
void build_mini_color_quad_file_aux(ColorQuadtree* quad, FILE* in);
*/
#endif