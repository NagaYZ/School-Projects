#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affichage.h"
#include "menu.h"
#include "lecture.h"
#include "ecriture.h"

const char* get_filename_ext(const char* filename){
	/*return extension of file*/
	const char *dot = strrchr(filename, '.');/*get last occurence of a dot .   .*/
	if(!dot || dot == filename) return "";/*if nothing*/
	return dot;/*return part after the dot (aka extension)*/
}

char* get_basename(char* texte) {
	/*return basename of file*/
    char *basename;
    char *ext;
    if ((basename = malloc (strlen (texte) + 1)) == NULL)
    	return NULL;
    strcpy (basename, texte);
    ext = strrchr (basename, '.');/*get last occurence of a dot .   */
    if (ext != NULL)
        *ext = '\0';/*remove extension*/
    return basename;
}

void click_on_button(ColorQuadtree* quad_color,struct bit_read* b,BWQuadtree* quad_bw,FILE* fichier,int x,int y,
	MLV_Event event, MLV_Input_box* input_box,MLV_Mouse_button mouse_button,MLV_Button_state state,char* texte1,int* activate,MLV_Image** image1,int circle){

    if(*activate > 0){/*if input_box active */
        MLV_draw_all_input_boxes();
        
    }
    /*parse text in input_box*/
    if((strlen(texte1) >1)&&(*activate == 1)){
    	char file[240];
		strcpy(file,"img/");
		strcat(file,texte1);
 	 	const char* ext = get_filename_ext(texte1);
	    if(!strcmp(texte1,"quit")){/*if enter "quit" in input_box */
	        *activate = -1;
	        return;
	    }

		else if(!strcmp(ext, ".qtn" )){/*if bw file*/
	    	/*free quadtree already made*/
	    	if(*quad_bw)
	    	{
    			free_bw_quad(quad_bw);	
    			*quad_bw = NULL;
    		}
    		if(*quad_color){
    			free_color_quad(quad_color);
    			*quad_color = NULL;
    		}
    		/*display, and build quadtree*/
    		display_re_input_box();
			build_bw_quadtree_from_file(quad_bw,&texte1);
			MLV_draw_filled_rectangle(0,0,512,512,MLV_COLOR_BLACK);
			if(*quad_bw != NULL){
				*activate = 0;
				display_bw_quadtree_from_file(*quad_bw,0,0,512,circle);
			}else
				*texte1='\0';
		}
	    
	    else if(!strcmp(ext, ".qtc" )){/*if color file*/
			/*free quadtree already made*/
			if(*quad_bw)
	    	{
    			free_bw_quad(quad_bw);	
    			*quad_bw = NULL;
    		}
    		if(*quad_color){
    			free_color_quad(quad_color);
    			*quad_color = NULL;
    		}
    		/*display, and build quadtree*/
    		display_re_input_box();    		
	    	build_color_quadtree_from_file(quad_color, &texte1);
	    	MLV_draw_filled_rectangle(0,0,512,512,MLV_COLOR_BLACK);
	    	if(*quad_color != NULL){
	    		*activate = 0;
	    		display_color_quadtree_from_file(*quad_color,0,0,512,circle);
	    	}else
	    		*texte1='\0';
	    }
	    else if(!strcmp(ext, ".gmn" )){
			display_mini_disabled();
			display_re_input_box();
			*texte1 = '\0';
		}
	    
	    else if(!strcmp(ext, ".gmc" )){
	    	display_mini_disabled();
	    	display_re_input_box();
	    	*texte1 = '\0';

	    }
	    /*IF FILE IS IMAGE , OPEN IT AND DRAW IT*/
	    else if(!strcmp(ext,".ico") || !strcmp(ext,".bmp") || !strcmp(ext,".pdf")|| 
	          	!strcmp(ext,".png")  || !strcmp(ext,".jpg") || !strcmp(ext,".gif")|| 
	          	!strcmp(ext,".tiff")  || !strcmp(ext,".cur")  || !strcmp(ext,".pnm") || 
	          	!strcmp(ext,".xpm") || !strcmp(ext,".lbm")  || !strcmp(ext,".pcx") || !strcmp(ext,".xv") )
	    {
	        *image1 = MLV_load_image(file);
	        if(*image1 != NULL){	   
	        	/*free already made quadtree*/
	        	if(*quad_bw){
	    			free_bw_quad(quad_bw);	
	    			*quad_bw = NULL;
	    		}
	    		if(*quad_color){
	    			free_color_quad(quad_color);
	    			*quad_color = NULL;
	    		}         
		        display_image(*image1);		       
		        display_re_input_box();
		        *activate = 0;	        
	    	}
	    	else {
	    		MLV_free_image(*image1);
	    		MLV_draw_filled_rectangle(0,0,512,512,MLV_COLOR_BLACK);	
	    		/*free already made quadtree*/
	    		if(*quad_bw){
	    			free_bw_quad(quad_bw);	
	    			*quad_bw = NULL;
	    		}
	    		if(*quad_color){
	    			free_color_quad(quad_color);
	    			*quad_color = NULL;
	    		}
	    		MLV_draw_text_box(550,380,300,30,"IMAGE NOT FOUND !",1,MLV_COLOR_RED,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	    		MLV_actualise_window();	    		
	    		MLV_wait_milliseconds(300);
	    		*texte1 = '\0';
	    	}
	    }
	    else{/*DISPLAY ,IF FILE IS NOR AN IMAGE OR A FILE, AND RESET TEXT INPUT*/
	    	MLV_draw_text_box(550,380,300,30,"FILE NOT FOUND !",1,MLV_COLOR_RED,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
    		MLV_actualise_window();	    		
    		MLV_wait_milliseconds(300);
    		*texte1 = '\0';
	    }
	}
	/*ON CLICK BUTTON */
    if((event == MLV_MOUSE_BUTTON) && (mouse_button == MLV_BUTTON_LEFT ) && (state == MLV_RELEASED) )/*CLICK ON BUTTON*/
    {
        if((y <= 460 && y >= 430 ) && (x <= 850 && x >= 550 )){/*OUTSIDE , CLOSE INPUT_BOX*/
           *activate = -1;
           return;
        }

        else if((x <= 850 && x >= 550 ) && (y <= 410 && y >= 380))  /*ON OPEN FILE INPUT_BOX*/
            *activate = 2;            
        
        else if((y <= 360 && y >= 330 ) && (x <= 850 && x >= 550)){  /*ON SAVE GRAPHE BW*/
            display_mini_disabled();
            return;
            /*graphe_minimisé_bw();*/
        }

        else if((y <= 310 && y >= 280 ) && (x <= 850 && x >= 550)){  /*ON SAVE GRAPHE COLOR*/		
			display_mini_disabled();
			return;
			/*graphe_minimisé_color();*/
		}

		else if((y <= 260 && y >= 230 ) && (x <= 850 && x >= 550)){  /*ON MINIMISATION*/
			printf("Minimisation..\n");

			/*MINIMISE EXISTING QUADTREE AND DISPLAY IT*/
			if(*quad_bw){
				MLV_draw_filled_rectangle(0,0,520,520,MLV_COLOR_BLACK);
				minimise_bw_quad(quad_bw);
				display_bw_quadtree_from_file(*quad_bw,0,0,512,circle);
			}
			else if(*quad_color){
				MLV_draw_filled_rectangle(0,0,520,520,MLV_COLOR_BLACK);
				minimise_color_quad(quad_color);
				display_color_quadtree_from_file(*quad_color,0,0,512,circle);
			}
			else{/*DISPLAY IF NO QUADTREE*/
				display_no_quadtree();
				return;
			}					
			display_done();
		}

		else if((y <= 210 && y >= 180 ) && (x <= 850 && x >= 550)){  /*ON SAVE BW*/
			if(!texte1){
				display_no_quadtree();
				return;
			}
			if(*quad_bw)
				save_bw_as_bw(*quad_bw, get_basename(texte1));
			else if(*quad_color)
				save_color_as_bw(*quad_color, get_basename(texte1));
			else{
				display_no_quadtree();
				return;
			}
			display_done();
			printf("Saved as bw done.\n");
		}

		else if((y <= 160 && y >= 130 ) && (x <= 850 && x >= 550)){ /*ON SAVE COLOR*/
			if(!texte1){
				display_no_quadtree();
				return;
			}
			if(*quad_bw)/*if quadtree made is bw*/
				save_bw_as_color(*quad_bw, get_basename(texte1));
			else if(*quad_color)/*if quadtree made is color*/
				save_color_as_color(*quad_color, get_basename(texte1));
			else{
				display_no_quadtree();
				return;
			}
			display_done();
			printf("Saved as color done.\n");
		}

        else if((y <= 110 && y >= 80 ) && (x <= 850 && x >= 550)){ /*ON QUADTREE*/
        	if(*quad_color || *quad_bw){/*if quadtree already made then do NOT make it again*/
    			display_done();
    			return;
    		} 	
    		if(!*image1){
				display_no_image();
				return;
			}		
    		printf("quadtree...\n");
    		MLV_draw_filled_rectangle(0,0,520,520,MLV_COLOR_BLACK);
        	if(is_color_image(*image1))
           		build_color_quad_image(quad_color,*image1,circle);
           	else
           		build_bw_quad_image(quad_bw,*image1,circle);;
           	display_done();
           	 
        }
        else { 
            *activate = 0;             
            MLV_draw_text_box(550,380,300,30,"OPEN FILE",1,MLV_COLOR_WHITE,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
        	MLV_draw_filled_rectangle(550,40,30,10,MLV_COLOR_BLACK);
        }       
    }
    MLV_actualise_window();
}