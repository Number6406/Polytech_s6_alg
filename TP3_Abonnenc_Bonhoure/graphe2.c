#include <stdio.h>
#include <stdlib.h>


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

int etiquetteArcs = 1;


// Ajoute un arc dans un graphe, si l'arc n'existe pas déjà
int ajouter_arc(pnoeud_t graphe, pnoeud_t noeudParent, int etiqNoeudDirecteur) {
	
	parc_t arcVerif = noeudParent->liste_arcs;
	while(arcVerif != NULL) {
		if(arcVerif->noeud_dest->etiquette_noeud == etiqNoeudDirecteur) {return 1;}
		arcVerif = arcVerif->suivant_arc;
	}
	
	pnoeud_t noeudPotentiel = graphe; //On parcours le graphe pour trouver le noeud en question
	while(noeudPotentiel != NULL && noeudPotentiel->etiquette_noeud != etiqNoeudDirecteur){
		noeudPotentiel = noeudPotentiel->suivant_noeud;
	}
	
	if(noeudPotentiel != NULL) { //On définit le noeud sur lequel pointe l'arc s'il existe
		parc_t nv_arc = malloc(sizeof(parc_t)); //Allocation dynamique de la mémoire d'un nouvel arc
		
		nv_arc->etiquette_arc = etiquetteArcs++;
		nv_arc->noeud_dest = noeudPotentiel;
		nv_arc->suivant_arc = noeudParent->liste_arcs;
		noeudParent->liste_arcs = nv_arc;
		
		return 0;
	} else {
		return 2;
	}
	
}

// Fonction interactive de création d'un graphe
pnoeud_t creer_graphe(){
	pnoeud_t G,P,C;
	int nb_noeuds;
	unsigned int i;
	int erreur;
	int nbArcs;
	
	printf("Bienvenue dans l'interface de création de graphe.\n Combien de noeuds souhaitez vous créer ? ");
	scanf("%d",&nb_noeuds);
	G = malloc(sizeof(noeud_t));
	printf("Quelle est l'étiquette de votre noeud ? ");
	scanf("%d",&G->etiquette_noeud);
	P=G;
	for (i = 1; i < nb_noeuds; i++){
		C = malloc(sizeof(noeud_t));
		printf("Quelle est l'étiquette de votre noeud ? ");
		scanf("%d",&C->etiquette_noeud);
		C->parcouru = 0;
		P->suivant_noeud = C;
		P=C;
	}
	
	P = G;
	char rep;
	while(P!=NULL){
		nbArcs = 0;
		printf("Noeud %d : A t'il des arcs ? o/n ",P->etiquette_noeud);
		scanf(" %c",&rep);
		while(rep == 'o' || rep == 'O'){
			int etiq;
			printf("Vers quel noeud va t'il ? ");
			scanf("%d",&etiq);
			
			if((erreur = ajouter_arc(G,P,etiq))) {
				//erreur d'ajout
				if(erreur == 1) {
					printf("Cet arc est déjà présent pour ce noeud.\n");
				} else {printf("L'étiquette spécifiée n'existe pas. Rien n'a été créé.\n");}
			} else {
				nbArcs++;
			}
			
			if(nbArcs < nb_noeuds) {
				printf("Un autre arc ? o/n ");
				scanf(" %c",&rep);
			} else { rep = 'n'; }
		}
		P = P->suivant_noeud;
	}
	
	printf("Fin de la création de votre graphe.\n");
	
	return G;
}

// Affichage d'un graphe
void affGraphe(pnoeud_t graphe) {
	
	pnoeud_t tmpNoeuds = graphe;
	while(tmpNoeuds != NULL) {
		printf("Noeud %d |", tmpNoeuds->etiquette_noeud);
		
		parc_t tmpArcs = tmpNoeuds->liste_arcs;
		while(tmpArcs != NULL) {
			printf(" Arc %d (Noeud %d) -", tmpArcs->etiquette_arc, tmpArcs->noeud_dest->etiquette_noeud);
			tmpArcs = tmpArcs->suivant_arc;
		}
		
		printf("\n");
		tmpNoeuds = tmpNoeuds->suivant_noeud;
	}
	
}

// Nombre d'arc dans une liste d'arc fournie en paramètre
int nb_arc_list(parc_t l){
	int nb = 0;
	parc_t tmp = l;
	while(tmp!=NULL){
		tmp = tmp->suivant_arc;
		nb++;
	}
	return nb;
}

// Renvoie le nombre d'arc total du graphe
int nombre_arcs (pnoeud_t p) {
	int somme = 0;
	pnoeud_t tmp = p;
	while(tmp != NULL){
		somme += nb_arc_list(tmp->liste_arcs);
		tmp = tmp->suivant_noeud;
		
	}
	return somme;
}


// Nombre de noeuds dans un graphe
int nbNoeudGraphe(pnoeud_t graphe) {
	int nbNoeuds = 0;
	
	pnoeud_t noeudC = graphe;
	while(noeudC != NULL) {
	  nbNoeuds++;
	  noeudC = noeudC->suivant_noeud;
	}
	
	return nbNoeuds;
}

// Renvoie le degré d'un graphe
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

// Renvoie une booléen (vrai) si le graphe est indépendant (tous ses noeuds)
int independant (pnoeud_t p) {
  /* Les aretes du graphe n'ont pas de sommet en commun */
	pnoeud_t noeudC = p;
	while(noeudC != NULL) {
		parc_t arcC = noeudC->liste_arcs;
		int nbArcs = 0;
		while(arcC != NULL) {
			if(arcC->noeud_dest->parcouru) return 0; //Si ce noeud est déjà parcouru, le graphe n'est pas independant
			arcC->noeud_dest->parcouru = 1;
			
			nbArcs += 1;
			arcC = arcC->suivant_arc;
		}
		if(nbArcs > 1) return 0;
		noeudC = noeudC->suivant_noeud;
	}
	
	return 1;
}

// Renvoie vrai si le graphe est complet
int complet (pnoeud_t p) {
  /* Toutes les paires de sommet du graphe sont jointes par un arc */
  
  int nbNoeuds = nbNoeudGraphe(p);
  int nbArcs;
  
  pnoeud_t noeudC = p;
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
	pnoeud_t graphe = creer_graphe();
	affGraphe(graphe);
	
	printf("Nombre d'arcs : %d\n", nombre_arcs(graphe));
	printf("Nombre de noeuds : %d\n", nbNoeudGraphe(graphe));
	printf("Dégré du graphe : %d\n", degre_graphe(graphe));
	printf("Indépendant ? %d\n", independant(graphe));
	printf("Complet ? %d\n", complet(graphe));
	
	return 0;
}

  
             
