# Makefile TP Flex

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall -lfl -ly
BISONFLAGS =  -d
EXEC=as

$(EXEC): lex.yy.c $(EXEC).tab.c $(EXEC).tab.h
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).tab.c $(EXEC).tab.h: $(EXEC).y
	bison $(BISONFLAGS) $(EXEC).y

%.o: %.c
	$(CC) -o $@ -c $< $(LDFLAGS)

lex.yy.c: $(EXEC).lex $(EXEC).tab.h
	flex $(EXEC).lex

clean:
	rm -f $(EXEC) *.[o] *.txt