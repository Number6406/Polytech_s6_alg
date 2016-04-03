CC = gcc
EXEC = main graphe1
CFLAGS = -Wall
SRCS = main.c graphe.c graphe1.c dijkstra.c grapheio.c
OBJS = $(SRCS:.c=.o)



all : $(EXEC)

main : main.o graphe.o grapheio.o dijkstra.o
	-@echo Creation de "l'executable" $@
	$(CC) main.o graphe.o grapheio.o dijkstra.o -o main

clean :
	@echo Suppression des fichiers objets
	rm *.o
