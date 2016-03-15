#include <stdio.h>


typedef struct a *parc_t ;


typedef struct n {
  int        etiquette_noeud ; // etiquette du noeud
  parc_t     liste_arcs ; // arcs sortants du noeud
  struct n   *suivant_noeud ; // noeud suivant
} noeud_t, *pnoeud_t ;


typedef struct a {
  int         etiquette_arc ; // etiquette de l arc
  pnoeud_t    noeud_dest ; // identificateur du noeud
  struct a *  suivant_arc ; // arc suivanr
} arc_t, *parc_t ;


int nombre_arcs (pnoeud_t p) {

}


int degre_graphe (pnoeud_t p) {
 
}


int independant (pnoeud_t p) {
  /* Les aretes du graphe n'ont pas de sommet en commun */

}


int complet (pnoeud_t p) {
  /* Toutes les paires de sommet du graphe sont jointes par un arc */
  
}



int main (int argc, char **argv)
{

}

  
             
