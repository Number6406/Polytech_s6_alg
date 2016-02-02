
#include <stdio.h>
#include <stdlib.h>


typedef struct Noeud Noeud;
struct Noeud
{
	int nb;
    int cle [3];
    Noeud *enfant [4];
};

typedef struct Noeud* Arbre;


Arbre vide (void) {
	Arbre A;
	A = NULL;
	return A;
};

/*

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->nombre = 0;
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}
*/

Arbre test_bidon(void){
	Arbre A;
	A = malloc(sizeof(Noeud));
	A->nb = 2;
	A->cle[0] = 5;
	A->cle[1] = 12;
	A->enfant[0] = malloc(sizeof(Noeud));
	A->enfant[1] = NULL;
	A->enfant[2] = malloc(sizeof(Noeud));
	A->enfant[0]->nb = 1;
	A->enfant[0]->cle[0] = 3;
	A->enfant[0]->enfant[0] = NULL;
	A->enfant[0]->enfant[1] = NULL;
	A->enfant[2]->nb = 1;
	A->enfant[2]->cle[0] = 15;
	A->enfant[2]->enfant[0] = NULL;
	A->enfant[2]->enfant[1] = NULL;
	
	return A;
}

void parcours(Arbre A){
	int i;
	if (A != NULL){
		for(i=0; i < A->nb;i++){
			parcours(A->enfant[i]);
			printf("%d ",A->cle[i]);
		}
		parcours(A->enfant[i]);
	}
}

int recherche_b (int x, Arbre A) {
	int i,b;
	b = 0;
	if (A != NULL){
		for(i=0; i < A->nb;i++){
			b = b || recherche_b(x,A->enfant[i]);
			if (A->cle[i] == x) return 1;
		}
		b = b || recherche_b(x,A->enfant[i]);
		return b;
	}
	else return 0;
}

Arbre recherche_p (int x, Arbre A) {
	int i;
	Arbre b = NULL;
	if (A != NULL){
		for(i=0; i < A->nb;i++){
			b = recherche_p(x,A->enfant[i]);
			if (A->cle[i] == x) return A;
			if (b != NULL) return b;
		}
		b = recherche_p(x,A->enfant[i]);
		return b;
	}
	else return NULL;
}

void insertion (int cle; Arbre A){
	
}

int main(void) {
	Arbre A = test_bidon();
	parcours(A);
	printf("\n3 est dans A : %d\n",recherche_b(3,A));
	printf("8 est dans A : %d\n",recherche_b(8,A));
	printf("\n3 est dans A ?\n");
	parcours(recherche_p(3,A));
	printf("\n8 est dans A ?\n");
	parcours(recherche_p(8,A));
	printf("\n5 est dans A ?\n");
	parcours(recherche_p(5,A));
	return 0;
}
