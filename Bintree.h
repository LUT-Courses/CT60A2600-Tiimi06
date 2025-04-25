#ifndef BINTREE_H
#define BINTREE_H
#define NIMIPITUUS 50

typedef struct BinSolmu {
    char name[NIMIPITUUS];
    int count;
    struct BinSolmu *pVasen;
    struct BinSolmu *pOikea;
    int height;
} BSOLMU;

BSOLMU* binaariLuoSolmu(const char *pNimi, int iLukumaara);
BSOLMU* binaariLisaa(BSOLMU *pJuuri, const char *pNimi, int iLukumaara);
void binaariVapauta(BSOLMU *pJuuri);
BSOLMU* binaariLueTiedosto(BSOLMU *pJuuri, const char *pTiedostonNimi);
void tulostaPuu(BSOLMU *pJuuri, int taso);

BSOLMU* binaariPoistaLukumaara(BSOLMU *pJuuri, int iLukumaara);
BSOLMU* binaariPoistaNimi(BSOLMU *pJuuri, const char *pNimi);
BSOLMU* binaariHaku(BSOLMU *pJuuri, int haettavaArvo);
int etsiNimiLukumaaranPerusteella(BSOLMU *pJuuri, int arvo, char *nimi);

/* UUSI apufunktio:
   Etsii lukumäärän nimen perusteella ja tallentaa sen *arvo-muuttujaan.
   Palauttaa 1, jos osuma löytyy, muulloin 0.
*/
int etsiLukumaaraNimenPerusteella(BSOLMU *pJuuri, const char *pNimi, int *arvo);

#endif
