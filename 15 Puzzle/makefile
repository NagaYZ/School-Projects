CC = gcc
CFLAGS = -Wall -ansi -g -lMLV
OBJ=main.o graphique.o plateau.o

taquin: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.c graphique.h plateau.h
	$(CC) -c $< $(CFLAGS)

graphique.o: graphique.c graphique.h plateau.h
	$(CC) -c $< $(CFLAGS)

plateau.o: plateau.c plateau.h
	$(CC) -c $< $(CFLAGS)

clean: 
	rm -f *.o taquin