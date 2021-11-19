CC=gcc
CFLAGS=-ansi -Wall -lncurses -lm
OBJ=main.o echiquier.o attaque.o graphique.o

Dame: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.c echiquier.h graphique.h
	$(CC) -c $< $(CFLAGS)

echiquier.o: echiquier.c echiquier.h
	$(CC) -c $< $(CFLAGS)

attaque.o: attaque.c attaque.h echiquier.h
	$(CC) -c $< $(CFLAGS)

graphique.o: graphique.c graphique.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f Dame
