-- packages utilisés
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Unchecked_Deallocation;

package body arbres is
	
	-- creer un arbre vide
	function creer_abr return abr is
	begin
		return Null;
	end creer_abr;
	
	-- procedure de désallocation d'une case mémoire contenant un noeud
	procedure free is new Ada.Unchecked_Deallocation (noeud, abr);
	
	-- ajouter une clé à un abr déjà existant
	procedure ajouter_cle ( A : in out abr; cle : in integer ) is
		N : abr;
	begin
		if A = Null then 
			-- On crée la case mémoire pour la clé donnée
			N := new noeud;
			N.all.cle := cle;
			N.all.gauche := Null;
			N.all.droit := Null;
			A := N;
			
		else 
			if cle < A.all.cle then
				ajouter_cle(A.all.gauche,cle);
			else
				ajouter_cle(A.all.droit,cle);
			end if;
			
		end if;
				
	end ajouter_cle;
	
	--crée un abr à partir d'un tableau d'entiers et de la longueur de ce tableau
	function init_abr (T : tab) return abr is
		A : abr;
	begin
		A := creer_abr;
		for i in 1..T.L loop
			ajouter_cle(A,T.T(i));
		end loop;
		return A;
	end init_abr;
	
	-- supprimer un abr
	procedure liberer_abr ( A : in out abr) is
	begin
		if A /= Null
		then 
			liberer_abr (A.all.gauche);
			liberer_abr (A.all.droit);
			free(A);
		end if;
	end liberer_abr;
	
	procedure aff_racine (A : abr) is
	begin
		if A /= Null then
			put(A.all.cle,2);
		end if;
	end aff_racine;
	
	-- afficher un abr (aff infixé)
	procedure aff_abr ( A : in abr) is
		procedure aux ( A : in abr) is
		begin
			if A /= Null
			then
				aux(A.all.gauche);
				put(A.all.cle,3);
				aux(A.all.droit);
			end if;
		end aux;
		
	begin
		aux(A);new_line;
	end aff_abr;
	
	function max (x,y : integer) return integer is
	begin
		if x < y 
		then return y; 
		else return x; 
		end if;
	end max;
	
	-- hauteur de l'arbre A
	function hauteur (A: abr) return integer is
	begin
		if A = Null
		then return 0;
		else return 1+max(hauteur(A.all.gauche),hauteur(A.all.droit));
		end if;
	end hauteur;
	
	-- renvoie le nombre de noeuds internes à l'abr
	function nbNoeuds ( A : abr) return integer is
	begin
		if A = Null 
			then return 0;
			else if A.all.gauche = Null and A.all.droit = Null
				then return 0;
				else return 1 + nbNoeuds(A.all.gauche) + nbNoeuds(A.all.droit);
			end if;
		end if;
	end nbNoeuds;
	
	-- renvoie le nombre de feuilles de l'abr
	function nbFeuilles ( A : abr) return integer is
	begin
		if A = Null 
			then return 0;
			else if A.all.gauche = Null and A.all.droit = Null
				then return 1;
				else return nbFeuilles(A.all.gauche) + nbFeuilles(A.all.droit);
			end if;
		end if;
	end nbFeuilles;
	
	-- Calcule la somme des clés de l'ABR
	function somme (A : abr) return integer is
	begin
		if A = Null 
			then return 0;
			else return A.all.cle + somme(A.all.gauche) + somme(A.all.droit);
		end if;
	end somme;
	
	-- tourne l'abr (s'il est tournable) vers la droite
	procedure rotationD (A : in out abr) is
		B,G : abr;
	begin
		if A /= Null then
			G := A.all.gauche;
			if G /= Null then
				B := G.all.droit;
				G.all.droit := A;
				A.all.gauche := B;
				A := G;
			end if;	
		end if;
	end rotationD;
	
	-- tourne l'abr (s'il est tournable) vers la gauche
	procedure rotationG (A : in out abr) is
		B,D : abr;
	begin
		if A /= Null then
			D := A.all.droit;
			if D /= Null then
				B := D.all.gauche;
				D.all.gauche := A;
				A.all.droit := B;
				A := D;
			end if;	
		end if;
	end rotationG;
	
	-- equilibre (au mieux) un abr
	procedure equilibrer ( A : in out abr) is
		HG, HD : integer;
	begin
		if A /= Null then
			equilibrer (A.all.gauche);
			equilibrer (A.all.droit);
			HD := hauteur(A.all.droit);
			HG := hauteur(A.all.gauche);
			if HD + 1 < HG then rotationD(A); end if;
			if HG + 1 < HD then rotationG(A); end if;
		end if;
	end equilibrer;
	
	-- affichage de l'arbre
	procedure aff (A : in abr ; s : in String ) is
		hg, hd : integer;
	begin
		if (A /= NULL) then 
			if (A.all.gauche /= NULL) then
				aff(A.all.gauche, s & "    ");
			end if;
			put(s); aff_racine(A); if ( A.all.droit /= NULL or else A.all.gauche /= NULL ) then put("<"); end if;
			new_line;
			if (A.all.droit /= NULL) then
				aff(A.all.droit, s & "    ");
			end if;
		end if;
	end aff;
	
end arbres;
