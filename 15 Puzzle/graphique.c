#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "graphique.h"

void display_win(){
    /*print WIN in the black square when the game is won*/
    MLV_draw_text(3*(SIZE/4)+(SIZE/16), 3*(SIZE/4)+(SIZE/8),"YOU WIN!", MLV_COLOR_WHITE);
}

void display_game(Plateau P,MLV_Image* image){
    /*display the game with the black square*/
    int i, j;

    for(i = 0; i < NB_LIG ; i++){
        for(j = 0; j < NB_COL; j++){

            MLV_draw_partial_image(image, P.bloc[i][j].lig*(SIZE/4) , P.bloc[i][j].col*(SIZE/4), (SIZE/4)-6, (SIZE/4)-6, i*(SIZE/4), j*(SIZE/4));
            
            if(P.bloc[i][j].lig == 3 && P.bloc[i][j].col == 3)/*BLACK SQUARE*/
                MLV_draw_filled_rectangle(i*(SIZE/4), j*(SIZE/4), SIZE/4, SIZE/4, MLV_COLOR_BLACK);
        }
    }
    MLV_actualise_window();
}

int pixel_vers_case(int x){

    return x / (SIZE/4);
}
