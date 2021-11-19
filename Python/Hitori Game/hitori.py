from upemtk import*
from copy import *
import sys


def lire_grille(nom):
    """Lit le fichier , met chaque ligne dans une liste et ajoute la liste des les lignes dans une liste. """
    while True:
        try:
            fichier = open(nom , 'r')
            break
        except:
            return 'Nom'
            
    grille=[]
    
    for ligne in fichier:
        liste_element=[]
        for element in ligne.split():
            try:
                int(element)
            except:
                return 'Lettre'
            liste_element.append(element)
        grille.append(liste_element)
    if len(grille)!=len(grille[0])  :
        return 'Rect'  
    afficher_grille(grille)
    return grille
    
    fichier.close()
    
def afficher_grille(grille):
    """Affiche la grille"""
    for x in grille:
        print(x)
    
def dessine_plateau(grille):
    """Dessine une grille , colore en noir les cases qui sont dans l'ensemble noircies et en jaune celles qui sont dans l'ensemble case_indice """
    n = len(grille)
    a=-1
    b=-1
    for i in grille:
        a+=1
        for j in i:
            b+=1
            x, y = b * taille_case,a * taille_case
            
            
            rectangle(x,y,x+taille_case,y+taille_case,couleur='black',remplissage='white')
            texte(x+ taille_case/2, y+taille_case/2,j,couleur='black',ancrage="center",taille=int(24*6/n))
                   
            if (a,b) in noircies:
                rectangle(x,y,x+taille_case,y+taille_case,couleur='black',remplissage='black')
            if (a,b) in case_indice:
                rectangle(x,y,x+taille_case,y+taille_case,couleur='black',remplissage='yellow')
        b=-1   

def noircir_case(x,y):
    """Ajoute la case à l'ensemble noircies et à l'ensemble deja_noircies(copie de noircies)
    et ajoute la case dans une liste cases_noircies, sauvegarde de noircies avec un décalage de 1     coup(pour la fonction annuler_coup)"""
    noircies.add((x,y))
    deja_noircies.add((x,y))
    if len(noircies) >=1:
        case_noircies.append((x,y))
    
def rendre_visible(x,y):
    """Enleve la case de l'ensemble noircies et de l'ensemble deja_noircies(copie de noircies)
    et ajoute la case dans la liste cases_noircies."""
    noircies.remove((x,y))
    deja_noircies.remove((x,y))
    case_noircies.append((x,y))
    
def annuler_coup():
    """Enlève la dernière case de la liste case_noircies(dernière case noircie) et réinitialise l'ensemble case_indice.
    Renvoie l'ensemble case_noircies."""
    case_noircies.pop(-1)
    return set(case_noircies)
    
    
def pixel_vers_case(x,y, taille_case) :
    """Transforme les abscisses / ordonnees en colonne / ligne."""
    return int(y // taille_case), int(x // taille_case)

def sans_conflit(grille, noircies): #regle 1
    """Compare chaque case avec toute celle qui sont sur la meme ligne et la meme colonne.
    Renvoie False si il y a deux cases identiques sur la meme ligne ou colnne.
    Renvoie True sinon."""
    for i in range(len(grille)):
        for n in range(len(grille)):
            for x in range(len(grille)):
              
                if n==x:#pas deux fois la meme case
                    continue
                    
                if grille[i][n]==grille[i][x] and (((i,n) not in noircies) and ((i,x) not in noircies)):#ligne
                    return False
                    
                elif grille[n][i]==grille[x][i] and (((n,i) not in noircies) and ((x,i) not in noircies)):#colonne
                    
                    return False    

    return True
    
def sans_voisines_noircies(grille, noircies): #regle 2
    """Regarde si deux cases cote à cote(adjacentes) sont dans l'ensemble noircies.
    Renvoie False si il existe deux cases noircies cote a cote
    Renvoie True sinon."""
    if noircies != set():
        for coordonne in noircies:
            for x in range(-1,2):
                for y in range(-1,2):
                    a,b=coordonne
                    if (a == 0 and x == 1) or (b == 0 and y == 1) or (a == len(grille)-1 and x == -1) or (b == len(grille)-1 and y == -1)  :#cas particulier 
                        continue
                    if (a-x,b) in noircies and (x!=0):#haut/ bas
                        return False
                     
                    elif (a,b-y) in noircies and (y!=0):# gauche/ droite
                        return False
                      
    return True
    
    
def detecter_piece(grille, noircies,ligne,colonne, piece):
    """Ajoute chaque cases adjacentes et qui ne sont pas dans l'ensemble noircies, dans l'ensemble piece."""
    piece.add((ligne, colonne))
   
    if (0 <= colonne - 1) and ((ligne,colonne-1) not in noircies) and ((ligne, colonne - 1) not in piece):
        detecter_piece(grille, noircies, ligne, colonne - 1, piece)
        
    if (0 <= ligne - 1) and ((ligne - 1,colonne) not in noircies) and ((ligne - 1, colonne) not in piece):
        detecter_piece(grille, noircies, ligne - 1, colonne, piece)
        
    if (len(grille) > ligne + 1) and ((ligne + 1,colonne) not in noircies) and ((ligne + 1, colonne) not in piece):
        detecter_piece(grille, noircies, ligne + 1, colonne, piece)
        
    if (len(grille[ligne]) > colonne + 1) and ((ligne,colonne + 1) not in noircies) and ((ligne, colonne + 1) not in piece):
        detecter_piece(grille, noircies, ligne, colonne + 1, piece)
    
     
    return piece
    
def connexe(grille, noircies):#regle 3

    """Compte le nombre de cases non noircies et compare la longeur de l'ensemble piece avec le nombre total de cases non noircies.
    Si il y a deux zones distinctes alors l'ensemble piece ne sera pas unique(plus d'un ensemble piece) et sa longeur sera donc différente du total de cases non noircies.  
    Renvoie False si la longeur est différente
    Renvoie True sinon."""
    
    ligne=0    
    colonne=0 
    total_piece=0
    if len(noircies) == len(grille)*len(grille):
        return False
    while ligne < len(grille):
        while colonne < len(grille): 
            if (ligne,colonne) not in noircies:
                if len(detecter_piece(grille, noircies, ligne, colonne, set())) >=1:
                    len_piece=len(detecter_piece(grille, noircies, ligne, colonne, set()))
                    
                    total_piece += 1  #compte les pièces restantes
                        
            colonne+=1
        colonne=0    
        ligne+=1
   
    if total_piece != len_piece:
        return False
    else :
        return True
        
def solveur(grille,noircies,i,j):
    """Vérifie si les 3 règles valent True """
    if (sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) != True:
       
        return None
    if (sans_conflit(grille,noircies) and sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) == True:
        return noircies
    elif (sans_conflit(grille,noircies) != True) and (sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) == True:
        """Va considérer chaque cellule une par une, et explorer récursivement le reste de la grille, d’abord en supposant que cette cellule est noircie, puis qu’elle reste visible.  """
        if i == len(grille):
            return None
        if (i,j) not in noircies:
            for y in range(len(grille)):
                
                if grille[i][j]==grille[i][y] and ((i,y) not in noircies) and(j != y):#si conflit sur la meme ligne
                    noircies.add((i,j))
                    if j==len(grille)-1:
                        solveur(grille,noircies,i+1,0)
                         
                    if j!=len(grille)-1:
                        solveur(grille,noircies,i,j+1)
                        
                    if (sans_conflit(grille,noircies) and sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) == True: 
                        return noircies
                        
                    else:
                        noircies.discard((i,j))   
                        if j==len(grille)-1:
                            solveur(grille,noircies,i+1,0)
                            
                        if j!=len(grille)-1:
                            solveur(grille,noircies,i,j+1)    
                            
                        if (sans_conflit(grille,noircies) and sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) == True: 
                            return noircies 
                            
                        else:
                            
                            return None
                elif grille[i][j]==grille[y][j] and ((y,j) not in noircies) and (i != y):#si conflit sur la meme colonne
                    
                    noircies.add((i,j))
                    if j==len(grille)-1:
                        solveur(grille,noircies,i+1,0)
                         
                    if j!=len(grille)-1:
                        solveur(grille,noircies,i,j+1)
                        
                    if (sans_conflit(grille,noircies) and sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) == True: 
                        return noircies
                        
                    else:
                        noircies.discard((i,j))   
                        if j==len(grille)-1:
                            solveur(grille,noircies,i+1,0)
                            
                        if j!=len(grille)-1:
                            solveur(grille,noircies,i,j+1)    
                            
                        if (sans_conflit(grille,noircies) and sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) == True: 
                            return noircies 
                            
                        else:
                            return None  
        
        if j==len(grille)-1:
            solveur(grille,noircies,i+1,0)
        else:
            solveur(grille,noircies,i,j+1)
            
def indice(grille,noircies):
    """Cherche une solution de la grille à l'aide du solveur, regarde quel case de l'ensemble noircies sont dans la solution et ajoute une case de la solution qui n'est pas dans l'ensemble noircies dans l'ensemble case_indice.
    Renvoie False si il y a une case dans l'ensemble noircies qui n'est pas dans la solution (et donc la grille ne peut plus etre resolue avec la configuration actuelle).
    Renvoie True sinon.  """
    liste_a_noircir=[]
    noircies=set()
    solveur(grille,noircies,0,0)
    for x in noircies:
        for y in deja_noircies:
            if y not in noircies:
                return False
        if x not in deja_noircies:
            liste_a_noircir.append((x))
    
    case_indice.add((liste_a_noircir[0]))    
    return True

def victoire(grille,noircies):
    """Renvoie True si les trois règle sont respectées.
    Renvoei False sinon."""
    if (sans_conflit(grille,noircies) and sans_voisines_noircies(grille, noircies) and connexe(grille,noircies)) == True:
        return True
    return False    
    
def dessine_menu():
                rectangle(0,600,600+100,600+100,remplissage='whitesmoke',tag='menu')
                rectangle(15,615,105,685,couleur='black')
                texte(60,650, "Vérifier" , ancrage='center', taille='19',couleur='black', police='Calibri')
                rectangle(125,615,215,685,couleur='black')
                texte(170,650, "Résoudre" , ancrage='center', taille='17',couleur='black', police='Calibri')
                rectangle(230,615,300,685,couleur='black')
                texte(265,650, "Indice" , ancrage='center', taille='17',couleur='black', police='Calibri')
                dessine_plateau(grille)
                image(557,655,'back_jeu.png') # fleche annuler coup
##Programme principale 

jouer = 0# Variable principale qui définit les différents étapes du jeu.
noircies=set()#ensemble des cases noircies
deja_noircies=noircies.copy()#copie de noircies
case_indice=set()#ensemble des cases indices
case_noircies=[] # listes de sauvegardes des cases noircies

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
            if 200 < x < 400 and 350 < y < 450 and jouer == 0 : #clique sur jouer
                grille=lire_grille(str(input("Entrez le niveau.txt : ")))
                # gère les différentes expections
                while grille =='Nom': 
                    print("Nom de fichier invalide")
                    grille=lire_grille(str(input("Entrez le niveau.txt : ")))
                    continue
                while grille =='Lettre':
                    print("Grille invalide")
                    grille=lire_grille(str(input("Entrez le niveau.txt : ")))
                    continue    
                while grille =='Rect':
                    print("Grille rectangulaire")
                    grille=lire_grille(str(input("Entrez le niveau.txt : ")))
                    continue   
                n = len(grille)
                taille_case = 600/n # taille d'une case du plateau 
                jouer=3
                
        if jouer ==0:#page d'accueil
            
            efface_tout()
            rectangle(0,600,600+100,600+100,remplissage='whitesmoke',tag='menu') 
            image(600/2,(600+100)/2,'accueil.png')
            texte(600/2,160, "HITORI", ancrage='center', taille='100',couleur='blanchedalmond', police='Calibri')
            texte(600/2,400, "Jouer" , ancrage='center', taille='35',couleur='red', police='Calibri')
            rectangle(600/3,350,600/1.5,450,couleur='white')
            
            
        if jouer >= 3:  # PARTIE COMMENCE
            efface_tout()
            dessine_plateau(grille)
            while True:
                efface_tout()
                dessine_menu()
                
                if victoire(grille,noircies):#si grille finie
                    jouer=8
                    
                if jouer ==4 :
                    texte(410,650,"Vous n'avez noirci aucune case", ancrage='center', taille='13',couleur='black', police='Calibri')
                    
                elif jouer==5 :
                    texte(400,650,"Il reste des doublons!", ancrage='center', taille='14',couleur='black', police='Calibri')
                    
                elif jouer ==6:
                    texte(410,650,"Des cases noircies sont voisines!", ancrage='center', taille='13',couleur='black', police='Calibri')
                    
                elif jouer ==7:
                    texte(400,650,"Il y a deux zones distinctes!", ancrage='center', taille='14',couleur='black', police='Calibri')
                elif jouer==8:
                    texte(400,650,"Grille complète", ancrage='center', taille='17',couleur='black', police='Calibri')
                    rectangle(100,250,300,350,remplissage='white')
                    texte(125,285,"RECOMMENCER ?",couleur='green',taille='15',police='Calibri italic')
                    
                    rectangle(335,250,535,350,remplissage='white')
                    texte(365,285,"AUTRE GRILLE?",couleur='green',taille='15',police='Calibri italic')
                elif jouer==9:
                    texte(410,650,"La grille ne peut être résolue", ancrage='center', taille='12',couleur='black', police='Calibri')
                    rectangle(100,250,300,350,remplissage='white')
                    texte(125,285,"RECOMMENCER ?",couleur='green',taille='15',police='Calibri italic')
                    
                    rectangle(335,250,535,350,remplissage='white')
                    texte(365,285,"AUTRE GRILLE?",couleur='green',taille='15',police='Calibri italic')
                    
                elif jouer==10:
                    texte(410,650,"La grille ne peut être résolue", ancrage='center', taille='12',couleur='black', police='Calibri')
                mise_a_jour()
                ev = donne_ev()
                ty = type_ev(ev)
                if ty == 'Quitte':
                    ferme_fenetre()
                    break
                elif ty == 'ClicGauche' and jouer !=8:
                    x,y = abscisse(ev), ordonnee(ev)
                    i, j = pixel_vers_case(x,y,taille_case)
                    if (-1<i<n and -1<j<n):#si clique sur une case
                        if jouer>3:#efface le texte dans le menu.
                            jouer=3
                        elif (i,j) in case_indice:#enleve l'indice si on clique dessus et noircit la case
                            case_indice.discard((i,j)) 
                            noircir_case(i,j)
                        elif (i,j) in noircies:#rend une case visisble
                            rendre_visible(i,j)      
                        elif (i,j) not in noircies:#noircie une case visisble
                            noircir_case(i,j) 
                     
                    if  537<x<585 and 625<y<670:#clique sur fleche annuler_coup
                        case_indice=set()
                        if jouer>=3 and noircies == set() and case_indice ==set(): #si aucune case noircie
                            jouer =0
                            break
                        elif jouer>=3 and noircies != set() :#si case noircie 
                            
                            jouer=3
                            noircies=annuler_coup()
                            deja_noircies=noircies.copy()
                            continue
                        elif jouer>=3 and case_indice !=set() :#si case indice
                            
                            jouer=3
                            continue
                            
                    if  15<x<105 and 615<y<685:#clique sur Verifier
                        if (sans_conflit(grille,noircies) != True or sans_voisines_noircies(grille,noircies) != True or connexe(grille,noircies) != True) and noircies == set(): # si une des regle n'est pas respecté
                            jouer=4
                            continue
                        elif (sans_conflit(grille,noircies) != True) and noircies != set():
                            jouer=5
                            continue
                            
                        elif (sans_voisines_noircies(grille,noircies) != True) and noircies != set():
                            jouer=6
                            continue
                            
                        elif (connexe(grille,noircies) != True) and noircies != set():
                            jouer=7
                            continue
                        elif (sans_conflit(grille,noircies) == True) and (sans_voisines_noircies(grille,noircies) == True) and (connexe(grille,noircies) == True):
                            jouer=8
                            continue
                    if 125<x<215 and 615<y<685:#clique sur resoudre
                        noircies=set() 
                        if solveur(grille,noircies,0,0)  != None:
                            
                            noircies=solveur(grille,noircies,0,0)
                            jouer=8
                            continue   
                        else:
                            jouer=9
                            continue
                            
                    if 230<x<300 and 615<y<685:#clique sur indice
                        if indice(grille,noircies) == False:
                            jouer=10
                            continue                
                        else:
                            noircies=deja_noircies.copy()
                            continue
                            
                elif ty == 'ClicGauche' and jouer >=8 : # si grille finie
                        x = abscisse(ev) 
                        y = ordonnee(ev) 
                        if 100<x < 300 and 250 <y<350 :# clique dans le rectangle recommencer
                            jouer =3 
                            noircies=set()
                            case_indice=set()
                            case_noircies=[]
                            deja_noircies=noircies.copy()
                            break 
                            
                        if 335<x < 535 and 250 <y<350 :# clique dans le rectangle autre grille
                            jouer =0
                            noircies=set()
                            case_indice=set()
                            case_noircies=[]
                            deja_noircies=noircies.copy()
                            break 
                    
        