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
} noeud_t, *pnoeud_t ;

typedef struct arc {
  int         etiquette_arc ; // etiquette de l arc
  pnoeud_t    noeud_dest ; // identificateur du noeud
  struct arc *suivant_arc ; // arc suivant
} arc_t, *parc_t ;

typedef struct file{
	pnoeud_t elt;
	struct file *suivant_file;
	struct file *prec_file;
} file, *debut_file;

// Affichage d'un graphe
void affGraphe(pnoeud_t graphe) {
	
	pnoeud_t tmpNoeuds = graphe;
	while(tmpNoeuds != NULL) {
		printf("Noeud %d [%d]|", tmpNoeuds->etiquette_noeud, tmpNoeuds->parcouru);
		
		parc_t tmpArcs = tmpNoeuds->liste_arcs;
		while(tmpArcs != NULL) {
			printf(" -(%d)-> %d | ", tmpArcs->etiquette_arc, tmpArcs->noeud_dest->etiquette_noeud);
			tmpArcs = tmpArcs->suivant_arc;
		}
		
		printf("\n");
		tmpNoeuds = tmpNoeuds->suivant_noeud;
	}
	
}

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
		
		printf("Etiquette arc : ");
		scanf("%d",&nv_arc->etiquette_arc);
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
	G->etiquette_noeud=1;
	P=G;
	for (i = 1; (i<NB_MAX_NOEUDS)&&i < nb_noeuds; i++){
		C = malloc(sizeof(noeud_t));
		C->etiquette_noeud= i+1;
		C->parcouru=0;
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

void libererGraphe(pnoeud_t graphe) {
	pnoeud_t tmp, parcourir;
	 parcourir = graphe;
	while(parcourir!=NULL){
		tmp = parcourir;
		parcourir = parcourir->suivant_noeud;
		free(tmp);
	}
}

pnoeud_t generationNoeuds(pnoeud_t graphe, int nbNoeuds) {
	if(graphe != NULL) { libererGraphe(graphe); }
	
	//initialisation du graphe avec le premier arc
	graphe = malloc(sizeof(noeud_t));
	graphe->etiquette_noeud = 1;
	graphe->suivant_noeud = NULL;
	graphe->liste_arcs = NULL;
	
	int i;
	// création de tous les noeuds successeurs du graphe
	for (i=nbNoeuds; i>1; i--) {
		pnoeud_t noeudCourr = malloc(sizeof(noeud_t));
		noeudCourr->etiquette_noeud= i;
		noeudCourr->suivant_noeud = graphe->suivant_noeud;
		noeudCourr->parcouru = 0;
		noeudCourr->liste_arcs = NULL;
		graphe->suivant_noeud = noeudCourr;
	}
	
	return graphe;
}

int lire_graphe(pnoeud_t graphe, char *nomFich) {
	int n, a;
	FILE *fichier = fopen(nomFich, "r");
	int nbNoeuds, nbArcs;
	int noeudDest, etiqArc;
	
	if(fichier==NULL) { fprintf(stderr, "Le fichier n'existe pas."); return 1; }
	//Lit le nombre de noeuds du graphe et les créé en conséquence
	fscanf(fichier, "%d", &nbNoeuds);
	
	if(nbNoeuds == 0) { printf("Erreur : pas de noeuds\n"); return 1; }
	graphe = generationNoeuds(graphe, nbNoeuds);
	
	affGraphe(graphe);

	//Création des arcs de chaque noeud
	pnoeud_t noeudCourr = graphe; //Noeud courrant permettant la création des arcs
	for(n=0; n<nbNoeuds; n++) {
		
		fscanf(fichier, "%d", &nbArcs);
		
		for(a=0; a<nbArcs; a++) {
		
			fscanf(fichier, "%d\[%d]", &noeudDest, &etiqArc); //lecture d'un format d'arc
			
			pnoeud_t noeudPotentiel = graphe; //On parcours le graphe pour trouver le noeud en question
			while(noeudPotentiel != NULL && noeudPotentiel->etiquette_noeud != noeudDest){
				noeudPotentiel = noeudPotentiel->suivant_noeud;
			}
			
			parc_t arcVerif = noeudCourr->liste_arcs; // Vérification de l'existence de l'arc dans la liste
			
			while(arcVerif != NULL) {
				if(arcVerif->noeud_dest->etiquette_noeud == noeudDest) { fprintf(stderr, "Arc déjà présent\n"); return 1;}
				arcVerif = arcVerif->suivant_arc;
			}
			
			//Si le noeud vers lequel est censé pointer l'arc n'existe pas, retourne une erreur
			if(noeudPotentiel == NULL) { fprintf(stderr, "Le noeud n'existe pas.\n"); return 1; } 
			// création de l'arc dans la liste s'il n'est pas présent
			parc_t arcCourr = malloc(sizeof(parc_t));
			arcCourr->etiquette_arc = etiqArc;
			arcCourr->suivant_arc = noeudCourr->liste_arcs;
			noeudCourr->liste_arcs = arcCourr;
			
		}
		noeudCourr = noeudCourr->suivant_noeud; //Passage au noeud suivant
		
	}
	
	return 0;
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
				printf("%d ", noeudCourr->etiquette_noeud);
				
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
	
	printf("Parcours en largeur\n");
	deparcourir(p);
	f = ajout_queue(f,p);
	
	while(f!=NULL){
		
		pnoeud_t s;
		s = f -> elt;
		f = enlever_file(f,s);
		if(!(s->parcouru)){
			s->parcouru=1;
			printf("| %d ",s->etiquette_noeud);
			
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

int main (int argc, char **argv)
{
	pnoeud_t graphe = NULL;
	//graphe = creer_graphe();

	if(argc < 2) { printf("erreur de lecture : pas de nom indiqué"); return 1; }
	lire_graphe(graphe, argv[1]);
	
	affGraphe(graphe);
	
	
	printf("Nombre d'arcs : %d\n", nombre_arcs(graphe));
	printf("Nombre de noeuds : %d\n", nbNoeudGraphe(graphe));
	printf("Dégré du graphe : %d\n", degre_graphe(graphe));
	printf("Indépendant ? %d\n", independant(graphe));
	printf("Complet ? %d\n", complet(graphe));
	
	affGraphe(graphe);
	
	//parcours_largeur(graphe);
	profondeur(graphe);
	
	
	return 0;
}

  
             
