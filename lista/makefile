all: teste
debug: deb

deb: arvore.o lista.o codigo.o comprime.c
	c99 arvore.o lista.o codigo.o comprime.c -o deb -g

teste: arvore.o lista.o codigo.o comprime.c
	c99 arvore.o lista.o codigo.o comprime.c -o teste

arvore.o: arvore.c arvore.h
	c99 -c arvore.c

lista.o: lista.c lista.h arvore.h
	c99 -c lista.c

codigo.o: arvore.h lista.h codigo.h codigo.c
	c99 -c codigo.c

clean:
	rm -rf *.o *~ teste deb
