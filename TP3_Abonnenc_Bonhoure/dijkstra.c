#include "graphe.h"
#include <math.h>
#include <stdlib.h>

void init(pnoeud_t g){
	pnoeud_t tmp = g;
	if(tmp!=NULL){
		tmp->cout = 0;
		tmp->pred = NULL;
		tmp = tmp->suivant_noeud;
	}
	while (tmp!=NULL){
		tmp->cout = INFINITY;
		tmp->pred = NULL;
		tmp = tmp->suivant_noeud;
	}
}

void relax(pnoeud_t q, parc_t a){
	if(q!=NULL && a!=NULL && a->noeud_dest!=NULL){
		pnoeud_t r = a->noeud_dest;
		if((q->cout)+(a->etiquette_arc) < (r->cout)){
			r->cout = (q->cout)+(a->etiquette_arc);
			r->pred = q;
		}
	}
}

// Tout les arcs ont une valeur >= 0
int precond_dijkstra(pnoeud_t g){
	pnoeud_t tmp = g;
	while (tmp != NULL){
		parc_t a = tmp->liste_arcs;
		while(a!=NULL && a->etiquette_arc>=0){
			a = a->suivant_arc;
		}
		if(a!=NULL){return 0;}
		tmp = tmp->suivant_noeud;
	}
	return 1;
}

// Noeud de cout miniaml dans la file
pnoeud_t min_d(debut_file f){
	pnoeud_t min;
	debut_file tmp = f;
	if(tmp!=NULL) min = tmp->elt;
	while(tmp!=NULL){
		if(tmp->elt->cout < min->cout) min = tmp->elt;
		tmp = tmp->suivant_file;
	}
	return min;
}

// Ajout tout les noeud d'un graphe à une file
debut_file ajouter_graphe(pnoeud_t g){
	debut_file f;
	pnoeud_t tmp = g;
	while (tmp!=NULL){
		f = ajout_queue(f,tmp);
		tmp = tmp->suivant_noeud;
	}
	return f;
}

// Algorithme de dijkstra
void dijkstra(pnoeud_t g){
	init(g);
	debut_file Q = ajouter_graphe(g);
	while (Q!=NULL){
		pnoeud_t q = min_d(Q);
		Q = enlever_file(Q,q);
		parc_t larc = q->liste_arcs;
		while(larc!=NULL){
			relax(q,larc);
			larc = larc->suivant_arc;
		}
	}
}
