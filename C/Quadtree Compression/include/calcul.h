#ifndef __CALCUL__
#define __CALCUL__

/*return the distance between two pixel*/
double distance_pixel(int p1_r, int p2_r, int p1_g, int p2_g,int p1_b, int p2_b,int p1_a, int p2_a);

/*return an int array of 4 with the rgba value of the average zone color*/
int *average_color_zone(int x,int y,int zone,MLV_Image* image);

/*return the sum of error in a zone*/
double error_color_zone(int x,int y, int zone, unsigned char r, unsigned char g, unsigned char b, unsigned char a, MLV_Image* image);

/*look every pixel of the image, and return 0 if all are black/white and 1 else */
int is_color_image(MLV_Image* image);

#endif