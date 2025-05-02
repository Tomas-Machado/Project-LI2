CC = gcc
CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: game.o geracaomapa.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm jogo *.o
