CC = gcc -g -O3 -march=native
CGLAGS = -Wall -I
DEPS = global.h produtos_read_write.h clientes_read_write.h vendas_read_write.h avlstruct.h hashtables.h
OBJ = main.o global.o produtos_read_write.o clientes_read_write.o vendas_read_write.o avlstruct.o hashtables.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lm

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	rm main *.o
