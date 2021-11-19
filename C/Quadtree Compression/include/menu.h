#ifndef __MENU__
#define __MENU__

#include "lecture.h"

/*perform action depending on what button has been clicked on, or what has been typed in the input box*/
void click_on_button(ColorQuadtree* quad_color,struct bit_read* b,BWQuadtree* quad_bw,FILE* fichier,int x,int y,
	MLV_Event event, MLV_Input_box* input_box,MLV_Mouse_button mouse_button,MLV_Button_state state,
	char* texte1,int* activate,MLV_Image** image1,int circle);

/*return the file extension (ex : .png)*/
const char* get_filename_ext(const char* filename);

/*return basename of file (ex : rgba)*/
char* get_basename(char* texte1);

#endif