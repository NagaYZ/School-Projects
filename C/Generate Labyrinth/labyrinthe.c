/*Projet Labyrinthe : ZAIANI Yassine*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include <unistd.h>

int H,L,CELL_SIZE,nbr_classe;/*Variables Globales : hauteur,largeur,taille cellule(mlv) et nombre de classe(--acces)*/

char* intersections[2][2][2][2] = 
   { {{{" ","╶"},{"╴","─"}},{{"╵","└"},{"┘","┴"}}},
     {{{"╷","┌"},{"┐","┬"}},{{"│","├"},{"┤","┼"}}} };

typedef struct coordonnees_t {
    int x;
    int y;
} coordonnees_t;

typedef struct unionfind_t {
    coordonnees_t taille;
    coordonnees_t** pere;
    unsigned int** rang;
} unionfind_t;

typedef struct labyrinthe_t {
    coordonnees_t taille;
    int** murs_hori ;
    int** murs_vert ;
} labyrinthe_t;

typedef struct mur_supprimable {/*Améliorations du tirage des murs aléatoires*/
	int taille_hori;
	int taille_vert;
	int* murs_hori;
	int* murs_vert;
} mur_supprimable;

unionfind_t* alloueCases(int hauteur,int largeur){
    int i;
    unionfind_t* cases = (unionfind_t*) malloc(sizeof(unionfind_t));

    if (cases != NULL)
    {
        /*TAILLE*/
        cases->taille.x = hauteur;
        cases->taille.y = largeur;

        /*TABLEAUX DES PERES*/
        cases->pere = (coordonnees_t**) malloc(hauteur * sizeof(coordonnees_t *));
        for (i=0; i<hauteur; i++) 
            cases->pere[i] = (coordonnees_t *) malloc(largeur * sizeof(coordonnees_t)); 

        /*TABLEAUX DES RANGS*/
        cases->rang = (unsigned int**) malloc(hauteur * sizeof(unsigned int*));
        for (i=0; i<hauteur; i++) 
            cases->rang[i] = (unsigned int *) malloc(largeur * sizeof(unsigned int)); 
    }
    return cases;
}

labyrinthe_t* alloueMur(int hauteur,int largeur)
{
    int i;
    
    labyrinthe_t* cases = (labyrinthe_t*) malloc(sizeof(labyrinthe_t));

    if (cases != NULL)
    {
        /*TAILLE*/
        cases->taille.x = hauteur;
        cases->taille.y = largeur;

        /*TABLEAUX DES MURS HORIZONTAUX*/
        cases->murs_hori = (int**) malloc(hauteur * sizeof(int*));
        for (i=0; i<hauteur; i++) 
            cases->murs_hori[i] = (int *) malloc(largeur * sizeof(int)); 

        /*TABLEAUX DES MURS VERTICAUX*/
        cases->murs_vert = (int**) malloc(hauteur * sizeof(int*));
        for (i=0; i<hauteur; i++) 
            cases->murs_vert[i] = (int *) malloc(largeur * sizeof(int)); 
    }
    return cases;
}
mur_supprimable* alloueMurSupprimable(int hauteur,int largeur) 
{
    mur_supprimable* cases = (mur_supprimable*) malloc(sizeof(mur_supprimable));

    if (cases != NULL)
    {
    	cases->taille_hori=((hauteur-1)*largeur)*2;
    	cases->taille_vert=(hauteur*(largeur-1))*2;

        /*TABLEAUX DES MURS HORIZONTAUX*/
        cases->murs_hori = (int*) malloc(cases->taille_hori* sizeof(int));

        /*TABLEAUX DES MURS VERTICAUX*/
        cases->murs_vert = (int*) malloc(cases->taille_vert * sizeof(int));
         
    }
    return cases;
}
void Initialisation_cases(unionfind_t * lab)
{
    /*INITIALISATION*/
    /*CHAQUE CASE EST SON PROPRE PERE*/
    int i, j;
    for (i = 0; i < lab->taille.x; i++)
    {
        for (j = 0; j < lab->taille.y; j++)
        { 
            lab->pere[i][j].x=i; 
            lab->pere[i][j].y=j;  
            lab->rang[i][j]=1;    
        }
    }    
}

void Initialisation_murs(labyrinthe_t * murs)
{
    /*INITIALISATION*/
    /*CHAQUE CASE A 2 MURS SAUF LA SORTIE ET LES BORDS*/
    int i, j;

    for (i = 0; i < murs->taille.x; i++)
    {
        for (j = 0; j < murs->taille.y; j++)
        { 
            if(i != (murs->taille.x -1))
            {
                murs->murs_hori[i][j]=1;  
            }

            if(j != (murs->taille.y -1))
            {
                murs->murs_vert[i][j]=1;  
            }       
        }
    } 
}
void init_tableau_mur_supprimable(labyrinthe_t murs, mur_supprimable* wall){
	int i,j,compteur_hori,compteur_vert;
	compteur_hori=0;
	compteur_vert=0;
	/*INITIALISATION*/
    /*CHAQUE COORDONNEE DES CASES SAUF LA SORTIE ET LES BORD SONT DANS LES TABLEAUX*/
	
	for(i=0; i<murs.taille.x; i++)
	{
		for(j=0 ; j<murs.taille.y; j++)
		{

			if(murs.murs_hori[i][j]==1)   
			{          
                wall->murs_hori[compteur_hori] = i;
                wall->murs_hori[compteur_hori+1] = j;    
                compteur_hori+=2; 
			}
			
            if(murs.murs_vert[i][j]==1) 
            {             
                wall->murs_vert[compteur_vert] = i;
                wall->murs_vert[compteur_vert+1] = j;  
                compteur_vert+=2;  
            }   
                   	
		}
	}
}
void dessine_labyrinthe_mlv(labyrinthe_t mur) 
{
    int i, j;
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_line(0, CELL_SIZE,0,(mur.taille.x) * CELL_SIZE,MLV_COLOR_WHITE);/*gauche*/
    MLV_draw_line(0, 0, (mur.taille.y) * CELL_SIZE,0,MLV_COLOR_WHITE);/*haut*/
    MLV_draw_line(0, (mur.taille.x) * CELL_SIZE-1, (mur.taille.y) * CELL_SIZE,(mur.taille.x) * CELL_SIZE-1,MLV_COLOR_WHITE);/*bas*/
    MLV_draw_line((mur.taille.y) * CELL_SIZE-1, 0, (mur.taille.y) * CELL_SIZE-1,(mur.taille.x -1) * CELL_SIZE,MLV_COLOR_WHITE);/*droite*/

    for (i = 0; i < mur.taille.x; i++)
    {
        for (j = 0; j < mur.taille.y; j++) 
        {    
            if(mur.murs_hori[i][j]==1)
            {
            	if(j != (mur.taille.y -1))
            	{
                	MLV_draw_line(j * CELL_SIZE, (i+1) * CELL_SIZE,(j+1) * CELL_SIZE,(i+1) * CELL_SIZE,MLV_COLOR_WHITE);
            	}
            	else
            	{
            		MLV_draw_line(j * CELL_SIZE, (i+1) * CELL_SIZE,(j+1) * CELL_SIZE-1,(i+1) * CELL_SIZE,MLV_COLOR_WHITE);
            	}
            }
        
            if(mur.murs_vert[i][j]==1)
            {
            	if(i != (mur.taille.x -1))
            	{
                	MLV_draw_line((j+1) * CELL_SIZE, i * CELL_SIZE,(j+1) * CELL_SIZE,(i+1) * CELL_SIZE,MLV_COLOR_WHITE);
            	}
            	else
            	{
      	        	MLV_draw_line((j+1) * CELL_SIZE, i * CELL_SIZE,(j+1) * CELL_SIZE,(i+1) * CELL_SIZE-1,MLV_COLOR_WHITE);

            	}
            }
        }
    } 

    MLV_update_window();
}
void dessine_labyrinthe_ascii(labyrinthe_t mur) 
{
    int i, j;

    printf("%s",intersections[0][0][0][1]) ; 
   	for (i = 0; i < mur.taille.y; i++) /*LA LIGNE TOUT EN HAUT*/
    { 	
    	if(i==mur.taille.y-1)
    		printf("%s%s",intersections[0][0][1][1],intersections[1][0][1][0]);
    	else    	
    		printf("%s%s",intersections[0][0][1][1],intersections[mur.murs_vert[0][i]][0][1][1]);
    } 
    printf("\n");
    
    for (i = 0; i < mur.taille.x; i++)
    {
    	/*les murs de devant sans l'entree*/
    	if(i==mur.taille.x-1)
    		printf("%s",intersections[0][1][0][1]) ; 
    	else if(i!=0)
    		printf("%s",intersections[1][1][0][mur.murs_hori[i][0]]) ;                           
    	else
    		printf("%s",intersections[1][0][0][mur.murs_hori[i][0]]) ;                           

        for (j = 0; j < mur.taille.y; j++) /*les cases*/
        {    
        	if(j == mur.taille.y-1 && i == mur.taille.x-1)
        		printf("%s%s",intersections[0][0][1][1],intersections[0][0][1][1]) ;          	
	
        	else if(j == mur.taille.y-1)
        	{
        		if(i == mur.taille.x-2)
        			printf("%s%s",intersections[0][0][mur.murs_hori[i][j]][mur.murs_hori[i][j]],intersections[0][1][mur.murs_hori[i][j]][0]) ;  
        		else
        			printf("%s%s",intersections[0][0][mur.murs_hori[i][j]][mur.murs_hori[i][j]],intersections[1][1][mur.murs_hori[i][j]][0]) ;  
        	}

        	else if(i == mur.taille.x-1)
        		printf("%s%s",intersections[0][0][1][1],intersections[0][mur.murs_vert[i][j]][1][1]) ; 

        	else
          		printf("%s%s",intersections[0][0][mur.murs_hori[i][j]][mur.murs_hori[i][j]],intersections[mur.murs_vert[i+1][j]][mur.murs_vert[i][j]][mur.murs_hori[i][j]][mur.murs_hori[i][j+1]]) ;                           
        	
        }
        printf("\n"); 
    } 
     
}

coordonnees_t TrouveCompresse(unionfind_t lab, int i, int j)
{

    /*TROUVE PAR COMPRESSION LE PERE DUNE CASE ET RENVOIE LA STRUCTURE CONTENANT LES COORDONNES */
    if((lab.pere[i][j].x != i) || (lab.pere[i][j].y != j)){
        lab.pere[i][j] = TrouveCompresse(lab, lab.pere[i][j].x,lab.pere[i][j].y);  
    }
    return lab.pere[i][j]; 
}

void FusionRang(unionfind_t * lab, int x1,int y1,int x2,int y2)
{
    /*FUSION PAR RANG*/
 
    coordonnees_t pere_1 = TrouveCompresse(*lab, x1, y1); 
    coordonnees_t pere_2 = TrouveCompresse(*lab, x2, y2); 
    if((pere_1.x == pere_2.x)&&(pere_1.y == pere_2.y))
    	return;
    
    if (lab->rang[pere_1.x][pere_1.y] < lab->rang[pere_2.x][pere_2.y]) 
    {
        lab->pere[pere_1.x][pere_1.y].x = pere_2.x; 
        lab->pere[pere_1.x][pere_1.y].y = pere_2.y; 
    }
    else if (lab->rang[pere_1.x][pere_1.y] > lab->rang[pere_2.x][pere_2.y]) 
    {
        lab->pere[pere_2.x][pere_2.y].x = pere_1.x; 
        lab->pere[pere_2.x][pere_2.y].y = pere_1.y;
    }
    else
    { 
        lab->pere[pere_2.x][pere_2.y].x = pere_1.x; 
        lab->pere[pere_2.x][pere_2.y].y = pere_1.y;
        lab->rang[pere_1.x][pere_1.y]++; 
    } 
}

int check_meme_classe(unionfind_t lab,int x1,int y1,int x2,int y2)
{
    /*REGARDE SI DEUX STRUCTURE DE COORDONNEE FONT PARTIE DE LA MEME CLASSE ET RENVOIE 1, SI OUI*/
    coordonnees_t coord_1=TrouveCompresse(lab,x1,y1);
    coordonnees_t coord_2=TrouveCompresse(lab,x2,y2);
    
    if(coord_1.x == coord_2.x)
    {
        if(coord_1.y == coord_2.y)
            return 1;
    }
    return 0;
}

void enlever_mur_supprimable(mur_supprimable* wall,int pos,char* side)
{
	int i;
	/*RETIRE L'ELEMENT A L'INDICE "pos" DU TABLEAU "side" CORRESPONDANT */
	if(strcmp(side, "hori")==0)/*hori*/
	{
		for(i=pos; i < (wall->taille_hori-1); i++)
        {
            wall->murs_hori[i] = wall->murs_hori[i + 1];
        }
        wall->taille_hori-=1;
	}
	if(strcmp(side, "vert")==0)
	{
		for(i=pos; i < (wall->taille_vert-1); i++)
        {
            wall->murs_vert[i] = wall->murs_vert[i + 1];
        }
        wall->taille_vert-=1;
	}
}

int supprime_mur(unionfind_t * lab , labyrinthe_t * murs, int unique, mur_supprimable* wall)
{
    /*SUPPRIME UN MUR EXISTANT ON TIRE UNE PIECE ENTRE 0 ET 1 (0 HORIZONTAL ET 1 VERTICAL) */
    int i,j,side,random_hori,random_vert;   
    nbr_classe--;
    while(1)
    {  
	    side=rand() %2;

    	if(side==0)/*0 = HORIZONTAL*/
	    {
	    	if(wall->taille_hori !=0)/*SIL RESTE DES MURS HORIZONTAUX A SUPPRIMER SINON ON VA VOIR LES VERTICAUX*/
	    	{	    		
    			random_hori=rand() % wall->taille_hori;
    			
		    	if((random_hori %2) == 0)/*SI NOMBRE ALEATOIRE EST PAIRE*/
		    	{

		    		i=wall->murs_hori[random_hori];
		    		j=wall->murs_hori[random_hori+1];
		    		if(unique==1)/*SI OPTION UNIQUE*/
		    		{
		    			if(check_meme_classe(*lab,i,j,i+1,j) == 1)
		    				continue;
		    		}
		    		enlever_mur_supprimable(wall,random_hori+1,"hori");
		    		enlever_mur_supprimable(wall,random_hori,"hori");            	
		    	}
		    	else
		    	{
		    		i=wall->murs_hori[random_hori-1];
		    		j=wall->murs_hori[random_hori];
		    		if(unique==1)
		    		{
		    			if(check_meme_classe(*lab,i,j,i+1,j) ==1)
		    				continue;
		    		}
		    		enlever_mur_supprimable(wall,random_hori,"hori");
		    		enlever_mur_supprimable(wall,random_hori-1,"hori");
		        	
		    	}            	
		    	
		        murs->murs_hori[i][j]=0;      /*MUR A 0*/          
		        FusionRang(lab,i,j,i+1,j); /*FUSIONNE LES DEUX CASES*/
		        return 1;
		    }
		    else
		    	side=1;	        
	    }

	    if(side==1)/*VERTICAL*/
	    {
	    	if(wall->taille_vert !=0)
	    	{
    			random_vert=rand() % wall->taille_vert;
	    		  
		        if((random_vert %2) == 0)
		    	{
		    		i=wall->murs_vert[random_vert];
		    		j=wall->murs_vert[random_vert+1];
		    		if(unique==1)
		    		{
		    			if(check_meme_classe(*lab,i,j,i,j+1) ==1)
		    				continue;
		    		}
		    		enlever_mur_supprimable(wall,random_vert+1,"vert");
		    		enlever_mur_supprimable(wall,random_vert,"vert");            	
		    	}
		    	else
		    	{
		    		i=wall->murs_vert[random_vert-1];
		    		j=wall->murs_vert[random_vert];
		    		if(unique==1)
			    	{
			    		if(check_meme_classe(*lab,i,j,i,j+1) ==1)
			    			continue;
			    	}
		    		enlever_mur_supprimable(wall,random_vert,"vert");
		    		enlever_mur_supprimable(wall,random_vert-1,"vert");
		        	
		    	}   
		        murs->murs_vert[i][j]=0;              
		        FusionRang(lab,i,j,i,j+1);
		        return 1;
		    }
		    else
		    	side=0;
		}
    }
    
	return 0;
}

int main(int argc, char *argv[])
{     
	/*VALEUR PAR DEFAUT DES ARGUMENTS*/
    int i,attente,graine,unique,acces,texte;
    int taille_fenetre=1000;
    H=6;
	L=8;
	CELL_SIZE=(taille_fenetre/8);
	srand(time(NULL));
	attente=-1;
	unique=0;
	texte=0;
	acces=0;

	/*GESTION DES ARGUMENTS*/
    for ( i = 0; i < argc; i++) 
    {
    	if (sscanf(argv[i], "--taille=%dx%d", &H, &L) == 2)
    	{
    		if(H<=400 && L<=300)
    		{
	    		if(H>L)
	     			CELL_SIZE=(taille_fenetre/H);
	     		else
     				CELL_SIZE=(taille_fenetre/L);	
     		}
     		else
     		{
     			printf("TAILLE TROP GRANDE\n");
     			exit(1);
     		}   		
		}

     	if(sscanf(argv[i], "--graine=%d", &graine) == 1)
     		srand(graine); 
     	
     	if(sscanf(argv[i], "--attente=%d", &attente) == 1)
     	{
     		if(attente<0){
     		 	printf("valeur attente négatif\n");
     		 	exit(1);
     		}
     	}

     	if(strcmp(argv[i], "--unique") == 0)
     		unique=1;  	
     	if(strcmp(argv[i], "--mode=texte") == 0)
     		texte=1;  	
     	if(strcmp(argv[i], "--acces") == 0)
     		acces=1;  
	}

	/* ALLOUE MEMOIRE*/
    unionfind_t* lab=alloueCases(H,L);
    labyrinthe_t* murs=alloueMur(H,L);
    mur_supprimable* wall= alloueMurSupprimable(H,L);
    char* touche=(char *) malloc(400*sizeof(char));/*utiliser pour lentree au clavier entre chaque suppresion de mur*/

  	/*DEBUT DU PROGRAMME*/
    int entree_x,entree_y,sortie_x,sortie_y;
    nbr_classe=H*L; /*IL Y A AUTANT DE CASES QUE DE CLASSE*/
    entree_x=0;
    entree_y=0;
    sortie_x=(lab->taille.x)-1;
    sortie_y=(lab->taille.y)-1;

    if(texte != 1)/*FENETRE GRAPHIQUE SI MODE TEXTE DESACTIVE*/
	    MLV_create_window("Labyrinthe Graphique", "", taille_fenetre, taille_fenetre);

    /*INITIALISATION*/
    Initialisation_cases(lab); /*les cases sont leurs propres peres*/
    Initialisation_murs(murs); /*tous les murs a 1*/
    init_tableau_mur_supprimable(*murs,wall);/*TOUS LES MURS SONT SUPPRIMABLES (EXCEPTION : SORTIE ET BORD)*/

    while(check_meme_classe(*lab, entree_x, entree_y, sortie_x, sortie_y) != 1)/*TANT QUE ENTREE ET SORTIE NE FONT PAS PARTIE DE LA MEME CLASSE*/
    {
    	if(attente !=0 )/*SI ATTENTE ALORS ON AFFICHE*/
        {
            if(texte != 1)/*MLV*/
            {
                dessine_labyrinthe_mlv(*murs);
                if(attente==-1)
                    MLV_wait_keyboard(NULL,NULL,NULL);  
                else
                    MLV_wait_milliseconds(attente);
            }
            else/*TEXTE*/
            {
                dessine_labyrinthe_ascii(*murs);
                fflush(stdout);/*NECESSAIRE A CAUSE DU SLEEP*/
                if(attente==-1)
                	fgets(touche,400,stdin);                
                else
                	sleep(attente/1000);       
            }
        } 
        supprime_mur(lab,murs,unique,wall);    /*supprime un mur existant aleatoirement*/   
    }

    if(acces==1)/*SI --ACCES*/
    {
    	while(nbr_classe != 1)/*TANT QU'IL Y A PLUS D'UNE CLASSE*/
   		{      
			if(attente !=0 )
            {
                if(texte != 1)/*MLV*/
                {
                    dessine_labyrinthe_mlv(*murs);
                    if(attente==-1)
                        MLV_wait_keyboard(NULL,NULL,NULL);  
                    else
                        MLV_wait_milliseconds(attente);
                }
                else/*TEXTE*/
                {
                    dessine_labyrinthe_ascii(*murs);
                    fflush(stdout);
                    if(attente==-1)
                        fgets(touche,400,stdin); 
                    else                  	
                    	sleep(attente/1000);    
                }
            } 
            supprime_mur(lab,murs,unique,wall);    /*supprime un mur existant aleatoirement*/  
    	}
    }

   	/*AFFICHAGE DE FIN*/
	if(texte != 1)
	{
		dessine_labyrinthe_mlv(*murs);
		printf("FINI\n");
		MLV_wait_keyboard(NULL,NULL,NULL);
	}
	else
	{
		dessine_labyrinthe_ascii(*murs);
		printf("FINI\n");
	}

    return 0;
}