#include <stdio.h>
#include <stdlib.h>
	
#include "quadtree.h"
#include "menu.h"
#include "calcul.h"
#include "affichage.h"

int main(int argc, char *argv[]){
    /*ARGUMENTS*/
    int i,circle=0,usage_count=1;
    /*WRONG NUMBER OF ARG*/
    if(argc >3){
        fprintf(stderr, "Too many arguments.\n");
        usage();
        exit(EXIT_FAILURE);
    }
     /*PARSE ARG*/
    for(i=1; i < argc; i++){
        if(!strcmp(argv[i], "-help")){
            usage();
            usage_count=1;
        }
        else if(!strcmp(argv[i],"-circle"))
            circle=1;

        else {
            fprintf(stderr, "Unknown argument(s).\n");
            if(!usage_count)
                usage();
            exit(EXIT_FAILURE);
        }   
    }

    /*START*/
    int x=0,y=0;/*for the mouse*/

    /*INIT MLV , STRUCT*/
    MLV_create_window("QuadTree","QuadTree",900,512); /* create window */

    /*USED BY QUADTREES*/
    ColorQuadtree quad_color = NULL;
	struct bit_read* b = NULL;
	BWQuadtree quad_bw = NULL;
    FILE* fichier = NULL; 

    /*USED BY MLV*/
    MLV_Event event;
    MLV_Input_box *input_box = NULL;
    MLV_Mouse_button mouse_button;
    MLV_Button_state state;
    MLV_Image* image1= NULL;

    MLV_create_input_box(/*create input_box*/
        550, 380,
        300, 30, 
        MLV_COLOR_GREEN, MLV_COLOR_GREEN,
        MLV_COLOR_BLACK, "img/"
    );

    /*TEXT TO GET INPUT*/
    char* texte= NULL;
    char *texte1 = (char*) malloc(sizeof(char));
    *texte1 = '\0';
    if(texte1 == NULL)
    {
        fprintf(stderr, "Can't allocate texte\n");
        exit(1);
    }
    int activate = 0;

    /*DISPLAY MENU*/
    display_menu();    
    
    /*MAIN LOOP*/
    while(activate != -1){/*while not typed "quit" or clicked on exit*/
        event = MLV_get_event( /*GET EVENT*/
            NULL, NULL, NULL,
            &texte, &input_box,
            &x, &y, &mouse_button,&state);

        if( event == MLV_INPUT_BOX ){/*if ENTER the text typed in the input_box*/
            activate = 1;
            free( texte1 );
            texte1 = texte;
        }
        /*handle action on button press*/
        click_on_button(&quad_color,b,&quad_bw,fichier,x,y,event,input_box,mouse_button,state,
            texte1,&activate,&image1,circle);      
    }
    
    /*FREE EVERYTHING HEHE*/
    if(quad_color)
        free_color_quad(&quad_color);
    if(quad_bw)
        free_bw_quad(&quad_bw);
    if(fichier)
        free(fichier);
    if(b)
        free(b);
    free(texte1);
    if(image1)
        MLV_free_image(image1); 
    if(input_box)
        MLV_free_input_box(input_box);
    MLV_free_window();
    /*END*/
    return 0;
}
