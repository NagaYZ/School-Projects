#ifndef __DICO__
#define __DICO__

/*structure arbre lexico */
typedef struct dico_mot{
	char lettre;
	struct dico_mot *fg;
    struct dico_mot *fd;
    struct dico_mot *fils;
}Dico_mot, *Dico;

Dico alloueDico(char lettre);

void creer_arbre_fichier(FILE* in, Dico* dico);/*cree un arbre lexiocgraphique a partir des mots du fichier*/

void ajout_mot_dico(Dico* dico, char* mot);/*ajoute une chaine de caractere a larbre*/

int recherche_mot_dico(Dico dico, char* mot);/*renvoie 1 si le mot est dans le dico*/

#endif
