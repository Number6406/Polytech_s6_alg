
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
		
		Arbre racine;
		Arbre nd;
		
		// Recupére la 3eme valeur et ses fils
		nd = malloc(sizeof(Noeud));
		nd->nb = 1;
		nd->cle[0] = A->cle[2];
		nd->enfant[0] = A->enfant[2];
		nd->enfant[1] = A->enfant[3];
			
		if(P==NULL){//Eclatement racine
			
			// Crée le noeud racine, en mettant A à gauche
			racine = malloc(sizeof(Noeud));
			racine->nb = 1;
			racine->cle[0] = A->cle[1];
			racine->enfant[0] = A;
			racine->enfant[1] = nd;
			
			// Modifie le noeud A
			A->nb=1;
			A->enfant[2] = NULL;
			A->enfant[3] = NULL;
			
			// Renvoie la racine via A
			A = racine;
		}
		else{ // Eclatement avec insertion en P (supposant P de taille <=2)
			int i,j;
			int cle = A->cle[1];
			A->nb = 1;
			
			i=0;
			while(cle<P->cle[i])i++;
			for(j=P->nb;j>=i;j--){
				P->cle[j]=P->cle[j-1];
				P->enfant[j+1]=P->enfant[j];
			}
			P->nb = P->nb + 1;
			P->cle[i]=cle;
			P->enfant[i]=A;
			P->enfant[i+1]=nd;
			
			
			
			
			
		}
		
	}
	
}


// insérer un élément dans un Arbre
void insertion (int cle; Arbre A; Arbre parent){
	int i, j;
	
	
	if(est_feuille(A)){
		if(A->nb=1){
			nb=2;
			if(A->cle[0]<cle){
				A->cle[1]=cle;
			}
			else{
				A->cle[1] = A->cle[2];
				A->cle[0]=cle;
			}
		}
		else if(A->nb=2){
			
		}
		else{
			
		}
	}
	else
}

int main(void) {
	Arbre A = test_bidon();
	parcours(A);
	printf("\n3 est dans A : %d\n",recherche_b(3,A));
	printf("8 est dans A : %d\n",recherche_b(8,A));
	printf("3 est dans A ?\n");
	parcours(recherche_p(3,A));
	printf("8 est dans A ?\n");
	parcours(recherche_p(8,A));
	printf("5 est dans A ?\n");
	parcours(recherche_p(5,A));
	return 0;
}
