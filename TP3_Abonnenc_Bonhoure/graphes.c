// TD3 ALG, Graphes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAILLE 10

typedef int graphe_m[TAILLE][TAILLE];

void initGrapheM(graphe_m G) {
	int i, j;

	for(i=0; i<TAILLE; i++) {
		for(j=0; j<TAILLE; j++) {
			G[i][j] = INT_MAX;
		}
	}

}

int nbArcsM(graphe_m G) {
	int i, j;
	int somme = 0;

	for(i=0; i<TAILLE; i++) {
		for(j=0; j<TAILLE; j++) {
			if(G[i][j]) somme++;
		}
	}
	
	return somme;
}

int main(void) {
	
	return 0;
}
