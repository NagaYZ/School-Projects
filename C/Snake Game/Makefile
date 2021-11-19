CC=gcc
CFLAGS=-ansi -Wall -lncurses
OBJ=Main.o Monde.o Affichage.o Pomme.o Serpent.o

Snake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

Main.o: Main.c Monde.h Affichage.h
	$(CC) -c $< $(CFLAGS)

Monde.o: Monde.c Serpent.h Pomme.h Case.h Direction.h
	$(CC) -c $< $(CFLAGS)

Affichage.o: Affichage.c Monde.h Serpent.h Pomme.h Direction.h Case.h
	$(CC) -c $< $(CFLAGS)

Pomme.o: Pomme.c Case.h
	$(CC) -c $< $(CFLAGS)

Serpent.o: Serpent.c Direction.h Case.h
	$(CC) -c $< $(CFLAGS)
