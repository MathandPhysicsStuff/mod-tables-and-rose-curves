#set noexpandtab

CC = gcc

CFLAGS = -O2 -lm -lSDL2 -lSDL2main -lSDL2_ttf 

all: bin

bin: main.o functions.o text.o
	$(CC) $(CFLAGS) main.o functions.o text.o -o bin

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c

text.o: text.c
	$(CC) $(CFLAGS) -c text.c

clean:
	rm -f *.o



