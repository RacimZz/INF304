CC = clang

all: ensembles

ensembles.o: ensembles.c operations_ens.h sac.h
	$(CC) -c ensembles.c

sac.o: sac.c sac.h
	$(CC) -c sac.c

operations_ens.o: operations_ens.c operations_ens.h sac.h
	$(CC) -c operations_ens.c

ensembles: ensembles.o sac.o operations_ens.o
	$(CC) ensembles.o sac.o operations_ens.o -o ensembles

clean:
	rm -f ensembles *.o
