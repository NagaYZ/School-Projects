#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "graphique.h"
#include "plateau.h"

int main()
{
	/*INIT*/
	int x,y;
	int x_case_noir , y_case_noir ; 
	int* coord;
	MLV_Mouse_button mouse;
	MLV_Keyboard_button keyboard;	
	MLV_Event event;
	MLV_Button_state state;	
	Plateau P;
	InitialisationPlateau(&P);	
	srand(time(NULL));	

	/*LOAD WINDOW AND IMAGE */
	MLV_create_window("Taquin", "", SIZE, SIZE);
	MLV_Image* image = MLV_load_image("Panda.png");	
	MLV_draw_image(image,0,0);
	MLV_update_window();
	MLV_wait_milliseconds(250);

	/*SHUFFLE PLATEAU AND GET BLACK SQUARE COORDINATES*/
	coord = shufflePlateau(&P);/*coordinates of the black square*/
	x_case_noir = coord[0];
	y_case_noir = coord[1];
	MLV_actualise_window();
	MLV_draw_filled_rectangle(0,0,SIZE,SIZE,MLV_COLOR_BLACK);
	/*WHILE NOT WIN , WAIT FOR MOUSE CLICK AND SWAP VALID SQUARE WITH BLACK SQUARE*/
	while(!Win(P)){
		display_game(P,image);
		
		event = MLV_get_event(&keyboard,NULL,NULL,NULL,NULL,&x,&y,&mouse,&state);

		/*when keyboard or mouse button is pressed*/
		if(state == MLV_PRESSED){
			/*if left click mouse*/
			if((event == MLV_MOUSE_BUTTON) && (mouse == MLV_BUTTON_LEFT )){
				x = pixel_vers_case(x);
				y = pixel_vers_case(y);
				if(!clicValide(P,x,y,x_case_noir, y_case_noir))
					continue;

				swapCarre(&P, x, y, x_case_noir, y_case_noir);
				x_case_noir=x;
				y_case_noir=y;
			}
			/*if keyboard*/
			else if (event == MLV_KEY) {
				/*if key is ARROW(->,<-,up,down)*/
				switch(keyboard){
					case MLV_KEYBOARD_UP:
						x=x_case_noir;
						y=y_case_noir-1;
						break;
					case MLV_KEYBOARD_DOWN:
						x=x_case_noir;
						y=y_case_noir+1;
						break;
					case MLV_KEYBOARD_RIGHT:
						x=x_case_noir+1;
						y=y_case_noir;
						break;
					case MLV_KEYBOARD_LEFT:
						x=x_case_noir-1;
						y=y_case_noir;
						break;
					default:
						continue;
				}
				/*if valid move*/
				if(!clicValide(P,x,y,x_case_noir, y_case_noir))
					continue;

				swapCarre(&P, x, y, x_case_noir, y_case_noir);
				x_case_noir=x;
				y_case_noir=y;
			}
		}		
	}
	display_win();
	MLV_actualise_window();
	MLV_wait_seconds(3);
	MLV_free_window();
	return 1;
}
