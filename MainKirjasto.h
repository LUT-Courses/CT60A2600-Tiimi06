#ifndef L8T1KIRJASTO_H
#define L8T1KIRJASTO_H

#define SUKUNIMIKOKO 30
#define TIEDOSTONKOKO 30

#include "TIETO.h"
#include "TilastoFaktatLista.h"
#include "MergeSortLaskevaJKirjasto.h"
#include "Bintree.h" 

int graafiValikko(void);
int binaariValikko(void);
char *kysyNimi(char *pPromtti);
int valikko();
TIETO *lisaaAlkio(TIETO *pAlku, char *sukuNimi, int lkm);
TIETO *lueTiedosto(TIETO *pA, char *tiedostonNimi);
void tallennaEtuperin(TIETO *pA, char *tiedostonNimi) ;
void tallennaTakaperin(TIETO *pA, char *tiedostonNimi);
TIETO *tyhjennaLista(TIETO *pA);
void tilastoFaktaArpojaLista(TIETO *pA);
void tilastoFaktaArpojaBin(BNODE *pA);
int paaValikko(void);
int linkitettyValikko(void);
int binaariValikko(void); // Poista parametri




#endif