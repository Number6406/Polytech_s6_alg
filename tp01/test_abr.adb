-- packages utlisés
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with arbres; use arbres;

procedure test_abr is
	A : abr;
	T : tab;
	choix : integer := 0;
begin
	put_line("Programme de manipulation d'Arbres Binaires de Recherche.");
	put_line("Que voulez vous faire ?");
	put_line("1 - Creer un arbre.");
	put_line("2 - Equilibrer un arbre déséquilibré à droite.");
	put_line("3 - Equilibrer un arbre déséquilibré à gauche.");
	put_line("4 - Tourner un arbre quelconque.");
	while(choix < 1 or choix > 4) loop
		get(choix);
	end loop;
	put_line("------------------------");
	case choix is
		when 1 =>
			put("Taille ? ");get(T.L);
			for i in 1..T.L loop
				put("Ajouter : ");
				get(T.T(i));
			end loop;
			A := init_abr(T);
			aff_abr(A);
			info_abr(A);
			put("Arbre équilibré : "); new_line;
			equilibrer(A);
			aff_abr(A);
			info_abr(A);
		when 2 =>
			for i in 1..30 loop T.T(i) := i; end loop;
			T.L := 30;
			A := init_abr(T);
			aff_abr(A);
			info_abr(A);
			put("Arbre équilibré : "); new_line;
			equilibrer(A);
			aff_abr(A);
			info_abr(A);
		when 3 =>
			for i in 1..30 loop T.T(i) := 30-i; end loop;
			T.L := 30;
			A := init_abr(T);
			aff_abr(A);
			info_abr(A);
			put("Arbre équilibré : "); new_line;
			equilibrer(A);
			aff_abr(A);
			info_abr(A);
		when 4 =>
			T.T := (9,3,2,1,5,4,7,8,6,10,others=>0);
			T.L := 10;
			A := init_abr(T);
			aff_abr(A);
			info_abr(A);
			put("Arbre tourné à droite : "); new_line;
			rotationD(A);
			aff_abr(A);
			put("Arbre tourné à gauche : "); new_line;
			rotationG(A);
			rotationG(A);
			aff_abr(A);
		when others => put_line("Erreur lors du choix.");
	end case;
	liberer_abr(A);
end test_abr;
