# Makefile for L8T1

# Pääohjelma
L8T1: L8T1.o L8T1Kirjasto.o
	gcc -o L8T1 L8T1.o L8T1Kirjasto.o

# Pääohjelman objektitiedosto
L8T1.o: L8T1.c L8T1Kirjasto.h
	gcc -c L8T1.c -std=c99 -pedantic -Wall

# Kirjaston objektitiedosto
L8T1Kirjasto.o: L8T1Kirjasto.c L8T1Kirjasto.h
	gcc -c L8T1Kirjasto.c -std=c99 -pedantic -Wall