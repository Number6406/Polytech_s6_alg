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

void affGraphe(pnoeud_t graphe);

// Fonction interactive de création d'un graphe
pnoeud_t creer_graphe();

void libererGraphe(pnoeud_t graphe) ;

int lire_graphe(pnoeud_t *adr, char *nomFich);

// Nombre d'arc dans une liste d'arc fournie en paramètre
int nb_arc_list(parc_t l);

// Renvoie le nombre d'arc total du graphe
int nombre_arcs (pnoeud_t p);

// Nombre de noeuds dans un graphe
int nbNoeudGraphe(pnoeud_t graphe) ;

// Renvoie le degré d'un graphe
int degre_graphe (pnoeud_t p);

// Renvoie une booléen (vrai) si le graphe est indépendant (tous ses noeuds)
int independant (pnoeud_t p);

// Renvoie vrai si le graphe est complet
int complet (pnoeud_t p);

// Parcours en profondeur
int profondeur(pnoeud_t graphe);

// Parcours en largeur d'un graphe
void parcours_largeur(pnoeud_t p);
