#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include "quadtree.h"

/*DISPLAY ALL BUTTON*/
void display_menu();

/*re-display the box*/
void display_re_input_box();

/*draw the image*/
void display_image(MLV_Image* image);

/*DISPLAY WHEN THERE IS NO IMAGE WHEN CLICK ON QUADTREE*/
void display_no_image();

/*display message when quadtree or minimisation are done*/
void display_done();

/*display message if there are no quadtree , when try to save.*/
void display_no_quadtree();

/*display, reading/saving minimised quadtree as graph not possible.*/
void display_mini_disabled();

/*used to display part of a color quadtree, when build from an image step by step*/
void display_color_quadtree_from_image(ColorQuadtree quad,int circle);

/*used to display color quadtree, when build from a file*/
void display_color_quadtree_from_file(ColorQuadtree quad,int x, int y, int zone_start,int circle);

/*used to display bw quadtree, when build from a file*/
void display_bw_quadtree_from_file(BWQuadtree quad,int x, int y, int zone_start,int circle);

/*used to display part of a bw quadtree, when build from an image step by step*/
void display_bw_quadtree_from_image(BWQuadtree quad,int circle);

/*print in the terminal how to use the program, and the option*/
void usage();



#endif