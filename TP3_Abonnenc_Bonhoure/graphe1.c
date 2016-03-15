#include <stdio.h>
#include <limits.h>

#define MAX_NOEUDS     100

int etiquettes  [MAX_NOEUDS] ;

int arcs [MAX_NOEUDS][MAX_NOEUDS] ;

typedef int pnoeud_t ; // indice du numero de noeud

int nb_noeuds ;

int nombre_arcs (pnoeud_t p) {
	int i, j;
	int somme = 0;

	for(i=0; i<MAX_NOEUDS; i++) {
		for(j=0; j<MAX_NOEUDS; j++) {
			if(G[i][j]) somme++;
		}
	}
	
	return somme;
}


int degre_graphe (pnoeud_t p) {
	
}


int independant (pnoeud_t p) {
  /* Les aretes du graphe n'ont pas de sommet en commun */
	/** On veut qu'il y ait au plus une arète par ligne, et colonne*/
	unsigned int i,j;
	int col,lig;
	col = 1;
	lig = 1;
	i = 0; 
	
	while (i<nb_noeuds && col && lig){
		int sommec = 0;
		int sommel = 0;
		j = 0;
		while(j<nb_noeuds && sommec <=1 && sommel <=1){
			if( arcs [i][j] != INT_MAX) {
				sommec++;
				sommel++;
			}
			j++;
		}
		col = sommec <=1;
		lig = sommel <=1;
		i++;
	}
	return(col && lig);
}


int complet (pnoeud_t p) {
	/* Toutes les paires de sommet du graphe sont jointes par un arc */
	/** ie. aucun arc inexistant*/
	unsigned int i,j;
	int fin = 0;
	i=0;
	while( i < nb_noeuds && !fin){
		j = 0;
		while (j < nb_noeuds && arcs[i][j] != INT_MAX) {
			j++;
		}
		fin = j!=nb_noeuds;
	}
	return (i==nb_noeuds && j==nb_noeuds);
}



int main (int argc, char **argv) {

	return 0;
}

  
             
