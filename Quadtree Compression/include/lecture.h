#ifndef __LECTURE__
#define __LECTURE__

#include "quadtree.h"
#include <stdint.h>

struct bit_read{
	FILE* file;	/*The file to read */
	unsigned int bytepos;/* Position of the current byte*/
	unsigned int bytesize;/*Size of the file in bytes*/
	char padding;/*value of padding  (between 0 and 7(111))*/	
	unsigned char current;/*The current Byte*/	
	char remaining;/*Number of bit left to be read*/
};


/*used for test :print the color quadtree (1 125 152....) */
void display_color_quadtree_file(FILE* in);

/*used for test :print binary sequence without the padding of file.qtn (ex: 01101 01110101 ...)*/
void display_bw_quadtree_file(struct bit_read b);

/*initialize the reading buffer*/
int init_bit_read(struct bit_read* byte, FILE* file);

/*Read one bit of the byte, inside of the given buffer and return it*/
int read_bit(struct bit_read* byte);

/*open file in and use build_bw_quad_file_aux to create a bw quadtree*/
void build_bw_quadtree_from_file(BWQuadtree* quad, char** in);

/*read file and build a black and white quadtree from a file*/
void build_bw_quad_file_aux(struct bit_read* b, BWQuadtree* quad, FILE* in);

/*open file in and use build_color_quad_file_aux to create a color quadtree*/
void build_color_quadtree_from_file(ColorQuadtree* quad, char** in);

/*read file and build a color quadtree from a file*/
void build_color_quad_file_aux(ColorQuadtree* quad, FILE* in);


#endif