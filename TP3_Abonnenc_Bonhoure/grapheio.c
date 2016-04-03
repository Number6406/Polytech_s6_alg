#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

// Affichage d'un graphe
void affGraphe(pnoeud_t graphe) {
	
	pnoeud_t tmpNoeuds = graphe;
	while(tmpNoeuds != NULL) {
		printf("Noeud %c [%d]|", 'A'+(tmpNoeuds->etiquette_noeud)-1, tmpNoeuds->parcouru);
		
		parc_t tmpArcs = tmpNoeuds->liste_arcs;
		while(tmpArcs != NULL) {
			printf(" -(%d)-> %c | ", tmpArcs->etiquette_arc, 'A'-1+tmpArcs->noeud_dest->etiquette_noeud);
			tmpArcs = tmpArcs->suivant_arc;
		}
		
		printf("\n");
		tmpNoeuds = tmpNoeuds->suivant_noeud;
	}
	
}

// Affichage d'un graphe et du cout d'un chemin
// Attention les couts doivent ête initialisés !
void affGraphe_cout(pnoeud_t graphe) {
	
	pnoeud_t tmpNoeuds = graphe;
	while(tmpNoeuds != NULL) {
		if(tmpNoeuds->pred!=NULL){
			printf("Noeud %c [Coût : %d][Pred : %c]|", 'A'+(tmpNoeuds->etiquette_noeud)-1, tmpNoeuds->cout,'A'-1+tmpNoeuds->pred->etiquette_noeud);
		} else {
			printf("Noeud %c [Coût : %d]|", 'A'+(tmpNoeuds->etiquette_noeud)-1, tmpNoeuds->cout);
		}
		parc_t tmpArcs = tmpNoeuds->liste_arcs;
		while(tmpArcs != NULL) {
			printf(" -(%d)-> %c | ", tmpArcs->etiquette_arc, 'A'-1+tmpArcs->noeud_dest->etiquette_noeud);
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

int lire_graphe(pnoeud_t *adr, char *nomFich) {
	pnoeud_t graphe = *adr;
	int n, a;
	FILE *fichier = fopen(nomFich, "r");
	int nbNoeuds, nbArcs;
	int noeudDest, etiqArc;
	
	if(fichier==NULL) { fprintf(stderr, "Le fichier n'existe pas."); return 1; }
	//Lit le nombre de noeuds du graphe et les créé en conséquence
	fscanf(fichier, "%d", &nbNoeuds);
	
	if(nbNoeuds == 0) { printf("Erreur : pas de noeuds\n"); return 1; }
	graphe = generationNoeuds(graphe, nbNoeuds);
	

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
			arcCourr->noeud_dest = noeudPotentiel;
			arcCourr->etiquette_arc = etiqArc;
			arcCourr->suivant_arc = NULL;
			// Ajout en queue
			parc_t tmp = noeudCourr->liste_arcs;
			parc_t prec=NULL;
			while(tmp!=NULL){
				prec = tmp;
				tmp = tmp->suivant_arc;
			}
			if(prec == NULL){noeudCourr->liste_arcs = arcCourr;}
			else {
				prec->suivant_arc=arcCourr;
			}
			
		}
		noeudCourr = noeudCourr->suivant_noeud; //Passage au noeud suivant
		
	}
	
	*adr = graphe;
	
	return 0;
}
