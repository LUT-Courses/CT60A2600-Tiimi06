# Makefile for Main

#projekti: Bintree.o 
# Pääohjelma
projekti: Main.o MainKirjasto.o TilastoFaktatLista.o MergeSortLaskevaJKirjasto.o MergeSortNousevaJKirjasto.o Bintree.o TilastoFaktatBin.o
	gcc -o projekti Main.o MainKirjasto.o TilastoFaktatLista.o MergeSortLaskevaJKirjasto.o MergeSortNousevaJKirjasto.o Bintree.o TilastoFaktatBin.o

# Pääohjelman objektitiedosto
Main.o: Main.c MainKirjasto.h TilastoFaktatLista.h MergeSortLaskevaJKirjasto.h MergeSortNousevaJKirjasto.h Bintree.h TilastoFaktatBin.h
	gcc -c Main.c -std=c99 -pedantic -Wall

# Kirjaston objektitiedosto
MainKirjasto.o: MainKirjasto.c MainKirjasto.h TilastoFaktatLista.h MergeSortLaskevaJKirjasto.h MergeSortNousevaJKirjasto.h Bintree.h TilastoFaktatBin.h
	gcc -c MainKirjasto.c -std=c99 -pedantic -Wall

# TilastoFaktatLista objektitiedosto
TilastoFaktatLista.o: TilastoFaktatLista.c TilastoFaktatLista.h
	gcc -c TilastoFaktatLista.c -std=c99 -pedantic -Wall

# MergeSortNousevaJKirjasto objektitiedosto
MergeSortNousevaJKirjasto.o: MergeSortNousevaJKirjasto.c MergeSortNousevaJKirjasto.h
	gcc -c MergeSortNousevaJKirjasto.c -std=c99 -pedantic -Wall

# MergeSortLaskevaJKirjasto objektitiedosto
MergeSortLaskevaJKirjasto.o: MergeSortLaskevaJKirjasto.c MergeSortLaskevaJKirjasto.h
	gcc -c MergeSortLaskevaJKirjasto.c -std=c99 -pedantic -Wall

# Bintree kirjaston objektitiedosto
Bintree.o: Bintree.c Bintree.h
	gcc -c Bintree.c -std=c99 -pedantic -Wall

# TilastoFaktatBin kirjaston objektitiedosto (UUSI)
TilastoFaktatBin.o: TilastoFaktatBin.c TilastoFaktatBin.h
	gcc -c TilastoFaktatBin.c -std=c99 -pedantic -Wall

# PITÄÄ AINA LISÄTÄ TÄTÄ et ei tuu ongelma kääntämiseen kanssa
clean:
	rm -f *.o projekti teks*.txt
#muista poistaa kaikki tekstitiedostot ennen codegradepalautus, lisäämällä kommento "teks*.txt"  "*.o projektin" jälkeen