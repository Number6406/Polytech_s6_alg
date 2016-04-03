#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NB_MAX_NOEUDS 20

typedef struct arc *parc_t ;

typedef struct n {
  int        etiquette_noeud ; // etiquette du noeud
  parc_t     liste_arcs ; // arcs sortants du noeud
  struct n   *suivant_noeud ; // noeud suivant
  int		 parcouru; // vérifier sur le noeud a été parcouru lors d'un traitement
  int 		 cout;
  struct n	 *pred;
} noeud_t, *pnoeud_t ;

typedef struct arc {
  int         etiquette_arc ; // etiquette de l'arc
  pnoeud_t    noeud_dest ; // identificateur du noeud
  struct arc *suivant_arc ; // arc suivant
} arc_t, *parc_t ;

typedef struct file{
	pnoeud_t elt;
	struct file *suivant_file;
	struct file *prec_file;
} file, *debut_file;

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

// Remet à zéro le champ parcouru du graphe
void deparcourir(pnoeud_t graphe) {
	pnoeud_t noeudCourr = graphe;
	while(noeudCourr != NULL) {
		noeudCourr->parcouru = 0;
		noeudCourr = noeudCourr->suivant_noeud;
	}
}

// Parcours en profondeur
int profondeur(pnoeud_t graphe) {
	deparcourir(graphe);
	printf("Parcours en profondeur \n");
	void aux(pnoeud_t graphe){
		pnoeud_t noeudCourr = graphe;
		
		while(noeudCourr != NULL) {
			if(noeudCourr->parcouru == 0) {
				noeudCourr->parcouru = 1;
				printf("%c ", 'A'-1+noeudCourr->etiquette_noeud);
				
				parc_t arcCourr = noeudCourr->liste_arcs;
				while(arcCourr != NULL) {
					aux(arcCourr->noeud_dest);
					
					arcCourr = arcCourr->suivant_arc;
				}	
			}
			noeudCourr = noeudCourr->suivant_noeud;
		}
	}
	aux(graphe);
	
	return 0;
}


// Structure de file utile au parcours en largeur
// First In First Out
// Ajouter un noeud en queue de file
debut_file ajout_queue(debut_file f, pnoeud_t p){
	if(f==NULL){ 
		f = malloc(sizeof(file));
		f->prec_file=NULL;
		f->suivant_file=NULL;
		f->elt = p;
		return f;
	} else{
		debut_file tmp = f;
		debut_file prec;
		while(tmp!=NULL){
			prec = tmp;
			tmp = tmp->suivant_file;
		}
		tmp=malloc(sizeof(file));
		tmp->elt = p;
		tmp->suivant_file=NULL;
		tmp->prec_file = prec;
		prec->suivant_file=tmp;
		return f;
	}
}

// Vérifie si un élément appartient à la file
int appartient_file(debut_file f, pnoeud_t p){
	debut_file tmp = f;
	while(tmp!=NULL && tmp->elt != p){
		tmp = tmp->suivant_file;
	}
	return tmp!=NULL;
}

// Enlever l'élément donné en argument de la file
debut_file enlever_file(debut_file f, pnoeud_t p){
	debut_file tmp,prec;
	tmp=f;
	prec=NULL;
	while(tmp!=NULL && tmp->elt!=p){
		prec=tmp;
		tmp=tmp->suivant_file;
	}
	if(tmp!=NULL){
		if(prec==NULL){
			f=tmp->suivant_file;
			free(tmp);
		} else{
		prec->suivant_file=tmp->suivant_file;
		free(tmp);
		}
	}
	return f;
}

// Parcours en largeur d'un graphe
void parcours_largeur(pnoeud_t p){
	debut_file f = NULL;
	pnoeud_t en_cours = p;
	
	printf("\nParcours en largeur\n");
	
	deparcourir(p);
	
	f = ajout_queue(f,p);
	
	while(f!=NULL){
		pnoeud_t s;
		s = f -> elt;
		f = enlever_file(f,s);
		if(!(s->parcouru)){
			s->parcouru=1;
			printf("| %c ",'A'-1+s->etiquette_noeud);
			
			parc_t t = s->liste_arcs;
			
			while(t!=NULL){
				pnoeud_t c = t->noeud_dest;
				if(!(c->parcouru)){
					f = ajout_queue(f,c);
				}
				t = t->suivant_arc;
			}
		}
		if(f==NULL){
			if(en_cours!=NULL){
				f = ajout_queue(f,en_cours);
				en_cours = en_cours->suivant_noeud;
			}
		}
	}
	printf("|\n");
	// FIN
}
  
             
