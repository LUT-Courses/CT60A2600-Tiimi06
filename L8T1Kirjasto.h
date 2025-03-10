#ifndef L8T1KIRJASTO_H
#define L8T1KIRJASTO_H

#define SUKUNIMIKOKO 30
#define TIEDOSTONKOKO 30

#include "TIETO.h"
#include "TilastoFaktatKirjasto.h"



char *kysyNimi(char *pPromtti);
int valikko();
TIETO *lisaaAlkio(TIETO *pAlku, char *sukuNimi, int lkm);
TIETO *lueTiedosto(TIETO *pA, char *tiedostonNimi);
void tallennaEtuperin(TIETO *pA, char *tiedostonNimi) ;
void tallennaTakaperin(TIETO *pA, char *tiedostonNimi);
TIETO *tyhjennaLista(TIETO *pA);
void tilastoFaktaArpoja(TIETO *pA);



#endif