-- packages utlisés
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with arbres; use arbres;

procedure test_abr is
	A : abr;
	T : tab;
begin
	for i in 1..20 loop T.T(i) := (2*i+6) mod 27; end loop;
	T.L := 20;
	A := init_abr(T);
	aff_abr(A);
	ajouter_cle(A,5);
	aff_abr(A);
	put("Hauteur de l'arbre : "); put(hauteur(A),2); new_line;
	put("Nombre de noeuds internes : "); put(nbNoeuds(A),2); new_line;
	put("Nombre de feuilles : "); put(nbFeuilles(A),2); new_line;
	put("Somme des clés : "); put(somme(A),2); new_line;
	put("Arbre tourné à droite : "); new_line;
	rotationD(A);
	aff_abr(A);
	put("Arbre tourné à gauche : "); new_line;
	rotationG(A);
	aff_abr(A); 
	put("Arbre équilibré : "); new_line;
	equilibrer(A);
	aff_abr(A);
	put("Hauteur de l'arbre : "); put(hauteur(A),2); new_line;
	put_line("---------------");
	put_line("Affichage de l'arbre équilibré : ");
	aff(A,"");
	liberer_abr(A);
end test_abr;
