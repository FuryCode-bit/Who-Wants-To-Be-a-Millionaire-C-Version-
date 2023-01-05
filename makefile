.PHONY: clean

trabalho : trabalho.o funcionalidades.o
	gcc -o trabalho trabalho.o funcionalidades.o
	rm *.o
    
funcionalidades.o : funcionalidades.c
	gcc -c funcionalidades.c

trabalho.o : trabalho.c funcionalidades.h
	gcc -c trabalho.c
