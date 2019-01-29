CC=gcc
CFLAGS=-I.

all:
	$(CC) -o midifreq midifreq.c -lm -Wall
	$(CC) -o nscale nscale.c scale.c -lm -Wall
	$(CC) -o expbrk expbrk.c -lm -Wall
	$(CC) -o sinetext sinetext.c -lm -Wall
	$(CC) -o tfork tfork2.c -lm -Wall
	$(CC) -o tforkraw tforkraw.c -lm -Wall
clean:
	rm -f ./*.txt
	rm -f ./*.raw
	rm -f midifreq
	rm -f nscale
	rm -f expbrk
	rm -f sinetext
	rm -f tfork
	rm -f tforkraw
