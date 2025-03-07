#ifndef L8T1KIRJASTO_H
#define L8T1KIRJASTO_H

#define SUKUNIMIKOKO 30
#define TIEDOSTONKOKO 30

typedef struct tieto {
    char sukunimi[SUKUNIMIKOKO];
    int lukumaara;
    struct tieto *pSeuraava;  //talennetaan tähän linkitetty listaan seuraavan alkion osoite
    struct tieto *pEdellinen; // talennetaan tähän linkitetty listaan edellisen alkion osoite

} TIETO;


char *kysyNimi(char *pPromtti);
int valikko();
TIETO *lisaaAlkio(TIETO *pAlku, char *sukuNimi, int lkm);
TIETO *lueTiedosto(TIETO *pA, char *tiedostonNimi);
void tallennaEtuperin(TIETO *pA) ;
TIETO *tyhjennaLista(TIETO *pA);



#endif