#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ecriture.h"

void init_write(struct bit_write* b){
	/*init writing buffer*/
	b->buf = 0;
	b->padding = 3; /*3 bit for padding*/
	b->remaining = 8;/*bit left to write*/
	b->save_first =0;
}
void save_bw_as_bw(BWQuadtree quad,char* out)/*.qtn*/
{
	/*concatenate img directory, open file,init buffer and write bw as bw quad */
	struct bit_write w;
	char file_out[240];
	strcpy(file_out,"img/");
	strcat(file_out,out);
	strcat(file_out,".qtn");
	FILE* out1 = fopen(file_out,"wb");
	if(out1 == NULL){
		fprintf(stderr, "Can't open file %s\n",file_out);
		exit(1);
	}
	/*INIT,WRITING*/
	init_write(&w);
	write_bw_quad_as_bw_aux(&w, quad, out1);
	write_end_bw_quadtree(&w, out1);	
	fclose(out1);
}
void save_color_as_color(ColorQuadtree quad,char* out)/*.qtc*/
{	
	/*concatenate img directory, open file, write color as color quad */
	char file_out[240];
	strcpy(file_out,"img/");
	strcat(file_out,out);
	strcat(file_out,".qtc");
	FILE* out1 = fopen(file_out,"w");
	if(out1 == NULL){
		fprintf(stderr, "Can't open file %s\n",file_out);
		exit(1);
	}
	/*WRITING*/
	write_color_quad_as_color_aux(quad, out1);
	fclose(out1);
}
void save_bw_as_color(BWQuadtree quad, char* out){/*.qtc*/
	/*concatenate img directory, open file, write bw as color quad */
	char file_out[240];
	strcpy(file_out,"img/");
	strcat(file_out,out);
	strcat(file_out,".qtc");
	FILE* out1 = fopen(file_out,"w");
	if(out1 == NULL){
		fprintf(stderr, "Can't open file %s\n",file_out);
		exit(1);
	}
	/*WRITING*/
	write_bw_quad_as_color_aux(quad,out1);
	fclose(out1);
}
void save_color_as_bw(ColorQuadtree quad, char*out){/*.qtn*/
	/*concatenate img directory, open file, init buffer, write color as bw quad */
	struct bit_write w;
	char file_out[240];
	strcpy(file_out,"img/");
	strcat(file_out,out);
	strcat(file_out,".qtn");
	FILE* out1 = fopen(file_out,"wb");
	if(out1 == NULL){
		fprintf(stderr, "Can't open file %s\n",file_out);
		exit(1);
	}
	/*INIT,WRITING*/
	init_write(&w);
	write_color_quad_as_bw_aux(&w, quad, out1);
	write_end_bw_quadtree(&w, out1);	/*write remaining bits*/
	fclose(out1);
}
void write_bw_quad_as_bw_aux(struct bit_write* b, BWQuadtree quad, FILE * f){
	/*write a bw as bw , bit by bit*/
	if(quad->NE == NULL && quad->NO == NULL && quad->SE == NULL && quad->SO == NULL){/*if leaf*/
		
		b->buf = ((b->buf* 2) + 1);/*is leaf so +1 in the buffer*/
		b->remaining--;
		if((b->padding + (8 - b->remaining)) % 8 == 0)/*if buffer full*/
		{
			if(b->padding == 3)
				b->save_first = b->buf;
			fwrite(&(b->buf),1,1, f);
			b->padding = 0;
			b->remaining = 8;
		}

		b->buf = (b->buf*2) + quad->BLACK ;	 /*put leaf color 0/1 */
	}
	else 
		b->buf = b->buf * 2 ; /*else add 0 for node*/

	b->remaining--;
	
	if((b->padding + (8 - b->remaining)) % 8 == 0)/*if full*/
	{
		if(b->padding == 3)/*save first byte*/
			b->save_first = b->buf;
		fwrite(&(b->buf),1,1, f);
		b->padding = 0;
		b->remaining = 8;

	}

	/*preorder traversal*/
	if(quad->NO != NULL)
		write_bw_quad_as_bw_aux(b,quad->NO,f);

	if(quad->NE != NULL)
		write_bw_quad_as_bw_aux(b,quad->NE,f);

	if(quad->SE != NULL)
		write_bw_quad_as_bw_aux(b,quad->SE,f);

	if(quad->SO != NULL)
		write_bw_quad_as_bw_aux(b,quad->SO,f);
}

void write_color_quad_as_bw_aux(struct bit_write* b, ColorQuadtree quad, FILE * f){
	if(quad->NE == NULL && quad->NO == NULL && quad->SE == NULL && quad->SO == NULL){
		
		b->buf = ((b->buf* 2) + 1);/*is leaf so +1*/
		b->remaining--;
		if((b->padding + (8 - b->remaining)) % 8 == 0)/*if buffer full*/
		{
			if(b->padding == 3)
				b->save_first = b->buf;
			fwrite(&(b->buf),1,1, f);
			b->padding = 0;
			b->remaining = 8;
		}

		b->buf = (b->buf*2) + convert_color_to_bw(quad) ;	 /*put leaf color 0/1 */
	}
	else 
		b->buf = b->buf * 2 ;

	b->remaining--;
	/*if buffer full, write it and , reinitialize value*/
	if((b->padding + (8 - b->remaining)) % 8 == 0)
	{
		if(b->padding == 3)/*save firs byte*/
			b->save_first = b->buf;
		fwrite(&(b->buf),1,1, f);/*write buffer*/
		b->padding = 0;
		b->remaining = 8;

	}

	/*preorder traversal*/
	if(quad->NO != NULL)
		write_color_quad_as_bw_aux(b,quad->NO,f);

	if(quad->NE != NULL)
		write_color_quad_as_bw_aux(b,quad->NE,f);

	if(quad->SE != NULL)
		write_color_quad_as_bw_aux(b,quad->SE,f);

	if(quad->SO != NULL)
		write_color_quad_as_bw_aux(b,quad->SO,f);
}

void write_end_bw_quadtree(struct bit_write* b, FILE* f){/*.qtn*/
	if(b->remaining == 0)/*return if there is no bit to ignore, writing is done*/
		return;

	/*write remaining bits*/
	else if(b->remaining != 8){/*add padding to beginning and fill the last byte with 0 using left shift*/
		
		unsigned char decalage = b->buf << b->remaining;/*shift the last byte*/

		fwrite(&(decalage),1,1,f);/*write it*/

		fseek(f, 0, SEEK_SET);/*get back to beginning*/

		unsigned char t = b->remaining << 5; /*padding*/
		t+= b->save_first;/*padding + saved first byte*/
		fwrite(&(t),1,1,f);/*write it at the beginning*/
	}
	
}
void write_bw_quad_as_color_aux(BWQuadtree quad, FILE * f){
	/*write a bw quad as color*/
	if(quad->NE == NULL && quad->NO == NULL && quad->SE == NULL && quad->SO == NULL){
		/*write 0000 if bw quad leaf is BLACK*/
		fprintf(f,"1%c%c%c%c",!(quad->BLACK)*255,!(quad->BLACK)*255,!(quad->BLACK)*255,255);
	}
	else /*if node*/
		fprintf(f,"0");

	/*preorder traversal*/
	if(quad->NO != NULL)
		write_bw_quad_as_color_aux(quad->NO,f);

	if(quad->NE != NULL)
		write_bw_quad_as_color_aux(quad->NE,f);

	if(quad->SE != NULL)
		write_bw_quad_as_color_aux(quad->SE,f);

	if(quad->SO != NULL)
		write_bw_quad_as_color_aux(quad->SO,f);
}

void write_color_quad_as_color_aux(ColorQuadtree quad, FILE * f){
	if(quad->NE == NULL && quad->NO == NULL && quad->SE == NULL && quad->SO == NULL){
		fprintf(f,"1%c%c%c%c",quad->r,quad->g,quad->b,quad->a);
	}
	else 
		fprintf(f,"0");

	if(quad->NO != NULL)
		write_color_quad_as_color_aux(quad->NO,f);

	if(quad->NE != NULL)
		write_color_quad_as_color_aux(quad->NE,f);

	if(quad->SE != NULL)
		write_color_quad_as_color_aux(quad->SE,f);

	if(quad->SO != NULL)
		write_color_quad_as_color_aux(quad->SO,f);
}


/*
void write_mini_bw_quad(BWQuadtree quad, char* out)
{
}
void write_mini_color_quad(ColorQuadtree quad, char* out)
{
}
*/