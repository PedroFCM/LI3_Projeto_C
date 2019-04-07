CC = gcc -ansi -g -Ofast -march=native -Wall
CGLAGS = -I
DEPS = $(wildcard *.h)
OBJ = $(patsubst %.c,%.o,$(wildcard *.c))

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lm
	
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

doc:
	mkdir doc
	doxygen Doxygen
	mv html/ latex/ doc/

removedoc:
	rm -r doc/

remvalidtext:
	rm validData/*.txt

clean:
	rm main *.o