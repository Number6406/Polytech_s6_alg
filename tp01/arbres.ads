-- packages utilisées
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

package arbres is
   
	--Définition du type ABR, Arbre Binaire de Recherche
	type noeud;
	type abr is access noeud;
	type noeud is record
		cle : integer;
		gauche : abr;
		droit : abr;
	end record;
	
	type inttab is array (1..500) of integer;
	
	type tab is record
		T : inttab;
		L : integer;
	end record;
	
	-- creer un arbre vide
	function creer_abr return abr;
	
	-- ajouter une clé à un abr déjà existant
	procedure ajouter_cle ( A : in out abr; cle : in integer );
	
	--crée un abr à partir d'un tableau d'entiers et de la longueur de ce tableau
	function init_abr (T : tab) return abr;
	
	-- supprimer un abr
	procedure liberer_abr ( A : in out abr);
	
	-- afficher un abr
	procedure aff_abr ( A : in abr);
	
	-- retourne la hauteur de l'arbre A
	function hauteur (A: abr) return integer;
	
	-- renvoie le nombre de noeuds internes à l'abr
	function nbNoeuds ( A : abr) return integer;
	
	-- renvoie le nombre de feuilles de l'abr
	function nbFeuilles ( A : abr) return integer;
	
	-- Calcule la somme des clés de l'ABR
	function somme (A : abr) return integer;
	
	-- tourne l'abr (s'il est tournable) vers la droite
	procedure rotationD (A : in out abr);
	
	-- tourne l'abr (s'il est tournable) vers la gauche
	procedure rotationG (A : in out abr);
	
	-- equilibre (au mieux) un abr
	procedure equilibrer ( A : in out abr);
	
	-- affichage de l'arbre
	procedure aff (A : in abr ; s : in String );
	
end arbres;
