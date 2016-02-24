
// TD2 ALG, Arbres 234
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

Arbre test_bidon(void){
	Arbre A;
	A = malloc(sizeof(Noeud));
	A->nb = 2;
	A->cle[0] = 5;
	A->cle[1] = 12;
	A->enfant[0] = malloc(sizeof(Noeud));
	A->enfant[1] = malloc(sizeof(Noeud));
	A->enfant[2] = malloc(sizeof(Noeud));
	A->enfant[0]->nb = 1;
	A->enfant[0]->cle[0] = 3;
	A->enfant[0]->enfant[0] = NULL;
	A->enfant[0]->enfant[1] = NULL;
	A->enfant[1]->nb = 2;
	A->enfant[1]->cle[0] = 8;
	A->enfant[1]->cle[1] = 11;
	A->enfant[1]->enfant[0] = NULL;
	A->enfant[1]->enfant[1] = NULL;
	A->enfant[1]->enfant[2] = NULL;
	A->enfant[2]->nb = 1;
	A->enfant[2]->cle[0] = 15;
	A->enfant[2]->enfant[0] = NULL;
	A->enfant[2]->enfant[1] = NULL;
	
	return A;
}

Arbre test_eclat(void){
	Arbre A;
	A = malloc(sizeof(Noeud));
	A->nb = 3;
	A->cle[0] = 5;
	A->cle[1] = 12;
	A->cle[2] = 23;
	A->enfant[0] = malloc(sizeof(Noeud));
	A->enfant[1] = malloc(sizeof(Noeud));
	A->enfant[2] = malloc(sizeof(Noeud));
	A->enfant[3] = malloc(sizeof(Noeud));
	A->enfant[0]->nb = 1;
	A->enfant[0]->cle[0] = 3;
	A->enfant[0]->enfant[0] = NULL;
	A->enfant[0]->enfant[1] = NULL;
	A->enfant[1]->nb = 2;
	A->enfant[1]->cle[0] = 8;
	A->enfant[1]->cle[1] = 11;
	A->enfant[1]->enfant[0] = NULL;
	A->enfant[1]->enfant[1] = NULL;
	A->enfant[1]->enfant[2] = NULL;
	A->enfant[2]->nb = 1;
	A->enfant[2]->cle[0] = 15;
	A->enfant[2]->enfant[0] = NULL;
	A->enfant[2]->enfant[1] = NULL;
	A->enfant[3]->nb = 1;
	A->enfant[3]->cle[0] = 25;
	A->enfant[3]->enfant[0] = NULL;
	A->enfant[3]->enfant[1] = NULL;
	
	return A;
}

// Parcoure l'abre en ordre infixé (pour un affichage dans l'ordre croissant
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

// Renvoie vrai si la clé se trouve dans l'arbre
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

// Renvoie le noeud dans lequel se trouve la clé
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

// Eclater les noeuds de taille 3 !
void eclaterNoeud(Arbre A, Arbre P){
	if(A->nb == 3){
		
		Arbre nga;
		Arbre ndr;
		
		// Recupére la 3eme valeur et ses fils
		ndr = malloc(sizeof(Noeud));
		ndr->nb = 1;
		ndr->cle[0] = A->cle[2];
		ndr->enfant[0] = A->enfant[2];
		ndr->enfant[1] = A->enfant[3];
			
		if(P == NULL){//Eclatement racine
			
			// Crée le noeud gauche, en mettant A en haut
			nga = malloc(sizeof(Noeud));
			nga->nb = 1;
			nga->cle[0] = A->cle[0];
			nga->enfant[0] = A->enfant[0];
			nga->enfant[1] = A->enfant[1];
			
			// Modifie le noeud A
			A->cle[0] = A->cle[1];
			A->enfant[0]=nga;
			A->enfant[1]=ndr;
			A->enfant[2] = NULL;
			A->enfant[3] = NULL;
			A->nb=1;
			
		}
		else{ // Eclatement avec insertion en P (supposant P de taille <=2)
			int i,j;
			int cle = A->cle[1];
			A->nb = 1;
			A->enfant[2] = NULL;
			A->enfant[3] = NULL;
			
			i=0;
			while(cle<P->cle[i])i++;
			for(j=P->nb;j>=i;j--){
				P->cle[j]=P->cle[j-1];
				P->enfant[j+1]=P->enfant[j];
			}
			P->nb = P->nb + 1;
			P->cle[i]=cle;
			P->enfant[i]=A;
			P->enfant[i+1]=ndr;
			
		}
		
	}
	
}

int *insereCleNoeud(int cle, int nb, int tab[]) {
	int i, j;
	for(i = 0; i < 3; i++) {
		if(i > nb) {
			tab[i] = cle;
			return tab;
		} else {
			if(cle < tab[i]) {
				for(j=i; j < 3; j++) {
					tab[j] = tab[j-1];
				}
				tab[i] = cle;
				return tab;
			}
		}
	}
}

// insérer un élément dans un Arbre
void insertion (int cle, Arbre A, Arbre P){
	int i;

	// Si le noeud n'a pas d'élément, on ne peut pas descendre plus loin, donc on insère
	if(A == NULL) {
		A = malloc(sizeof(Noeud));
		A->nb = 1;
		A->cle[0] = cle;
	} else {
			
		// Eclatement si le noeud comporte 3 éléments
		if(A->nb == 3) eclaterNoeud(A,P);

		if(A->nb < 3) {
			insereCleNoeud(cle,A->nb,A->cle);
		} else {		
			for (i = 0; i < A->nb; i++) {
				if(cle < A->cle[i]) insertion(cle, A->enfant[i], A);
			}
		}
	}	
	
}

Arbre creer_arbre(){
	int cle;
	Arbre A = NULL;
	printf("Création d'un arbre. Pour arreter, entrez un entier négatif.\n");
	do{
		printf("Cle à insérer : ");
		scanf("%d",&cle);
		//insertion(cle,A,NULL);
	}while(cle>0);
	return A;
}

// Hauteur en recupérant le maximum des hauteurs de chaque sous arbres
int hauteur_naive(Arbre A){
	int i;
	int max, courant;
	if (A == NULL) return 0;
	else {
		max = hauteur_naive(A->enfant[0]);
		for(i=1;i<=A->nb;i++){
			courant = hauteur_naive(A->enfant[i]);
			if(courant > max) max = courant;
		}
		return 1+max;
	}
}

// Hauteur considérant que toutes les feuilles sont au même niveau
int hauteur(Arbre A){
	
	if (A == NULL) return 0;
	else {
		return 1+hauteur(A->enfant[0]);
	}
}

int main(void) {
	Arbre A = test_eclat();
	parcours(A);
	printf("\n3 est dans A : %d\n",recherche_b(3,A));
	printf("8 est dans A : %d\n",recherche_b(8,A));
	printf("3 est dans A ?\n");
	parcours(recherche_p(3,A));
	printf("\n8 est dans A ?\n");
	parcours(recherche_p(8,A));
	printf("\n5 est dans A ?\n");
	parcours(recherche_p(5,A));
	
	printf("\nhauteur A : %d\n A != NULL : %d\n",hauteur(A), A!=NULL);
	eclaterNoeud(A,NULL);
	parcours(A);
	printf("\nhauteur A : %d\n A != NULL : %d\n",hauteur(A), A!=NULL);
	
	return 0;
}
