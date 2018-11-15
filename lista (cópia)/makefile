all: comprime descomprime

descomprime: desc_codigo.o comprime.c
	c99 desc_codigo.o descomprime.c -o descomprime -g

comprime: arvore.o lista.o codigo.o comprime.c
	c99 arvore.o lista.o codigo.o comprime.c -o comprime -g

arvore.o: arvore.c arvore.h
	c99 -c arvore.c

lista.o: lista.c lista.h arvore.h
	c99 -c lista.c

codigo.o: arvore.h lista.h codigo.h codigo.c
	c99 -c codigo.c

clean:
	rm -rf *.o *~ comprime descomprime
