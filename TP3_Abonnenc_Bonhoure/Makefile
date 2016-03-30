CC = gcc
EXEC = main graphe1
CFLAGS = -Wall
SRCS = main.c graphe2.c graphe1.c
OBJS = $(SRCS:.c=.o)



all : $(EXEC)

main : main.o graphe2.o
	-@echo Creation de "l'executable" $@
	$(CC) main.o graphe2.o -o main
