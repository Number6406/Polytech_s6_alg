#ifndef GRAPHEIO_H
#define GRAPHEIO_H

// Affichage d'un graphe
void affGraphe(pnoeud_t graphe);

// Affichage d'un graphe et du cout d'un chemin
// Attention les couts doivent ête initialisés !
void affGraphe_cout(pnoeud_t graphe);

// Fonction interactive de création d'un graphe
pnoeud_t creer_graphe();

// Libére la mémoire d'un graphe
void libererGraphe(pnoeud_t graphe);

// Lit un graphe depuis un fichier
int lire_graphe(pnoeud_t *adr, char *nomFich);

#endif
