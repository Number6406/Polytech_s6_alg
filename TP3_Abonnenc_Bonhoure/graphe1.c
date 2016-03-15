#include <stdio.h>
#include <limits.h>

#define MAX_NOEUDS     100

int etiquettes  [MAX_NOEUDS] ;

int arcs [MAX_NOEUDS][MAX_NOEUDS] ;

typedef int pnoeud_t ; // indice du numero de noeud

int nb_noeuds ;

void init() {
	int i, j;

	for(i=0; i<nb_noeuds; i++) {
		for(j=0; j<nb_noeuds; j++) {
			arcs[i][j] = INT_MAX;
		}
	}

}

int nombre_arcs (pnoeud_t p) {
	int i, j;
	int somme = 0;

	for(i=0; i<nb_noeuds; i++) {
		for(j=0; j<nb_noeuds; j++) {
			if(arcs[i][j] != INT_MAX) somme++;
		}
	}
	
	return somme;
}


int degre_graphe (pnoeud_t p) {
	int i, j;
	int max = INT_MIN;

	for(i=0; i<nb_noeuds; i++) {
		
		int degreCourrant = 0;
		for(j=0; j<nb_noeuds; j++) {
			if(arcs[i][j] != INT_MAX) {degreCourrant++;}
		}
		
		if(degreCourrant > max) {
			max = degreCourrant;
		}
	}
	
	return max;
}


int independant (pnoeud_t p) {
  /* Les aretes du graphe n'ont pas de sommet en commun */
  return 0;
}


int complet (pnoeud_t p) {
  /* Toutes les paires de sommet du graphe sont jointes par un arc */
  return 0;
}

int main (int argc, char **argv) {
	nb_noeuds = 10;
	pnoeud_t p = 1;
	
	init();
	arcs[0][1] = 1;
	arcs[0][2] = 5;
	arcs[1][2] = 12;
	
	printf("Nombre de noeuds : %d\n", nombre_arcs(p));
	printf("Degré du graphe : %d\n", degre_graphe(p));
	
	return 0;
}

  
             
