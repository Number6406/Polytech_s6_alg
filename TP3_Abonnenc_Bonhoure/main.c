/*
 * main.c
 * 
 * Copyright 2016 Alicia Abonnenc <alicia@alicia-X550CC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include "graphe2.h"


int main(int argc, char **argv)
{	
	pnoeud_t graphe = NULL;
	//graphe = creer_graphe();

	if(argc < 2) { printf("erreur de lecture : pas de nom indiqué"); return 1; }
	lire_graphe(&graphe, argv[1]);
	
	affGraphe(graphe);
	
	
	printf("Nombre d'arcs : %d\n", nombre_arcs(graphe));
	printf("Nombre de noeuds : %d\n", nbNoeudGraphe(graphe));
	printf("Dégré du graphe : %d\n", degre_graphe(graphe));
	printf("Indépendant ? %d\n", independant(graphe));
	printf("Complet ? %d\n", complet(graphe));
	
	affGraphe(graphe);
	
	profondeur(graphe);
	parcours_largeur(graphe);
	
	return 0;
}

