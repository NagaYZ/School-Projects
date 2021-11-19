#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "quadtree.h"
#include "calcul.h"


double distance_pixel(int p1_r, int p2_r, int p1_g, int p2_g,int p1_b, int p2_b,int p1_a, int p2_a)
{
	return sqrt(
	((p1_r - p2_r) * (p1_r - p2_r)) +
	((p1_g - p2_g) * (p1_g - p2_g)) +
	((p1_b - p2_b) * (p1_b - p2_b)) + 
	((p1_a - p2_a) * (p1_a - p2_a)));
	
}

int *average_color_zone(int x,int y,int zone,MLV_Image* image){	/*modify return paramaeter*/
	/*return the average color of a zone*/
	int i,j;
	int sum_red = 0;
	int sum_green = 0;
	int sum_blue = 0;
	int sum_alpha = 0;
	static int tab[4];/*to store the average of each color*/

	int red = 0;
	int green= 0;
	int blue= 0;
	int alpha= 0;
	/*go through every pixel of a zone and add their value to a sum*/
	for(i=x; i< x+zone; i++){
		for(j = y; j < y+zone; j++){

			MLV_get_pixel_on_image(image,i,j,&red,&green,&blue,&alpha);		
			sum_red += red;			
			sum_green += green;			
			sum_blue += blue;	
			sum_alpha += alpha;		
		}
	}

	int num_total_pixel = zone*zone;
	/*get average of each color and return them in an array*/
	tab[0] = sum_red / num_total_pixel ;
	tab[1] = sum_green / num_total_pixel;
	tab[2] = sum_blue / num_total_pixel;
	tab[3] = sum_alpha / num_total_pixel;
	return tab;

}

double error_color_zone(int x,int y, int zone, unsigned char r, unsigned char g, unsigned char b, unsigned char a, MLV_Image* image){
	/*return error of a zone*/
	int i=0,j=0;
	double sum_erreur = 0;
	int red = 0;
	int green= 0;
	int blue= 0;
	int alpha= 0;
	
	/*go through every pixel in a zone and compare them to the average color of the zone*/
	for(i = x ; i < x+zone; i++){
		for(j = y; j < y+zone; j++){
			MLV_get_pixel_on_image(image,i,j,&red,&green,&blue,&alpha);
			sum_erreur += distance_pixel(red,r,green,g,blue,b,alpha,a);
		}
	}	
	return sum_erreur;
}

int is_color_image(MLV_Image* image){
	/*look every pixel, return 0 if all are black/white*/
	int i=0,j=0;
	int red = 0;
	int green= 0;
	int blue= 0;
	int alpha= 0;
	/*look every pixel of an image and return 1 if there is at least one pixel which isnt black or white*/
	for(i = 0 ; i < 512; i++){
		for(j = 0; j < 512; j++){
			MLV_get_pixel_on_image(image,i,j,&red,&green,&blue,&alpha);
			if( ((red == 0)||(red ==255)) && ((green==red) && (blue==red)))
				;
			else
				return 1;
		}
	}	
	return 0;
}