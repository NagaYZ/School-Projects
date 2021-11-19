#include <stdio.h>
#include <stdlib.h>

#include "quadtree.h"


void display_menu(){
	/*DISPLAY ALL BUTTON*/
	MLV_draw_filled_rectangle(512,0,950,512,MLV_COLOR_BLACK); 
	MLV_draw_text_box(550,430,300,30,"EXIT",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(550,380,300,30,"OPEN FILE",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(550,330,300,30,"SAVE GRAPHE ( BLACK & WHITE )",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(550,280,300,30,"SAVE GRAPHE ( COLOR )",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(550,230,300,30,"MINIMISATION",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(550,180,300,30,"SAVE BINARY ( BLACK & WHITE )",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(550,130,300,30,"SAVE ( COLOR )",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box(550,80,300,30,"QUADTREE",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
}

void display_re_input_box(){
	MLV_draw_text_box(550,380,300,30,"OPEN FILE",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_actualise_window();	 
}

void display_image(MLV_Image* image){
	MLV_draw_image(image,0,0);
	MLV_actualise_window();
}

void display_no_image(){
	/*DISPLAY WHEN THERE IS NO IMAGE WHEN CLICK ON QUADTREE*/
   	printf("No image\n");
	MLV_draw_text(550,40,"NO IMAGE !",MLV_COLOR_WHITE);
	MLV_actualise_window();
	MLV_wait_milliseconds(400);
	MLV_draw_filled_rectangle(550,40,300,20,MLV_COLOR_BLACK);
	MLV_actualise_window();
}


void display_done(){
	/*DISPLAY WHEN QUADTREE IS DONE*/
   	printf("done\n");
	MLV_draw_text(550,40,"DONE !",MLV_COLOR_WHITE);
	MLV_actualise_window();
	MLV_wait_seconds(2);
	MLV_draw_filled_rectangle(550,40,300,20,MLV_COLOR_BLACK);
	MLV_actualise_window();
}

void display_no_quadtree(){
	/*Display when try to save a quadtree when there is no quadtree*/
	MLV_draw_text(550,40,"NO QUADTREE YET !",MLV_COLOR_WHITE);
	MLV_actualise_window();
	MLV_wait_milliseconds(500);
	MLV_draw_filled_rectangle(550,40,300,20,MLV_COLOR_BLACK);
	MLV_actualise_window();
	printf("No quadtree\n");
}

void display_mini_disabled(){
	MLV_draw_text(550,40,"MINIMISATION DISABLED ",MLV_COLOR_WHITE);
	MLV_actualise_window();
	MLV_wait_milliseconds(500);
	MLV_draw_filled_rectangle(550,40,300,20,MLV_COLOR_BLACK);
	MLV_actualise_window();
	printf("minimisation currently disabled.\n");
}

void display_color_quadtree_from_image(ColorQuadtree quad,int circle){
	/*display square of color quadtree,  used when building from image to display step by step*/

	MLV_draw_filled_rectangle(quad->x,quad->y,quad->zone,quad->zone,MLV_COLOR_BLACK);
	if(circle)
		MLV_draw_filled_circle(quad->x+quad->zone/2,quad->y+quad->zone/2,(quad->zone/2)-1,MLV_rgba(quad->r,quad->g,quad->b,quad->a));	
	else
		MLV_draw_filled_rectangle(quad->x,quad->y,quad->zone,quad->zone,MLV_rgba(quad->r,quad->g,quad->b,quad->a));	
}

void display_color_quadtree_from_file(ColorQuadtree quad,int x, int y, int zone_start,int circle){
	/*display each leaf of a color quadtree built from a file*/
	if(quad->NE == NULL && quad->NO == NULL && quad->SE == NULL && quad->SO == NULL){

		if(circle)
			MLV_draw_filled_circle(x+zone_start/2,y+zone_start/2,(zone_start/2)-1,MLV_rgba(quad->r,quad->g,quad->b,quad->a));	
		else
			MLV_draw_filled_rectangle(x,y,zone_start,zone_start,MLV_rgba(quad->r,quad->g,quad->b,quad->a));	
		return;
	}	
	/*preorder traversal , change value of x,y,zone depending on (NO,NE,SE,SO)*/
	display_color_quadtree_from_file(quad->NO, x, y, zone_start/2,circle);
	display_color_quadtree_from_file(quad->NE, x+(zone_start/2), y, zone_start/2,circle);
	display_color_quadtree_from_file(quad->SE, x+(zone_start/2), y+(zone_start/2), zone_start/2,circle);
	display_color_quadtree_from_file(quad->SO, x, y+(zone_start/2) ,zone_start/2,circle);
}

void display_bw_quadtree_from_file(BWQuadtree quad,int x,int y,int zone_start,int circle){
	/*display each leaf of a bw quadtree built from a file*/
	if(quad->NE == NULL && quad->NO == NULL && quad->SE == NULL && quad->SO == NULL){
		if(circle)
			MLV_draw_filled_circle(x+zone_start/2,y+zone_start/2,(zone_start/2)-1,quad->BLACK?MLV_COLOR_BLACK : MLV_COLOR_WHITE);	
		else
			MLV_draw_filled_rectangle(x,y,zone_start,zone_start,quad->BLACK?MLV_COLOR_BLACK : MLV_COLOR_WHITE);
		return;
	}	
	
	/*preorder traversal , change value of x,y,zone depending on (NO,NE,SE,SO)*/
	display_bw_quadtree_from_file(quad->NO, x, y, zone_start/2,circle);
	display_bw_quadtree_from_file(quad->NE, x+(zone_start/2), y, zone_start/2,circle);
	display_bw_quadtree_from_file(quad->SE, x+(zone_start/2), y+(zone_start/2), zone_start/2,circle);
	display_bw_quadtree_from_file(quad->SO, x, y+(zone_start/2) ,zone_start/2,circle);
}

void display_bw_quadtree_from_image(BWQuadtree quad,int circle){
	/*display square of bw quadtree,  used when building from image to display step by step*/
	MLV_draw_filled_rectangle(quad->x,quad->y,quad->zone,quad->zone,MLV_COLOR_BLACK);
	if(circle)
		MLV_draw_filled_circle(quad->x+quad->zone/2,quad->y+quad->zone/2,(quad->zone/2)-1,quad->BLACK?MLV_COLOR_BLACK : MLV_COLOR_WHITE);	
	else
		MLV_draw_filled_rectangle(quad->x,quad->y,quad->zone,quad->zone,quad->BLACK?MLV_COLOR_BLACK : MLV_COLOR_WHITE);

}

void usage(){
	/*display command line usage and arg*/
    printf("Usage:\t ./projet [-help][-circle]\n\n\t-help : display the usage of the program\n\t-circle : transform square to circle to see where quadtree are small/big\n");
	/*display program usage*/
	printf("\nThis program can compress and decompress image using Quadtrees.\n\n");
	printf("To start, Click on OPEN FILE, and type the filename of the image/file you want to use. NOTE: file must be in the img folder.\n");
	printf("To get a Quadtree representation, Click on QUADTREE, if the opened file is already a quadtree, then the process will NOT be done a second time.\n");
	printf("To save your Quadtree, Click on SAVE ( BLACK & WHITE ) if you want to save a Black&White representation of your quadtree,\n\t\t    Or Click on SAVE ( COLOR ), to save a color representation of your quadtree.\nSaved file have the same name as the file you used (ex: rgba.png->rgba.qtc).\n");
	printf("To exit the program, Click on EXIT, or enter quit in the OPEN FILE input_box.\n");
	printf("\nOther Buttons are currently disabled due to malfunctioning.\n");
	/*credits*/
	printf("\nMade by ZAIANI Yassine and BEKHTI Abderahman.\n\n");
}