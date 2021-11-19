CC=gcc
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=src
HEADDIR=include
BINDIR=bin
 
# compilation option
CFLAGS= -I $(HEADDIR) -g -Wall -ansi
# LIB
GLLIBS = -lMLV -lm
 
# Where to find *.c
SRC= $(wildcard $(SRCDIR)/*.c)
OBJ= $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

# create executable
projet: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(GLLIBS)

# Create *.o from *.c
$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

# clean everything -> bin file and executable
clean: 
	rm -f $(BINDIR)/* projet
