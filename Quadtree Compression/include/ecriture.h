#ifndef __ECRITURE__
#define __ECRITURE__

#include <stdint.h>
#include "quadtree.h"
#include "lecture.h"

struct bit_write {

	unsigned char buf;/*byte buffer*/
	unsigned char save_first;/*save the first byte to rewrite it with the padding at the end*/
	int padding;/*number of bit in the padding(=3) */
	int remaining;/*bits remaining in a byte (byte : 8 full , 0 empty)*/
};

/*init the write buffer*/
void init_write(struct bit_write* b);


/*compact function which use others
open file and use write_color_quad_as_color_aux to write a color quadtree as color*/
void save_color_as_color(ColorQuadtree quad, char* out);/*.qtc*/
/*write a color quadtree to file .qtc*/
void write_color_quad_as_color_aux(ColorQuadtree quad, FILE * f);


/*compact function which use others
use init_write to initialize the write buffer ,
open file and use write_bw_quad_as_bw_aux and write_end_bw_quadtree to write a bw quadtree ,bit by bit*/
void save_bw_as_bw(BWQuadtree quad, char* out);/*.qtn*/
/*write a bw quadtree to file .qtn*/
void write_bw_quad_as_bw_aux(struct bit_write* b, BWQuadtree quad, FILE * f);/*.qtn*/


/*compact function which use others
open file and use write_color_quad_as_color_aux to write a color quadtree as color*/
void save_bw_as_color(BWQuadtree quad, char* out);/*.qtc*/
/*rgb value are equal to 255 if BLACK=0 and 0 else,
write a bw quad as a color quadtree*/
void write_bw_quad_as_color_aux(BWQuadtree quad, FILE * f);


/*compact function which use others
use init_write to initialize the write buffer ,
open file and use write_color_quad_as_bw_aux and write_end_bw_quadtree to write a bw quadtree ,bit by bit*/
void save_color_as_bw(ColorQuadtree quad, char* out);/*.qtn*/
/*use convert_color_to_bw from quadtree.c to get an approximation of the color,
write a color quad as a bw quadtree*/
void write_color_quad_as_bw_aux(struct bit_write* b, ColorQuadtree quad, FILE * f);


/*add the padding to the beginning of the file and write the remaining bits */
void write_end_bw_quadtree(struct bit_write* b,FILE* f);



/*write a minimised bw quad to file.gmn
void write_mini_bw_quad(BWQuadtree quad, char* out); .gmn

write a minimised color quad to file.gmn
void write_mini_color_quad(ColorQuadtree quad, char* out); .gmc
*/
#endif