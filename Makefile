# Makefile for L8T1

#projekti: Bintree.o 
# Pääohjelma
projekti: L8T1.o L8T1Kirjasto.o TilastoFaktatKirjasto.o MergeSortLaskevaJKirjasto.o MergeSortNousevaJKirjasto.o Bintree.o
	gcc -o projekti L8T1.o L8T1Kirjasto.o TilastoFaktatKirjasto.o MergeSortLaskevaJKirjasto.o MergeSortNousevaJKirjasto.o Bintree.o

# Pääohjelman objektitiedosto
L8T1.o: L8T1.c L8T1Kirjasto.h TilastoFaktatKirjasto.h MergeSortLaskevaJKirjasto.h MergeSortNousevaJKirjasto.h Bintree.h
	gcc -c L8T1.c -std=c99 -pedantic -Wall

# Kirjaston objektitiedosto
L8T1Kirjasto.o: L8T1Kirjasto.c L8T1Kirjasto.h TilastoFaktatKirjasto.h MergeSortLaskevaJKirjasto.h MergeSortNousevaJKirjasto.h
	gcc -c L8T1Kirjasto.c -std=c99 -pedantic -Wall

# TilastoFaktatKirjasto objektitiedosto
TilastoFaktatKirjasto.o: TilastoFaktatKirjasto.c TilastoFaktatKirjasto.h
	gcc -c TilastoFaktatKirjasto.c -std=c99 -pedantic -Wall

# MergeSortNousevaJKirjasto objektitiedosto
MergeSortNousevaJKirjasto.o: MergeSortNousevaJKirjasto.c MergeSortNousevaJKirjasto.h
	gcc -c MergeSortNousevaJKirjasto.c -std=c99 -pedantic -Wall

# MergeSortLaskevaJKirjasto objektitiedosto
MergeSortLaskevaJKirjasto.o: MergeSortLaskevaJKirjasto.c MergeSortLaskevaJKirjasto.h
	gcc -c MergeSortLaskevaJKirjasto.c -std=c99 -pedantic -Wall

# Bintree kirjaston objektitiedosto (UUSI)
Bintree.o: Bintree.c Bintree.h
	gcc -c Bintree.c -std=c99 -pedantic -Wall

# PITÄÄ AINA LISÄTÄ TÄTÄ et ei tuu ongelma kääntämiseen kanssa
clean:
	rm -f *.o projekti 
#muista poistaa kaikki tekstitiedostot ennen codegradepalautus, lisäämällä kommento "teks*.txt"  "*.o projektin" jälkeen