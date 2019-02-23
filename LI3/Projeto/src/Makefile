CC = gcc
CGLAGS = -Wall -I
DEPS = ler.h
OBJ = main.o ler.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lm

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

perm:
	sudo chmod 777 datafiles/

clean:
	rm main *.o
