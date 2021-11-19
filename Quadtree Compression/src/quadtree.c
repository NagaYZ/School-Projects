#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "quadtree.h"
#include "affichage.h"

BWQuadtree allocate_bw_quad(int x ,int y,int zone, int color)
{/*Allocate a bw quadtree , and initialize its parameter x,y,zone,color (1, 0) ,
	and init all children to NULL*/
	assert(x >= 0 && x < 512);
	assert(y >= 0 && y < 512);
	assert(zone >= 1 && zone < 512);
	assert(color >= -1 && color <= 1);
	BWQuadtree quad = (BWQuadtree) malloc(sizeof(struct bw_quadtree));

	if (quad != NULL)
	{
		quad->x = x;
		quad->y = y;
		quad->zone = zone;
		quad->BLACK = color;
		quad->NO = NULL;
		quad->NE = NULL;
		quad->SE = NULL;
		quad->SO = NULL;
	}
	else{
		fprintf(stderr, "Cannot allocate bw quadtree.\n");
		exit(1);
	}
	return quad;
}

ColorQuadtree allocate_color_quad(int x ,int y, int zone,unsigned char r,unsigned char g, unsigned char b, unsigned char alpha)
{/*Allocate a color quadtree , and initialize its parameter x,y,zone,r,g,b,a ,
	and init all children to NULL*/
	assert(x >= 0 && x < 512);
	assert(y >= 0 && y < 512);
	assert(zone >= 1 && zone <= 512);
	assert(r >= 0 && r <= 255);
	assert(g >= 0 && g <= 255);
	assert(b >= 0 && b <= 255);
	assert(alpha >=0 && alpha <= 255);

	ColorQuadtree quad = (ColorQuadtree) malloc(sizeof(struct color_quadtree));

	if (quad != NULL)
	{
		quad->x = x;
		quad->y = y;
		quad->zone = zone;
		quad->r = r;
		quad->g = g;
		quad->b = b;
		quad->a = alpha;
		quad->NO = NULL;
		quad->NE = NULL;
		quad->SE = NULL;
		quad->SO = NULL;
	}
	else{
		fprintf(stderr, "Can't allocate color quadtree\n" );
		exit(1);
	}
	return quad;
}

int color_node_all_leaf_same_color(ColorQuadtree quad)
{
	if( (quad->NO->r == quad->NE->r)&& 
		(quad->NO->r == quad->SE->r)&&
		(quad->NO->r == quad->SO->r)&&
		(quad->NO->g == quad->NE->g)&& 
		(quad->NO->g == quad->SE->g)&&
		(quad->NO->g == quad->SO->g)&&
		(quad->NO->b == quad->NE->b)&& 
		(quad->NO->b == quad->SE->b)&&
		(quad->NO->b == quad->SO->b)&&
		(quad->NO->a == quad->NE->a)&& 
		(quad->NO->a == quad->SE->a)&&
		(quad->NO->a == quad->SO->a))
		return 1;
	return 0;

}

int bw_node_all_leaf_same_color(BWQuadtree quad)
{
	if(quad->NO->BLACK == -1)
		return 0;
	if( (quad->NO->BLACK == quad->NE->BLACK)&& 
		(quad->NO->BLACK == quad->SE->BLACK)&&
		(quad->NO->BLACK == quad->SO->BLACK))
		return 1;
	return 0;

}
int same_color_quadtree(ColorQuadtree quad,ColorQuadtree quad2){
	if((quad->x == quad2->x) && (quad->y == quad2->y) && (quad->zone == quad2->zone)
		&& (quad->r == quad2->r) && (quad->g == quad2->g) && (quad->b == quad2->b)
		&& (quad->a == quad2->a) && (quad->NO == quad2->NO) && (quad->NE == quad2->NE)
		&& (quad->SE == quad2->SE) && (quad->SO == quad2->SO))
		return 1;
	
	return 0;
}
int convert_color_to_bw(ColorQuadtree c){
	int color= (c->r * 0.33)+( c->g * 0.33)+ (c->b * 0.33);
	return (color < 128 ? 0 : 1);
}

void build_color_quad_image(ColorQuadtree *quad,MLV_Image* image,int circle){
	/* build color quadtree from image*/
	
	ColorQuadtree pire_zone=NULL,tmp_pire_zone =NULL;
	int zone=0;
	int x=0,y=0;

	int* tab;
	/*first part, get average color of whole image, and split in four square with their average color*/
	tab = average_color_zone(0,0,512,image);
	*quad = allocate_color_quad(0,0,512,tab[0],tab[1],tab[2],tab[3]);	
	display_color_quadtree_from_image(*quad,circle);
	tab = average_color_zone(0,0,256,image);
	(*quad)->NO = allocate_color_quad(0,0,256,tab[0],tab[1],tab[2],tab[3]);
	display_color_quadtree_from_image((*quad)->NO,circle);
	tab = average_color_zone(256,0,256,image);
	(*quad)->NE = allocate_color_quad(256,0,256,tab[0],tab[1],tab[2],tab[3]);
	display_color_quadtree_from_image((*quad)->NE,circle);
	tab = average_color_zone(256,256,256,image);
	(*quad)->SE = allocate_color_quad(256,256,256,tab[0],tab[1],tab[2],tab[3]);
	display_color_quadtree_from_image((*quad)->SE,circle);
	tab = average_color_zone(0,256,256,image);
	(*quad)->SO = allocate_color_quad(0,256,256,tab[0],tab[1],tab[2],tab[3]);
	display_color_quadtree_from_image((*quad)->SO,circle);
	MLV_actualise_window();
	
	tmp_pire_zone = (*quad)->NO;
	pire_zone = worst_error_zone_color(*quad,&tmp_pire_zone,image);/*get first worst zone between the 4*/

	/*while all zone arent perfect, changed to >= 450 to speed up a little the process as it is very slow(on my pc).*/
	while( error_color_zone(pire_zone->x,pire_zone->y,pire_zone->zone,pire_zone->r,pire_zone->g,pire_zone->b,pire_zone->a,image) >= 450){
	
		zone = (pire_zone)->zone /2;
		x = (pire_zone)->x;
		y = (pire_zone)->y;
		
		/*allocate 4 child to the worst zone node*/
		tab = average_color_zone(x,y, zone,image);
		(pire_zone)->NO = allocate_color_quad(x,y,zone,tab[0],tab[1],tab[2],tab[3]);
		display_color_quadtree_from_image((pire_zone)->NO,circle);

		tab = average_color_zone(x + zone, y, zone,image);
		(pire_zone)->NE = allocate_color_quad(x + zone,y,zone,tab[0],tab[1],tab[2],tab[3]);
		display_color_quadtree_from_image(pire_zone->NE,circle);

		tab = average_color_zone(x + zone, y + zone, zone,image);
		(pire_zone)->SE = allocate_color_quad(x + zone,y + zone,zone,tab[0],tab[1],tab[2],tab[3]);
		display_color_quadtree_from_image((pire_zone)->SE,circle);

		tab = average_color_zone(x, y + zone, zone,image);
		(pire_zone)->SO = allocate_color_quad(x,y + zone,zone,tab[0],tab[1],tab[2],tab[3]);
		display_color_quadtree_from_image((pire_zone)->SO,circle);

		MLV_actualise_window();	
		tmp_pire_zone = (pire_zone)->NO;	   
		pire_zone = worst_error_zone_color(*quad,&tmp_pire_zone,image);
		
	}	
}
void build_bw_quad_image(BWQuadtree *quad,MLV_Image* image,int circle){
	/* build bw quadtree from image*/
	
	BWQuadtree pire_zone=NULL,tmp_pire_zone =NULL;
	int zone=0;
	int x=0,y=0;

	int* tab;
	/*first part, get average color of whole image, and split in four square with their average color*/
	tab = average_color_zone(0,0,512,image);
	*quad = allocate_bw_quad(0,0,512,!(tab[0]/255));	
	display_bw_quadtree_from_image(*quad,circle);

	tab = average_color_zone(0,0,256,image);
	(*quad)->NO = allocate_bw_quad(0,0,256,!(tab[0]/255));
	display_bw_quadtree_from_image((*quad)->NO,circle);
	tab = average_color_zone(256,0,256,image);
	(*quad)->NE = allocate_bw_quad(256,0,256,!(tab[0]/255));
	display_bw_quadtree_from_image((*quad)->NE,circle);
	tab = average_color_zone(256,256,256,image);
	(*quad)->SE = allocate_bw_quad(256,256,256,!(tab[0]/255));
	display_bw_quadtree_from_image((*quad)->SE,circle);
	tab = average_color_zone(0,256,256,image);
	(*quad)->SO = allocate_bw_quad(0,256,256,!(tab[0]/255));
	display_bw_quadtree_from_image((*quad)->SO,circle);
	MLV_actualise_window();

	tmp_pire_zone = (*quad)->NO;/*first worst zone, is random leaf between 4*/
	pire_zone = worst_error_zone_bw(*quad,&tmp_pire_zone,image);/*get first worst zone between the 4*/


	/*while all zone arent perfect,  changed to >= 450 to speed up a little the process as it is very slow(on my pc).*/
	while( error_color_zone(pire_zone->x,pire_zone->y,pire_zone->zone,(!pire_zone->BLACK)*255,(!pire_zone->BLACK)*255,(!pire_zone->BLACK)*255,255,image) >= 450){
	
		zone = (pire_zone)->zone /2;
		x = (pire_zone)->x;
		y = (pire_zone)->y;

		/*allocate 4 child to the worst zone node*/
		tab = average_color_zone(x,y, zone,image);
		(pire_zone)->NO = allocate_bw_quad(x,y,zone,!(tab[0]/255));
		display_bw_quadtree_from_image((pire_zone)->NO,circle);

		tab = average_color_zone(x + zone, y, zone,image);
		(pire_zone)->NE = allocate_bw_quad(x + zone,y,zone,!(tab[0]/255));
		display_bw_quadtree_from_image(pire_zone->NE,circle);

		tab = average_color_zone(x + zone, y + zone, zone,image);
		(pire_zone)->SE = allocate_bw_quad(x + zone,y + zone,zone,!(tab[0]/255));
		display_bw_quadtree_from_image((pire_zone)->SE,circle);

		tab = average_color_zone(x, y + zone, zone,image);
		(pire_zone)->SO = allocate_bw_quad(x,y + zone,zone,!(tab[0]/255));
		display_bw_quadtree_from_image((pire_zone)->SO,circle);

		MLV_actualise_window();

		tmp_pire_zone = (pire_zone)->NO;/*new worst zone*/
		pire_zone = worst_error_zone_bw(*quad,&tmp_pire_zone,image);
		
	}	
}

ColorQuadtree worst_error_zone_color(ColorQuadtree quad, ColorQuadtree* pire_zone,MLV_Image* image){	

	/*if leaf, compare leaf error to worst zone error, and replace it if greater*/
	if(quad->NO == NULL && quad->NE == NULL && quad->SE == NULL && quad->SO == NULL ){
		if(error_color_zone(quad->x,quad->y,quad->zone,quad->r,quad->g,quad->b,quad->a,image) 
			> 
			error_color_zone((*pire_zone)->x,(*pire_zone)->y,(*pire_zone)->zone,(*pire_zone)->r,(*pire_zone)->g,(*pire_zone)->b,(*pire_zone)->a,image)){
  			(*pire_zone) = quad;
		}  		
  		return *pire_zone;
	}
	/*preorder traversal*/
	worst_error_zone_color(quad->NO,pire_zone, image);
	worst_error_zone_color(quad->NE,pire_zone, image);
	worst_error_zone_color(quad->SE,pire_zone, image);
	worst_error_zone_color(quad->SO,pire_zone, image);

	return *pire_zone;
}

BWQuadtree worst_error_zone_bw(BWQuadtree quad, BWQuadtree* pire_zone,MLV_Image* image){
	if(quad->NO == NULL && quad->NE == NULL && quad->SE == NULL && quad->SO == NULL ){

		if(error_color_zone(quad->x,quad->y,quad->zone,(!quad->BLACK)*255,(!quad->BLACK)*255,(!quad->BLACK)*255,255,image) 
			> 
			error_color_zone((*pire_zone)->x,(*pire_zone)->y,(*pire_zone)->zone,(!(*pire_zone)->BLACK)*255,(!(*pire_zone)->BLACK)*255,(!(*pire_zone)->BLACK)*255,255,image)){
  			(*pire_zone) = quad;
		}  		
  		return *pire_zone;
	}

	worst_error_zone_bw(quad->NO,pire_zone, image);
	worst_error_zone_bw(quad->NE,pire_zone, image);
	worst_error_zone_bw(quad->SE,pire_zone, image);
	worst_error_zone_bw(quad->SO,pire_zone, image);

	return *pire_zone;
}

/*minimisation to improve*/
void minimise_bw_quad(BWQuadtree* quad)
{
	/*if leaf*/
	if((*quad)->NE == NULL && (*quad)->NO == NULL && (*quad)->SE == NULL && (*quad)->SO == NULL){
		return;
	}
	/*preorder traversal*/
	minimise_bw_quad(&((*quad)->NO));
	minimise_bw_quad(&((*quad)->NE));
	minimise_bw_quad(&((*quad)->SE));
	minimise_bw_quad(&((*quad)->SO));

	/*if a node has all 4 children of the same color, then replace it with one of its children*/
	if(bw_node_all_leaf_same_color(*quad))
		*quad = (*quad)->NO;	
	
	return;
}
/*minimisation to improve*/
void minimise_color_quad(ColorQuadtree* quad)
{
	if((*quad)->NE == NULL && (*quad)->NO == NULL && (*quad)->SE == NULL && (*quad)->SO == NULL){
		return;
	}

	/*preorder traversal*/
	minimise_color_quad(&((*quad)->NO));
	minimise_color_quad(&((*quad)->NE));
	minimise_color_quad(&((*quad)->SE));
	minimise_color_quad(&((*quad)->SO));

	/*if a node has all 4 children of the same color, then replace it with one of its children*/

	if(color_node_all_leaf_same_color(*quad))
		*quad = (*quad)->NO;
}

void free_color_quad(ColorQuadtree* a){
  
  	/*free a color quadtree*/
    if((*a)->NO == NULL && (*a)->NE == NULL && (*a)->SE == NULL && (*a)->SO == NULL ){
        free(*a);
        return;
    }
    free_color_quad(&((*a)->NO));
    free_color_quad(&((*a)->NE));
    free_color_quad(&((*a)->SE));
    free_color_quad(&((*a)->SO)); 
    free(*a);
}

void free_bw_quad(BWQuadtree* a){
  
  	/*free a color quadtree*/
    if((*a)->NO == NULL && (*a)->NE == NULL && (*a)->SE == NULL && (*a)->SO == NULL ){
        free(*a);
        return;
    }
    free_bw_quad(&((*a)->NO));
    free_bw_quad(&((*a)->NE));
    free_bw_quad(&((*a)->SE));
    free_bw_quad(&((*a)->SO)); 
    free(*a);
}