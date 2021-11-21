#include <stdio.h>
#include <stdlib.h>

#include "lecture.h"

int init_bit_read(struct bit_read* byte, FILE* file){
	/*initialize bit_read structure*/
	/*return 0 if the file is not empty and -1 if empty*/

	fseek(file, 0, SEEK_END);/*go to the end of the file*/
	byte->bytesize = ftell(file);/*get byte size of the file*/
	fseek(file, 0, SEEK_SET);/*back to beginning*/

	if(byte->bytesize != 0) {/*if not empty*/
		byte->file = file;	
		byte->current = fgetc(file);/*get byte*/
		byte->bytepos = 1;

		byte->padding = byte->current >> 5; /*right shift first byte to get padding value (between 0 and 7)*/
		byte->remaining = 4; /* skip first 3 bits*/
		return 0;
	}
	else{
		fprintf(stderr, "File is Empty.\n");
		return -1;
	}
}

int read_bit(struct bit_read* byte){
	/* read one bit and return it,	return -1 if all bit of the last byte have been read*/
	if((byte->bytepos == byte->bytesize) && (byte->remaining+1 == byte->padding))
		return -1;

	int bit_pos = (1 << byte->remaining); /*right shift a 1 to the position of the bit to read*/
	int bit = (byte->current & bit_pos ) != 0 ? 1 : 0;/*get bit*/
	byte->remaining--;
	
	if((byte->remaining == -1) && (byte->bytepos != byte->bytesize)){
	/*if all bit in current byte have been read then get the next byte*/
		byte->current = fgetc(byte->file);
		byte->bytepos++;
		byte->remaining = 7;
	}
	return bit;
}
void build_color_quadtree_from_file(ColorQuadtree* quad, char** in){

	/*concatenate the img directory, read file, and build a color quadtree*/
	char file_in[240];
	strcpy(file_in,"img/");
	strcat(file_in,*in);
	FILE* in1 = fopen(file_in, "r");
	if(in1 == NULL){
		fprintf(stderr, "Can't open file\n");
		MLV_draw_text_box(550,380,300,30,"FILE NOT FOUND !",1,MLV_COLOR_RED,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
		MLV_actualise_window();	    		
		MLV_wait_milliseconds(300);
		return;
	}
	/*BUILD*/
	build_color_quad_file_aux(quad, in1);
	fclose(in1);
}

void build_color_quad_file_aux(ColorQuadtree* quad, FILE* in){
	/*build a color quadtree from file.qtc*/
	unsigned char c = 0;
	int i = 0;
	unsigned char tab[4];
	if(fread(&c,1,1,in)==1)
	{
		if(c == '1')/*if leaf*/
		{			
			for(i =0; i<4; i++)/*reads color value of a leaf*/
			{
				if(fread(&(tab[i]),1,1,in) == 1)/*store all value in a tab*/
					;				
				else{
					fprintf(stderr, "Corrupted file.qtc\n");
					exit(1);
				}
				if(i==3)
					*quad = allocate_color_quad(0,0,1,tab[0],tab[1],tab[2],tab[3]);

			}
			return;
		}
		else if(c == '0')/*if not leaf, allocate node, and preorder traversal*/
		{
			*quad = allocate_color_quad(1,1,1,1,1,1,0);
			build_color_quad_file_aux(&((*quad)->NO),in);
			build_color_quad_file_aux(&((*quad)->NE),in);
			build_color_quad_file_aux(&((*quad)->SE),in);
			build_color_quad_file_aux(&((*quad)->SO),in);
			return;
		}
    }
}
void build_bw_quadtree_from_file(BWQuadtree* quad, char** in)
{	

	/*concatenate img directory, reads file, init buffer and create bw quadtree*/
	struct bit_read b;	
	char file_in[240];
	strcpy(file_in,"img/");
	strcat(file_in,*in);
	FILE *in1 = fopen(file_in, "rb");
	if(in1 == NULL){
		fprintf(stderr, "Can't open file\n");
		MLV_draw_text_box(550,380,300,30,"FILE NOT FOUND !",1,MLV_COLOR_RED,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
		MLV_actualise_window();	    		
		MLV_wait_milliseconds(300);
		MLV_actualise_window();	
		return;
	}
	/*INIT, BUILD*/
	init_bit_read(&b, in1);
	build_bw_quad_file_aux(&b, quad, in1);
	fclose(in1);
}

void build_bw_quad_file_aux(struct bit_read* b, BWQuadtree* quad, FILE* in){
	/*build a black and white quadtree from file.qtn*/
	unsigned char c;
	/*while there is something to read in the buffer*/
	while((c = read_bit(b)) != -1){
		if(c == 1){/*if its a 1(leaf) then read next bit to get leaf color*/
			if((c = read_bit(b)) != -1){
				*quad = allocate_bw_quad(0,0,1,c);
				return;								
			}
			else{
				fprintf(stderr, "Corrupted file.qtn\n");
				exit(1);
			}
		}
		else if(c == 0)/*if not leaf, allocate node, and preorder traversal*/
		{
			*quad = allocate_bw_quad(0,0,1,-1);
			build_bw_quad_file_aux(b,&((*quad)->NO),in);
			build_bw_quad_file_aux(b,&((*quad)->NE),in);
			build_bw_quad_file_aux(b,&((*quad)->SE),in);
			build_bw_quad_file_aux(b,&((*quad)->SO),in);	
			return;
		}
    }
}

/*used for test*/
void display_bw_quadtree_file(struct bit_read b)
{
	int i;
	while((i = read_bit(&b)) != -1){
		printf("%d",i );
		if(b.remaining == 7) printf(" ");
	}
	printf("\n" ) ;

}

/*used for test*/
void display_color_quadtree_file(FILE* in){
	unsigned char c;
	int i = 0;
	while(fread(&c,1,1,in) == 1){
		if(c == '1'){
			for(i = 0; i < 4 ; i++){
				fread(&c,1,1,in);
				if(i==0)
					printf("r:%d ",c);
				if(i==1)
					printf("g:%d ",c);
				if(i==2)
					printf("b:%d ",c);
				if(i==3)
					printf("a:%d\n",c);
			}		
				
		}
		printf("0\n");

    }
}
