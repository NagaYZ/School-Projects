CC=gcc
CFLAGS=-ansi -Wall -lncurses -lm
OBJ=Main.o Jeu.o Affichage.o Dico.o Grille.o Test.o

Boggle: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

Main.o: Main.c Jeu.h Affichage.h
	$(CC) -c $< $(CFLAGS)

Grille.o: Grille.c Grille.h
	$(CC) -c $< $(CFLAGS)

Jeu.o: Jeu.c Jeu.h Grille.h Dico.h
	$(CC) -c $< $(CFLAGS)

Affichage.o: Affichage.c Affichage.h Grille.h
	$(CC) -c $< $(CFLAGS)

Dico.o: Dico.c Dico.h
	$(CC) -c $< $(CFLAGS)

Test.o: Test.c Test.h Grille.h Jeu.h Dico.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f Boggle
