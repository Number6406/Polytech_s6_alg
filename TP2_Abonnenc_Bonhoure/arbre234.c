
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

// Parcoure l'abre en ordre infixé (pour un affichage dans l'ordre croissant
void parcours(Arbre A){
	
	void aux(Arbre A){
		int i;
		if (A != NULL){
			for(i=0; i < A->nb;i++){
				aux(A->enfant[i]);
				printf("[%d,%d] ",A->cle[i],hauteur_naive(A));
			}
			aux(A->enfant[i]);
		}
	}
	
	aux(A);
	printf("\n");
}

// Affiche le contenu d'un noeud
void aff_noeud(Arbre A){
	int i;
	for (i=0; i<A->nb;i++){
		printf("%d ",A->cle[i]);
	}
	printf("\n");
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
Arbre eclaterNoeud(Arbre A, Arbre P){
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
			
			return A;
		}
		else{ // Eclatement avec insertion en P (supposant P de taille <=2)
			int i,j;
			int cle = A->cle[1]; // Recupération de la clé du milieu de l'arbre
			// Garde la clé de gauche dans l'arbre A et ses deux fils
			A->nb = 1;
			A->enfant[2] = NULL;
			A->enfant[3] = NULL;
			
			// Insertion en P au bon endroit
			
			i=0;
			while(i<P->nb && cle > P->cle[i])i++; // Avancer tant que la clé est plus grande
			
			//décaler les clefs et les enfants vers la droite
			for(j=P->nb;j>i;j--){
				P->cle[j]=P->cle[j-1];
				P->enfant[j+1]=P->enfant[j];
			}
			P->nb = P->nb + 1;
			P->cle[i]=cle;
			P->enfant[i]=A;
			P->enfant[i+1]=ndr;
			
			return P;
		}
		
	}
	return A;
	
}

// Insére une clé dans un noeud FEUILLE !
void insereCleNoeud(int cle, Arbre A) {
	int i, j;
		
	i=0;
	while(i<A->nb && cle > A->cle[i] )i++; // Avancer tant que la clé est plus grande
	//décaler les clefs vers la droite
	for(j=A->nb;j>i;j--){
		A->cle[j]=A->cle[j-1];
	}
	A->nb = A->nb + 1;
	A->cle[i]=cle;
	for(i=0;i<=A->nb;i++) {A->enfant[i]=NULL;}
}


int est_feuille(Arbre A){
	int b,i;
	b = (A!=NULL);
	for(i=0;i<=A->nb;i++){
		b = b && (A->enfant[i]==NULL);
	}
	return b;
}

// insérer un élément dans un Arbre
void insertion (int cle, Arbre A, Arbre P){

	// Si le noeud n'a pas d'élément, on ne peut pas descendre plus loin, donc on insère
	if(A == NULL) {
		printf("coucou Je suis un arbre null ! \n");
		A = malloc(sizeof(Noeud));
		A->nb = 1;
		A->cle[0] = cle;
		A->enfant[0]=NULL;
		A->enfant[1]=NULL;
		parcours(A);
		printf("\n");
	} 
	else {
		// Eclatement du noeud courant si le noeud comporte 3 éléments
		if(A->nb == 3){
			 A = eclaterNoeud(A,P);
			 insertion(cle,A,NULL);
		}
		else if(est_feuille(A)) {
			insereCleNoeud(cle,A);
		} 
		else {
			if(A->nb==1){
				if(cle < A->cle[0]) insertion(cle,A->enfant[0],A);
				else insertion(cle,A->enfant[1],A);
			}
			else if (A->nb==2){
				if(cle < A->cle[0]) insertion(cle,A->enfant[0],A);
				else {
					if(cle < A->cle[1]) insertion(cle,A->enfant[1],A);
					else insertion(cle,A->enfant[2],A);
				}
			}
			else{	
				printf("Erreur de taille de noeud. Noeud non éclaté en chemin ! \n");
			}
		}
	}	
	
}

// Crée un arbre avec des entrées au clavier
Arbre creer_arbre(){
	int cle;
	Arbre A;
	printf("Création d'un arbre. Pour arreter, entrez un entier négatif.\n");
	printf("Cle à insérer : ");
	scanf("%d",&cle);
	A=malloc(sizeof(Noeud));
	A->nb=1;
	A->cle[0]=cle;
	A->enfant[0]=NULL;
	A->enfant[1]=NULL;
	
	printf("Cle à insérer : ");
	scanf("%d",&cle);
		
	while(cle>0) {
		insertion(cle,A,NULL);
		parcours(A);
		printf("Cle à insérer : ");
		scanf("%d",&cle);
	}
	
	return A;
}

// Libérer un Arbre
void liberer(Arbre A){
	if(A!=NULL){
		int i;
		for (i=0; i <= A->nb; i++){
			liberer(A->enfant[i]);
		}
		free(A);
	}
}

// Calcule le nombre d'éléments d'un arbres 2-3-4
int nbElem(Arbre A) {
	if(A == NULL) return 0;
	else {
		int i;
		int nbCourr = A->nb;
		for(i = 0; i <= A->nb; i++) {
			nbCourr += nbElem(A->enfant[i]);
		}
		return nbCourr;
	}
}

void aff(Arbre A) {
	int i;
	if (A != NULL){
		for(i=0; i < A->nb;i++){
			printf("%d ",A->cle[i]);
		}
		for(i=0; i<=A->nb; i++) {
			aff(A->enfant[i]);
			printf("|");
		}
		
		printf("\n");
	}
}

void actionArbre(Arbre A) {
	int sc = 0;
	do {
		printf("===============================\n");
		printf("Actions à effectuer sur l'Arbre\n");
		printf("===============================\n");
		printf("1 : Insérer une clé\n");
		printf("2 : Supprimer une clé\n");
		printf("3 : Afficher l'arbre\n");
		printf("4 : Trouver une clé\n");
		printf("5 : Afficher la hauteur de l'arbre\n");
		printf("6 : Afficher le nombre d'éléments de l'arbre\n");
		printf("0 : Quitter\n");
		
		scanf("%d",&sc);
		
		switch(sc) {
			int cle;
			case 1 :
				printf("Choix de la clé à insérer : \n");
				scanf("%d",&cle);
				insertion(cle, A, NULL);
				break;
			case 2 :
				printf("Choix de la clé à supprimer : \n");
				scanf("%d",&cle);
				//TODO fonction suppression
				break;
			case 3 : parcours(A); break;
			case 4 :
				printf("Choix de la clé à rechercher : \n");
				scanf("%d",&cle);
				recherche_p(cle, A);
				break;
			case 5 : printf("Hauteur de l'arbre A : %d\n",hauteur(A)); break;
			case 6 : printf("Nombre d'éléments de l'arbre A : %d\n",nbElem(A)); break;
		}
		
	} while(sc);
}

void arbreMain() {
	Arbre A = creer_arbre();
	actionArbre(A);
}

void programme() {
	int sc = 0;
	
	printf("Bienvenue dans ce programme de test, permettant d'effectuer des opérations sur un arbre 2-3-4");
	
	do {
		printf("Choisir quoi faire parmis les choix suivants : \n");
		printf("1 : Créer un arbre depuis un fichier\n");
		printf("2 : Créer un arbre à la main\n");
		printf("0 : Quitter\n");
		
		scanf("%d", &sc);
		
		switch(sc) {
			case 1 : break;//TODO
			case 2 : arbreMain(); break;
		}
	} while(sc);
}

int main(void) {
	programme();
	return 0;
}

/*
 Arbre A = test_eclat();
	
	printf("L'arbre est composé de %d éléments.\n", nbElem(A));
	aff(A);
	
	parcours(A);
	printf("\n3 est dans A : %d\n",recherche_b(3,A));
	printf("8 est dans A : %d\n",recherche_b(8,A));
	printf("3 est dans A ?\n");
	aff_noeud(recherche_p(3,A));
	printf("8 est dans A ?\n");
	aff_noeud(recherche_p(8,A));
	printf("5 est dans A ?\n");
	aff_noeud(recherche_p(5,A));
	
	printf("\nTest Hauteur \nhauteur A : %d\n A != NULL : %d\n",hauteur(A), A!=NULL);
	
	printf("\nTest éclatement\nracine avant éclatement : ");
	aff_noeud(A);
	eclaterNoeud(A,NULL);
	printf("racine après éclatement : ");
	aff_noeud(A);
	parcours(A);
	printf("\nNouvelle hauteur de A : %d\n",hauteur(A));
	
	// Recherches OK. Eclatement de la racine OK.
	// Reste à tester l'insertion
	
	// TEST insertion clé noeud
	Arbre N;
	N=malloc(sizeof(Noeud));
	N->nb=2;
	N->cle[0]=5;
	N->cle[1]=10;
	N->enfant[0]=NULL;
	N->enfant[1]=NULL;
	N->enfant[2]=NULL;
	insereCleNoeud(12,N);
	
	printf("L'arbre est composé de %d éléments.\n", nbElem(N));
	
	aff_noeud(N);
	printf("est feuille ? %d\n",est_feuille(N));
	
	// TEST insertion dans un arbre
	insertion(7,N,NULL);
	parcours(N);
	insertion(53,N,NULL);
	parcours(N);
	
	printf("AUTRE ARBRE\n");
	parcours(A);
	insertion(22,A,NULL);
	parcours(A);
	A=NULL;
	insertion(5,A,NULL);
	parcours(A);
	
	Arbre B;
	//B=creer_arbre();
	printf("B NULL ? : %d",B==NULL);
	parcours(B);
	
	printf("libA\n");
	liberer(A);
	printf("libN\n");
	liberer(N);
	printf("libB\n");
	liberer(B);
	return 0;
*/
