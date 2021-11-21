from upemtk import *
from random import randint

##PROJET AP : ISOLA 

def initplateau(n): #Créer le plateau en n*n , 'n' choisis par l'utilisateur
    res = []
    for i in range(n):
        res.append([0]*n)
    return res
    
def draw_theme(n,taille_case,theme):
    if theme == 'noel':
        image(taille_case*n/2, taille_case*n/2,'img/theme_noel_jeu.png')
    if theme == 'foret':
        image(taille_case*n/2, taille_case*n/2,'img/theme_foret_jeu.png')
    if theme == 'eau':
        image(taille_case*n/2, taille_case*n/2,'img/theme_eau_jeu.png')
                    
def theme_pion1(x,y,taille_case,theme):
    if theme == 'noel':
        image(x+ taille_case/2, y+taille_case/2,'img/santa.png',tag='pion1')
    if theme == 'foret':
        image(x+ taille_case/2, y+taille_case/2,'img/feuille.png',tag='pion1')
    if theme == 'eau':
        image(x+ taille_case/2, y+taille_case/2,'img/poisson.png',tag='pion1')
    elif theme==0:
        cercle(x+ taille_case/2, y+taille_case/2,(taille_case*(3.5/10)),couleur='black',remplissage='black',tag='pion1')   
        
def theme_pion2(x,y,taille_case,theme):
    if theme == 'noel':
        image(x+ taille_case/2, y+taille_case/2,'img/renne.png',tag='pion2')
    if theme == 'foret':
        image(x+ taille_case/2, y+taille_case/2,'img/bois.png',tag='pion2')
    if theme == 'eau':
        image(x+ taille_case/2, y+taille_case/2,'img/poulpe.png',tag='pion2')
    elif theme==0:
        cercle(x+ taille_case/2, y+taille_case/2,(taille_case*(3.5/10)),couleur='blue',remplissage='blue',tag='pion2')
    
def theme_interdit(x,y,taille_case,theme):
    if theme == 'noel':
        image(x+ taille_case/2, y+taille_case/2,'img/boule.png',tag='interdit')
    if theme == 'foret':
        image(x+ taille_case/2, y+taille_case/2,'img/feu.png',tag='interdit')
    if theme == 'eau':
        image(x+ taille_case/2, y+taille_case/2,'img/requin.png',tag='interdit')
    elif theme==0:
        cercle(x+ taille_case/2, y+taille_case/2,(taille_case*(3.5/10)),remplissage='red',tag='interdit') 
            
def dessine_plateau(plateau,a,b,u,d,theme):
    n = len(plateau)
    draw_theme(n,taille_case,theme)
    for i in range(n):
        for j in range(n):
            x, y = j * taille_case, i * taille_case
            if theme ==0:
                rectangle(x,y,x+taille_case,y+taille_case,couleur='black',remplissage='white')
            else :
                rectangle(x,y,x+taille_case,y+taille_case,couleur='black')
                
            if plateau[i][j] == 1 : #pion 1
                if n <=6:
                    theme_pion1(x,y,taille_case,theme)
                if n>6:
                   cercle(x+ taille_case/2, y+taille_case/2,(taille_case*(3.5/10)),couleur='black',remplissage='black',tag='pion1')  
                   
            if plateau[i][j] == 2 :#pion 2
                if n <=6:
                    theme_pion2(x,y,taille_case,theme)
                if n>6:
                   cercle(x+ taille_case/2, y+taille_case/2,(taille_case*(3.5/10)),couleur='blue',remplissage='blue',tag='pion2')
                           
            if plateau[i][j]==3 : #interdit (case bloqué)
                if n <=6:
                    theme_interdit(x,y,taille_case,theme)
                if n>6:
                   cercle(x+ taille_case/2, y+taille_case/2,(taille_case*(3.5/10)),remplissage='red',tag='interdit')  

                   
def pixel_vers_case(x,y, taille_case) :
    return int(y // taille_case), int(x // taille_case)
    
def positionpion1 (plateau, i, j):
    plateau[i][j]= 1 
    
def positionpion2 (plateau, i, j):
    plateau[i][j]= 2
    
def positioninterdit(plateau,i,j):
    plateau[i][j]=3 

def annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer):
    if back ==1:
        return retour_pion1(l,l2,l_int_1,l_int_2,plateau) or retour_pion2(l,l2,l_int_1,l_int_2,plateau)
   
    if len(l) == 0 or ((a,b) != l[len(l)-1]):
        l.append((a,b))#pion1
    if len(l2) == 0 or (u,d) != l2[len(l2)-1]  :  
        l2.append((u,d))#pion2
    if interdit == 1 :
        if jouer == 7 or ordi==1 :
            if  len(l_int_1) == 0 or (i == ligne_interdit1 and (i,j) != l_int_1[len(l_int_1)-1]):
                l_int_1.append((i,j))#interdit pion1
        if jouer == 6:
            if  len(l_int_2)==0 or (i == ligne_interdit2 and (i,j) != l_int_2[len(l_int_2)-1]):
                l_int_2.append((i,j))#interdit pion2
    
        
def retour_pion1(l,l2,l_int_1,l_int_2,plateau):
    if len(l_int_1) == len(l_int_2) and len(l) > len(l2):#retour en arriere pion1
        x,y=l[len(l)-1]
        plateau[x][y]=0
        l.pop()
        x,y=l[len(l)-1]
        plateau[x][y]=1
        return x,y
        
    if len(l_int_1) > len(l_int_2) and len(l) == len(l2):#retour en arriere pion2
        x,y=l2[len(l2)-1]
        plateau[x][y]=0
        l2.pop()
        x,y=l2[len(l2)-1]
        plateau[x][y]=2
        return x,y
 
def retour_pion2(l,l2,l_int_1,l_int_2,plateau):
    if len(l_int_1) !=0 and len(l_int_1) > len(l_int_2) and len(l) > len(l2):#retour en arriere interdit pion1
        x,y=l_int_1[len(l_int_1)-1]
        plateau[x][y]=0
        l_int_1.pop()
        return x,y
        
    if len(l_int_2) !=0 and len(l_int_1) == len(l_int_2) and len(l) == len(l2):#retour en arriere interdit pion2
        x,y=l_int_2[len(l_int_2)-1]
        plateau[x][y]=0
        l_int_2.pop()
        return x,y
                   
def casesdispo(plateau,a,b,u,d,i,j,jouer):
    if jouer == 6 :
        casesdispo_pion1(plateau,a,b,u,d,i,j)
        
    if jouer == 7 :
        casesdispo_pion2(plateau,a,b,u,d,i,j)
                    
def casesdispo_pion1(plateau,a,b,u,d,i,j):
    for x in range(-1,2): #pion1
        for y in range(-1,2):
            if (a == 0 and x == 1) or (b == 0 and y == 1) or (a == n-1 and x == -1) or (b == n-1 and y == -1) :#cas particulier pion 1 
                continue
            if plateau[a-x][b-y]== 0:# chaque case vide autour du pion1 devienne jaune
                k,o = (b-y) * taille_case , (a-x) * taille_case
                rectangle(k,o,k+taille_case,o+taille_case,couleur='black',remplissage='gold')
  
def casesdispo_pion2(plateau,a,b,u,d,i,j):
    for x in range(-1,2):#pion2
        for y in range(-1,2):
            if (u == 0 and x == 1) or (d == 0 and y == 1) or (u == n-1 and x == -1) or (d == n-1 and y == -1) :#cas particulier pion 2
                continue
            if plateau[u-x][d-y] == 0:# chaque case vide autour du pion2 devienne verte
                k,o = (d-y) * taille_case , (u-x) * taille_case
                rectangle(k,o,k+taille_case,o+taille_case,couleur='black',remplissage='green')
    
def condition_mort(plateau,a,b,u,d):
    return mort_pion1(plateau,a,b) or mort_pion2(plateau,u,d)

def mort_pion1(plateau,a,b):
    compteur1 = 0
    for x in range(-1,2):           #pion1
        for y in range(-1,2):
            if is_on_borders(a,b,x,y)  :#cas particulier pion 1 
                continue
            if plateau[a-x][b-y] != 0:
                compteur1 +=1
            if (is_in_corners(a,b,x,y) and compteur1 == 4) or (is_in_corners(a,b,x,y) and compteur1 == 6) or (compteur1 ==9) :#cas particulier pion 1 dans les coins
                if ordi ==0:
                    texte(65,640,"Joueur 2 vous avez gagné",couleur='black',taille='18',police='Calibri italic')
                    return True
                texte(65,640,"L'ordinateur à gagné",couleur='black',taille='18',police='Calibri italic')
                return True
                
def is_on_borders(a,b,x,y):
    return (a == 0 and x == 1) or (b == 0 and y == 1) or (a == n-1 and x ==-1) or (b == n-1 and y ==-1)  :#cas particulier bord
    
def is_in_corners(a,b,x,y):
    return ((a == 0 and b == 0) or (a == n-1 and b == n-1)  or (a == 0 and b == n-1) or (a == n-1 and b == 0)) or (a == 0 or a == n-1 or b == 0 or b == n-1)
    
def mort_pion2(plateau,u,d):
    compteur2 = 0
    for x in range(-1,2):           #pion2
        for y in range(-1,2):
            if is_on_borders(u,d,x,y)  :#cas particulier pion 2
                continue
            if plateau[u-x][d-y] != 0:#nombre de cases vide trouver
                compteur2 +=1
            if (is_in_corners(u,d,x,y) and compteur2 == 4) or (is_in_corners(u,d,x,y) and compteur2 == 6) or (compteur2 == 9) :#cas particulier pion 2  
                texte(65,640,"Joueur 1 vous avez gagné",couleur='black',taille='18',police='Calibri italic')
                return True
                
def placer_ordi_pion(plateau) :
    x = randint(0,n-1)
    y = randint(0,n-1)
    while plateau[x][y] != 0 :
        x = randint(0,n-1)
        y = randint(0,n-1)
    plateau[x][y] = 2
    return x,y     
    
def placer_ordi_interdit (plateau) :
    t = randint(0,n-1)
    s = randint(0,n-1)
    while plateau[t][s] !=0:
        t = randint(0,n-1)
        s = randint(0,n-1)
    plateau[t][s] = 3
    l_int_2.append((t,s))
    return t,s
    
def deplacer_ordi(plateau,u,d):
    x = randint(0,n-1)
    y = randint(0,n-1)
    while (x > u+1 or x < u-1) or (y > d+1 or y < d-1) or plateau[x][y] != 0 or (x==u and y == d):
        x = randint(0,n-1)
        y = randint(0,n-1)
    plateau[x][y]= 2 
    l2.append((x,y))
    return x,y 
    
##Programme principale 

n = int(input('entrez le nombre de cases pour le tableau ( ex: 6 pour 6x6 cases) : '))
plateau = initplateau(n)
taille_case = 600/n # taille d'une case du plateau
jouer,regle,interdit,custom,theme,back,ordi,choix = 0,0,0,0,0,0,0,0 # Initialisation des variables
l,l2,l_int_1,l_int_2=[],[],[],[] #Initialisation des listes de sauvegardes des coups
colonne_interdit2=0
colonne_interdit1=0
if __name__ == '__main__':
    cree_fenetre(600,700)
    while True: 
        mise_a_jour()
        ev = donne_ev()
        ty = type_ev(ev)
        if ty == 'Quitte':
            ferme_fenetre()
            break
        elif ty == 'ClicGauche':
            x,y = abscisse(ev), ordonnee(ev)
            i, j = pixel_vers_case(x,y,taille_case)
            if 200 < x < 400 and 350 < y < 450 and jouer == 0 and custom ==0 : # clique sur jouer
                choix=1
                jouer = -1
                continue
            if 600/1.45 < x < 600/1.1 and 25 < y < 75 and jouer == 0 : #clique sur règle
                regle = 1
                continue
            if 600/9-28 < x < 600/9+27 and 23 < y < 77 and jouer == 0: # clique sur personnaliser
                custom = 1
                continue
            if choix == 1 and 200 < x < 500 and 450 < y < 550 : # choix de 2 joueurs 
                ordi=0
                jouer = 1
                choix = 0
                efface_tout()
                continue
            if choix == 1 and 100 < x < 400 and 300 < y < 400 : # choix de 1 joueur
                ordi=1
                jouer = 1
                choix = 0
                efface_tout()
                continue
            if  25 < x < 195 and 325 < y < 425 and custom==1:  # clique sur noel          
                theme,custom,jouer='noel',0,0
                continue
            if  215 < x < 385 and 325 < y < 425 and custom==1: # clique sur foret 
                theme,custom,jouer='foret',0,0
                continue 
            if  405 < x < 575 and 325 < y < 425 and custom==1: # clique sur eau        
                theme,custom,jouer='eau',0,0
                continue 
            if  235 < x < 365 and 505 < y < 600 and (custom==1 or regle == 1 ): #clique sur retour dans le menu personnaliser ou du menu des règles
                regle,custom,jouer=0,0,0
                continue    
                
            if (-1<i<n and -1<j<n) and ordi ==0:# on s'assure que l'on clique bien sur une case
                
                if jouer == 1 :
                    efface_tout()
                    jouer = 2
                    i, j = pixel_vers_case(x,y,taille_case)
                    a, b = i, j
                    continue
                if jouer == 2 : #placer pion1
                    efface_tout()
                    jouer = 3
                    i, j = pixel_vers_case(x,y,taille_case)
                    positionpion1(plateau, i, j)
                    a, b = i, j #position pion 1 actuelle
                    continue
                if jouer == 3 :
                    efface_tout()
                    jouer = 4
                    i, j = pixel_vers_case(x,y,taille_case)
                    u, d = i, j
                    continue
                if jouer == 4 and plateau[i][j]==0:#placer pion2
                    efface_tout()
                    jouer = 5
                    i, j = pixel_vers_case(x,y,taille_case)
                    positionpion2(plateau, i, j)
                    u, d = i, j #position pion 2 actuelle 
                    annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)
                    continue
                if jouer == 5 :#clique sur bonne chance
                    efface_tout()
                    jouer = 6
                    continue
            if ordi ==1:# on s'assure que l'on clique bien sur une case
                if (-1<i<n and -1<j<n) :
                    if jouer == 1 :
                        efface_tout()
                        jouer = 2
                        i, j = pixel_vers_case(x,y,taille_case)
                        a, b = i, j
                        continue
                    if jouer == 2 : #placer pion1
                        efface_tout()
                        jouer = 4
                        i, j = pixel_vers_case(x,y,taille_case)
                        positionpion1(plateau, i, j)
                        a, b = i, j #position pion 1 actuelle
                        
                if jouer == 4 :#placer pion2
                   
                    efface_tout()
                    u,d = placer_ordi_pion(plateau)
                    annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)
                    jouer = 5
                    continue
                if jouer == 5 :#clique sur bonne chance
                    efface_tout()
                    jouer = 6
            if back ==0 and 537<x<585 and 625<y<670 and jouer !=0 : # clique sur fleche annuler coup
            
                back=1
                
                if jouer ==1 and back ==1:
                    jouer,back=0,0
                    
                if jouer ==2 and back ==1:
                    jouer,back=0,0
                    
                if jouer ==3 and back ==1:
                    l,jouer,back=[],1,0
                    
                if jouer ==4 and back ==1:
                    l,jouer,back=[],1,0
                    
                if jouer==5 and back==1:
                    plateau[u][d],l2,jouer,back=0,[],3,0
         
        if choix == 1:
            efface_tout()
            image(600/2,(600+100)/2,'img/accueil.png')
            texte(600/2,160, "Choisissez :", ancrage='center', taille='80',couleur='blanchedalmond', police='Calibri')
            rectangle(100,400,400,300,couleur='white')
            rectangle(200,450,500,550,couleur='white')
            texte(250,350, "1 joueur" , ancrage='center', taille='35',couleur='blanchedalmond', police='Calibri')
            texte(350,500, "2 joueurs" , ancrage='center', taille='35',couleur='blanchedalmond', police='Calibri')
            
             
        if jouer == 0 :# page d'accueil
            efface_tout()
            rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
            image(taille_case*n/2,(taille_case*n+100)/2,'img/accueil.png')
            texte(taille_case*n/2,160, "ISOLA", ancrage='center', taille='100',couleur='blanchedalmond', police='Calibri')
            texte(taille_case*n/2,400, "Jouer" , ancrage='center', taille='35',couleur='red', police='Calibri')
            rectangle(taille_case*n/3,350,taille_case*n/1.5,450,couleur='white')
            image(taille_case*n/9,50,'img/personnaliser.png',tag='perso')
            rectangle(taille_case*n/1.45,25,taille_case*n/1.1,75,couleur='white')
            texte(taille_case*n/1.25,50, "regle" , ancrage='center', taille='25',couleur='white',police='Calibri italic')
             
        if custom ==1: # page personnalisation
            efface_tout()   
            rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
            image(taille_case*n/2,(taille_case*n+100)/2,'img/accueil.png')
            texte(taille_case*n/2,100, "Choississez un thème", ancrage='center', taille='40',couleur='blanchedalmond')
            image(110,350,'img/theme_noel.png',tag='noel')
            image(taille_case*n/2,350,'img/theme_foret.png',tag='foret')
            image(490,350,'img/theme_eau.png',tag='eau')
            image(taille_case*n/2,545,'img/back.png',tag='back')
            
        if regle == 1 :
            efface_tout()
            image(taille_case*n/2,700/2,'img/accueil.png')
            texte(taille_case*n/2,180, "REGLE : \n \n La position initiale des pions est laissée au choix des joueurs.\n Les adversaires jouent à tour de rôle. Jouer consiste à effectuer \n les deux étapes suivantes : \n - deplacer son pion \n - choisir une case à bloqué \n \n BUT : \n \n Bloqué son adversaire a l'aide des cases a blqué \n ou de son propre pions " , ancrage='center', taille='17',couleur='white', police='Calibri')
            ligne(4, 38, 72, 38, couleur='white', epaisseur=3)
            ligne(7, 263, 60, 263, couleur='white', epaisseur=3)
            image(taille_case*n/2,545,'img/back.png',tag='back')
## 2 Joueur           
        if ordi ==0:    
            if jouer == 1 : # placer le premier pion
                efface_tout()
                image(taille_case*n/2,700/2,'img/accueil.png')
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                texte(taille_case*n/2,200, "Placer un pion", ancrage='center', taille='30',couleur='maroon')
                texte(taille_case*n/2,taille_case*n/2, "Appuyer pour commencer ! ", ancrage='center', taille='30',couleur='maroon')
                image(557,655,'img/back_jeu.png') # fleche annuler coup
                
            if jouer == 2 : # 1 pion
                efface_tout()
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                plateau = initplateau(n)
                dessine_plateau(plateau,a,b,taille_case*n,taille_case*n,theme)
                image(557,655,'img/back_jeu.png') # fleche annuler coup
            
            if jouer == 3 : # placer le deuxieme pion
                efface_tout()
                image(taille_case*n/2,700/2,'img/accueil.png')
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                texte(taille_case*n/2,200, "Placer le deuxième pion", ancrage='center', taille='30',couleur='maroon')
                texte(taille_case*n/2,taille_case*n/2, "Appuyer pour continuer ! ", ancrage='center', taille='30',couleur='maroon')
                image(557,655,'img/back_jeu.png') # fleche annuler coup
                
            if jouer == 4 : # 2 pion
                efface_tout()
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                dessine_plateau(plateau,a,b,u,d,theme)
                image(557,655,'img/back_jeu.png') # fleche annuler coup
            
            if jouer == 5 :#Bonne chance
                efface_tout()
                image(taille_case*n/2,700/2,'img/accueil.png')
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                texte(taille_case*n/2,200, "Bonne chance !", ancrage='center', taille='30',couleur='maroon')
                image(557,655,'img/back_jeu.png') # fleche annuler coup
            
            if jouer >= 6:  # PARTIE JOUEUR VS JOUEUR COMMENCE
                efface_tout()
                dessine_plateau(plateau,a,b,u,d,theme)
                while True:
                    efface_tout()
                    dessine_plateau(plateau,a,b,u,d,theme)
                    rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                    image(557,655,'img/back_jeu.png') # fleche annuler coup 
                    
                    if condition_mort(plateau,a,b,u,d):#mort
                        jouer=10
                        rectangle(taille_case*n/2-85,taille_case*n/2-50,taille_case*n/2+85,taille_case*n/2+50,remplissage='white',tag='rst')
                        texte(taille_case*n/2-75,taille_case*n/2-10,"RECOMMENCER ?",couleur='green',taille='15',police='Calibri italic')
                        
                    if jouer ==6 : # texte joueur 1 deplacer pion
                        casesdispo(plateau,a,b,u,d,i,j,jouer)
                        texte(45,640,"Joueur 1 déplacer votre pion sur une des cases vides",couleur='black',taille='18',police='Calibri italic')
                        
                    if jouer==7 :# texte joueur 2 deplacer pion
                        casesdispo(plateau,a,b,u,d,i,j,jouer)
                        texte(45,640,"Joueur 2 déplacer votre pion sur une des cases vides",couleur='black',taille='18',police='Calibri italic') 
                        
                    if jouer ==8:# texte joueur 1 choisir case à bloqué
                        texte(45,640,"Joueur 1 choississez une case vide à bloqué",couleur='black',taille='18',police='Calibri italic')
                        
                    if jouer ==9:# texte joueur 2 choisir case à bloqué
                        texte(45,640,"Joueur 2 choississez une case vide à bloqué",couleur='black',taille='18',police='Calibri italic')
                    
                    mise_a_jour()
                    ev = donne_ev()
                    ty = type_ev(ev)
                    if ty == 'Quitte':
                        ferme_fenetre()
                        break
                    elif ty == 'ClicGauche' and jouer !=10:
                        x,y = abscisse(ev), ordonnee(ev)
                        i, j = pixel_vers_case(x,y,taille_case)
                        if back ==0 and jouer >=6 and jouer !=10 and 537<x<585 and 625<y<670 : # clique sur fleche annuler coup
                            back=1
                            if jouer==8 and len(l_int_1) == len(l_int_2) and len(l) > len(l2)and back ==1:
                                a,b = annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)#pion1 = ancienne position
                                jouer,interdit,back=6,0,0   #joueur 1 replace son pion
                                
                            if jouer==9 and len(l_int_1) > len(l_int_2) and len(l) == len(l2)and back ==1:
                                u,d = annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)#pion2 = ancienne position
                                jouer,interdit,back=7,0,0   #joueur 2 replace son pion
                                
                            if jouer ==7 and len(l_int_1) !=0 and len(l_int_1) > len(l_int_2) and len(l) > len(l2) and back ==1:
                                ligne_interdit1,colonne_interdit1=annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,ligne_interdit1,colonne_interdit1,back,interdit,jouer)#interdit 1 = ancienne position
                                
                                jouer,interdit,back=8,0,0  #joueur 1 doit replacer son interdit
                                
                            if jouer ==6 and len(l_int_2) !=0 and len(l_int_1)==len(l_int_2) and len(l) == len(l2) and back ==1:
                                ligne_interdit2,colonne_interdit2=annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,ligne_interdit2,colonne_interdit2,back,interdit,jouer)#interdit 2 = ancienne position
                                
                                jouer,interdit,back=9,0,0  #joueur 2 doit replacer son interdit
                                
                            if jouer==6 and len(l) == len(l2) and len(l_int_1) == len(l_int_2) and back==1:
                                
                                plateau[u][d],l2,jouer,interdit,back=0,[],3,0,0  #placer position initiale pion2
                                break
                            back=0    
                            
                        if (-1<i<n and -1<j<n): # on s'assure que l'on clique bien sur une case
                        
                            if jouer == 6 and  plateau[i][j]==0 and ((i,j) == (a-1,b-1) or (i,j) == (a-1,b) or (i,j) == (a-1,b+1) or (i,j) == (a,b+1) or (i,j) == (a+1,b+1) or (i,j) == (a+1,b) or (i,j) == (a+1,b-1) or (i,j) == (a,b-1)): # joueur 1 place son pion que sur les cases vides
                                
                                positionpion1(plateau, i, j)#on met un 1 dans la liste de liste plateau
                                plateau[a][b] = 0 # l'ancienne position du pion 1 est vide
                                a, b = i, j #position pion 1 sauvegardé
                                interdit=0
                                annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)
                                jouer = 8  # joueur 1 doit placer son interdit
                            
                            if  jouer == 7 and plateau[i][j]==0 and ((i,j) == (u-1,d-1) or (i,j) == (u-1,d) or (i,j) == (u-1,d+1) or (i,j) == (u,d+1) or (i,j) == (u+1,d+1) or (i,j) == (u+1,d) or (i,j) == (u+1,d-1) or (i,j) == (u,d-1)): # joueur 2 place son pion que sur les cases vides
                            
                                positionpion2(plateau, i, j)#on met un 2 dans la liste de liste plateau
                                plateau[u][d] = 0 # l'ancienne position du pion 2 est vide
                                u, d = i, j #position pion 2 sauvegardé
                                interdit=0
                                annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)
                                jouer = 9  # joueur 2 doit placer son interdit
                                
                    elif ty == 'ClicDroit' and jouer == 8 : # joueur 1 place son interdit
                        x,y = abscisse(ev), ordonnee(ev)
                        i, j = pixel_vers_case(x,y,taille_case)
                        if (-1<i<n and -1<j<n):# on s'assure que l'on clique bien sur une case
                        
                            if plateau[i][j]==0:# on s'assure que la case est vide
                                interdit=1
                                ligne_interdit1,colonne_interdit1=i,j# position interdit 1 sauvegardé
                                positioninterdit(plateau,ligne_interdit1,colonne_interdit1)#on met un 3 dans la liste de liste plateau
                                jouer = 7 # au tour de joueur 2 de joué
                            else :
                                continue
                                
                            annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,ligne_interdit1,colonne_interdit1,back,interdit,jouer)   
                        
                    elif ty == 'ClicDroit' and jouer == 9 : #joueur 2 place son interdit
                        x,y = abscisse(ev), ordonnee(ev)
                        i, j = pixel_vers_case(x,y,taille_case)
                        if (-1<i<n and -1<j<n):# on s'assure que l'on clique bien sur une case
                        
                            if plateau[i][j]==0:# on s'assure que la case est vide
                                interdit=1
                                ligne_interdit2,colonne_interdit2=i,j# position interdit 2 sauvegardé
                                positioninterdit(plateau,ligne_interdit2,colonne_interdit2)#on met un 3 dans la liste de liste plateau
                                jouer = 6 # au tour de joueur 1 de joué
                            else :
                                continue
                                
                            annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,ligne_interdit2,colonne_interdit2,back,interdit,jouer)
                        
                    elif ty == 'ClicGauche' and jouer ==10 : # si clique sur recommencer
                        x = abscisse(ev) 
                        y = ordonnee(ev) 
                        if x > taille_case*n/2-85 and x < taille_case*n/2+85 and y > taille_case*n/2-50 and y < taille_case*n/2+50 :# clique dans le rectangle recommencer
                            jouer,interdit =1,0 # retour au début
                            l,l2,l_int_1,l_int_2=[],[],[],[] # Réinistialisation des listes de sauvegardes des coups
                            break 
                            
                            
                            
                    
## 1 Joueur                              
        if ordi ==1:  # PARTIE JOUEUR VS IA COMMENCE
            if jouer == 1 : # placer le premier pion
                efface_tout()
                image(taille_case*n/2,700/2,'img/accueil.png')
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                texte(taille_case*n/2,200, "Placer un pion", ancrage='center', taille='30',couleur='maroon')
                texte(taille_case*n/2,taille_case*n/2, "Appuyer pour commencer ! ", ancrage='center', taille='30',couleur='maroon')
                image(557,655,'img/back_jeu.png') # fleche annuler coup
                
            if jouer == 2 : # 1 pion
                efface_tout()
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                plateau = initplateau(n)
                dessine_plateau(plateau,a,b,taille_case*n,taille_case*n,theme)
                image(557,655,'img/back_jeu.png') # fleche annuler coup
            
                
            if jouer == 4 : # 2 pion
                efface_tout()
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                dessine_plateau(plateau,a,b,u,d,theme)
                image(557,655,'img/back_jeu.png') # fleche annuler coup
            
            if jouer == 5 :#Bonne chance
                efface_tout()
                image(taille_case*n/2,700/2,'img/accueil.png')
                rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                texte(taille_case*n/2,200, "Bonne chance !", ancrage='center', taille='30',couleur='maroon')
                image(557,655,'img/back_jeu.png') # fleche annuler coup
                
            if jouer >=6:
                    
                efface_tout()
                dessine_plateau(plateau,a,b,u,d,theme)
                while True:
                    efface_tout()
                    dessine_plateau(plateau,a,b,u,d,theme)
                    rectangle(0,taille_case*n,taille_case*n+100,taille_case*n+100,remplissage='whitesmoke',tag='menu') # affichage
                    if jouer ==8:
                        image(557,655,'img/back_jeu.png') # fleche annuler coup 
                    
                    if condition_mort(plateau,a,b,u,d):#mort
                        jouer=10
                        rectangle(taille_case*n/2-85,taille_case*n/2-50,taille_case*n/2+85,taille_case*n/2+50,remplissage='white',tag='rst')
                        texte(taille_case*n/2-75,taille_case*n/2-10,"RECOMMENCER ?",couleur='green',taille='15',police='Calibri italic')
                        
                    if jouer ==6 : # texte joueur 1 deplacer pion
                        casesdispo(plateau,a,b,u,d,i,j,jouer)
                        texte(45,640,"Joueur 1 déplacer votre pion sur une des cases vides",couleur='black',taille='18',police='Calibri italic')
                    
                    if jouer ==8:# texte joueur 1 choisir case à bloqué
                        texte(45,640,"Joueur 1 choississez une case vide à bloqué",couleur='black',taille='18',police='Calibri italic')
                  
                    mise_a_jour()
                    ev = donne_ev()
                    ty = type_ev(ev)
                    if ty == 'Quitte':
                        ferme_fenetre()
                        break
                    elif ty == 'ClicGauche' and jouer !=10:
                        x,y = abscisse(ev), ordonnee(ev)
                        i, j = pixel_vers_case(x,y,taille_case)
                        if back ==0 and jouer >=6 and jouer !=10 and 537<x<585 and 625<y<670 : # clique sur fleche annuler coup
                            back=1
                            if jouer==8 and len(l_int_1) == len(l_int_2) and len(l) > len(l2)and back ==1:
                                a,b = annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)#pion1 = ancienne position
                                jouer,interdit,back=6,0,0   #joueur 1 replace son pion
                                
                            if jouer==6 and len(l) == len(l2) and len(l_int_1) == len(l_int_2) and back==1 and interdit ==0:
                                
                                plateau[u][d],l,l2,jouer,interdit,back=0,[],[],1,0,0  #placer position initiale pion2
                                break
                            back=0    
                            
                        if (-1<i<n and -1<j<n) and jouer ==6: # on s'assure que l'on clique bien sur une case
                        
                            if jouer == 6 and  plateau[i][j]==0 and ((i,j) == (a-1,b-1) or (i,j) == (a-1,b) or (i,j) == (a-1,b+1) or (i,j) == (a,b+1) or (i,j) == (a+1,b+1) or (i,j) == (a+1,b) or (i,j) == (a+1,b-1) or (i,j) == (a,b-1)): # joueur 1 place son pion que sur les cases vides
                                
                                positionpion1(plateau, i, j)#on met un 1 dans la liste de liste plateau
                                plateau[a][b] = 0 # l'ancienne position du pion 1 est vide
                                a, b = i, j #position pion 1 sauvegardé
                                interdit=0
                                annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,i,j,back,interdit,jouer)
                                jouer = 8  # joueur 1 doit placer son interdit
                            
                    
                    elif ty == 'ClicDroit' and jouer == 8 : # joueur 1 place son interdit
                        x,y = abscisse(ev), ordonnee(ev)
                        i, j = pixel_vers_case(x,y,taille_case)
                        if (-1<i<n and -1<j<n):# on s'assure que l'on clique bien sur une case
                            if plateau[i][j]==0:# on s'assure que la case est vide
                                interdit=1
                                ligne_interdit1,colonne_interdit1=i,j# position interdit 1 sauvegardé
                                positioninterdit(plateau,ligne_interdit1,colonne_interdit1)#on met un 3 dans la liste de liste plateau
                            else :
                                continue
                                
                            annuler_coup(l,l2,l_int_1,l_int_2,plateau,a,b,u,d,ligne_interdit1,colonne_interdit1,back,interdit,jouer)    
                            if condition_mort(plateau,a,b,u,d): 
                                jouer=10
                                rectangle(taille_case*n/2-85,taille_case*n/2-50,taille_case*n/2+85,taille_case*n/2+50,remplissage='white',tag='rst')
                                break
                                
                            plateau[u][d] = 0
                            u,d = deplacer_ordi(plateau,u,d)
                            interdit =1
                            ligne_interdit2, colonne_interdit2= placer_ordi_interdit(plateau)
                            jouer = 6
                            
                    elif ty == 'ClicGauche' and jouer ==10 : # si clique sur recommencer
                        x = abscisse(ev) 
                        y = ordonnee(ev) 
                        if x > taille_case*n/2-85 and x < taille_case*n/2+85 and y > taille_case*n/2-50 and y < taille_case*n/2+50 :# clique dans le rectangle recommencer
                            jouer,interdit =1,0 # retour au début
                            l,l2,l_int_1,l_int_2=[],[],[],[] # Réinistialisation des listes de sauvegardes des coups
                            break 