# Makefile for L8T1

# Pääohjelma
projekti: L8T1.o L8T1Kirjasto.o TilastoFaktatKirjasto.o MergeSortLaskevaJKirjasto.o
	gcc -o projekti L8T1.o L8T1Kirjasto.o TilastoFaktatKirjasto.o MergeSortLaskevaJKirjasto.o

# Pääohjelman objektitiedosto
L8T1.o: L8T1.c L8T1Kirjasto.h TilastoFaktatKirjasto.h MergeSortLaskevaJKirjasto.h
	gcc -c L8T1.c -std=c99 -pedantic -Wall

# Kirjaston objektitiedosto
L8T1Kirjasto.o: L8T1Kirjasto.c L8T1Kirjasto.h TilastoFaktatKirjasto.h MergeSortLaskevaJKirjasto.h
	gcc -c L8T1Kirjasto.c -std=c99 -pedantic -Wall

# TilastoFaktatKirjasto objektitiedosto
TilastoFaktatKirjasto.o: TilastoFaktatKirjasto.c TilastoFaktatKirjasto.h
	gcc -c TilastoFaktatKirjasto.c -std=c99 -pedantic -Wall

<<<<<<< HEAD
# MergeSortLaskevaJKirjasto objektitiedosto
MergeSortLaskevaJKirjasto.o: MergeSortLaskevaJKirjasto.c MergeSortLaskevaJKirjasto.h L8T1Kirjasto.h TilastoFaktatKirjasto.h
	gcc -c MergeSortLaskevaJKirjasto.c -std=c99 -pedantic -Wall
=======
# MergeSortNousevaJKirjasto objektitiedosto
MergeSortNousevaJKirjasto.o: MergeSortNousevaJKirjasto.c MergeSortNousevaJKirjasto.h
	gcc -c MergeSortNousevaJKirjasto.c -std=c99 -pedantic -Wall
>>>>>>> 646140c0118cd03b0754b1c4033bb8161ccca942
