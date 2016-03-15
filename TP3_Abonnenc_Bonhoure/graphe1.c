#include <stdio.h>

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

}


int complet (pnoeud_t p) {
  /* Toutes les paires de sommet du graphe sont jointes par un arc */
  
}



int main (int argc, char **argv) {

}

  
             
