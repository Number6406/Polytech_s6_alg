#include <stdio.h>


typedef struct arc *parc_t ;

typedef struct n {
  int        etiquette_noeud ; // etiquette du noeud
  parc_t     liste_arcs ; // arcs sortants du noeud
  struct n   *suivant_noeud ; // noeud suivant
  int		 parcouru; // vérifier sur le noeud est atteint par un arc
} noeud_t, *pnoeud_t ;


typedef struct arc {
  int         etiquette_arc ; // etiquette de l arc
  pnoeud_t    noeud_dest ; // identificateur du noeud
  struct arc *suivant_arc ; // arc suivant
} arc_t, *parc_t ;


int nb_arc_list(parc_t l){
	int nb = 0;
	parc_t tmp = l;
	while(tmp!=NULL){
		tmp = tmp->suivant_arc;
		nb++;
	}
	return nb;
}

int nombre_arcs (pnoeud_t p) {
	int somme = 0;
	pnoeud_t tmp = p;
	while(tmp != NULL){
		somme += nb_arc_list(tmp->liste_arcs);
		tmp = tmp->suivant_noeud;
		
	}
	return somme; // MDIFIIIIIIERRRRR
}


int degre_graphe (pnoeud_t p) {
	int deg = 0;
	
	int deg_noeud(pnoeud_t p ){
		return nb_arc_list(p->liste_arcs);
	}
	
	pnoeud_t tmp = p;
	while(tmp!=NULL){
		int d = deg_noeud(tmp);
		if(d>deg) deg = d;
		tmp = tmp->suivant_noeud;
	}
	
	return deg;
}


int independant (pnoeud_t p) {
  /* Les aretes du graphe n'ont pas de sommet en commun */
  
	pnoeud_t noeudC = p;
	while(noeudC != NULL) {
		
		parc_t arcC = noeudC->liste_arcs;
		while(arcC != NULL) {
			if(arcC->noeud_dest->parcouru) return 0; //Si ce noeud est déjà parcouru, le graphe n'est pas independant
			arcC->noeud_dest->parcouru = 1;
			
			arcC = arcC->suivant_arc;
		}
		
		noeudC = noeudC->suivant_noeud;
	}
	
	return 1;
}


int complet (pnoeud_t p) {
  /* Toutes les paires de sommet du graphe sont jointes par un arc */
  
  int nbNoeuds = 0;
  int nbArcs;
  
  pnoeud_t noeudC = p;
  while(noeudC != NULL) {
	  nbNoeuds++;
	  noeudC = noeudC->suivant_noeud;
  }
  
  noeudC = p;
  while(noeudC != NULL) {
	
	parc_t arcC = noeudC->liste_arcs;
	nbArcs = 0;
	while(arcC != NULL) {
		nbArcs++;
		
		arcC = arcC->suivant_arc;
	}
	
	if(nbArcs != nbNoeuds) return 0;
  
	noeudC = noeudC->suivant_noeud;
  }
  
  return 1;
}



int main (int argc, char **argv)
{
	return 0;
}

  
             
