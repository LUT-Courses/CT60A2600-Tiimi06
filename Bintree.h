#ifndef BINTREE_H
#define BINTREE_H
#define NIMIPITUUS 50

typedef struct BinNode {
    char name[NIMIPITUUS];
    int count;
    struct BinNode *pVasen;
    struct BinNode *pOikea;
    int height;
} BNODE;

BNODE* binaariLuoNode(const char *pNimi, int iLukumaara);
BNODE* binaariInsert(BNODE *pJuuri, const char *pNimi, int iLukumaara);
void binaariVapauta(BNODE *pJuuri);
BNODE* binaariLueTiedosto(BNODE *pJuuri, const char *pTiedostonNimi);
void tulostaPuu(BNODE *pJuuri, int taso);

BNODE* binaariPoistaLukumaara(BNODE *pJuuri, int iLukumaara);
BNODE* binaariPoistaNimi(BNODE *pJuuri, const char *pNimi);
BNODE* binaariHaku(BNODE *pJuuri, int haettavaArvo);
int etsiNimiLukumaaranPerusteella(BNODE *pJuuri, int arvo, char *nimi);

/* UUSI apufunktio:
   Etsii lukumäärän nimen perusteella ja tallentaa sen *arvo-muuttujaan.
   Palauttaa 1, jos osuma löytyy, muulloin 0.
*/
int etsiLukumaaraNimenPerusteella(BNODE *pJuuri, const char *pNimi, int *arvo);

#endif
