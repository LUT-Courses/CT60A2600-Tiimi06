#ifndef GRAAFI_H
#define GRAAFI_H
#define SOLMUNPITUUS 50
#define INF 1000000
#define RIVILKM 100

// Kaari (reuna) graafissa
typedef struct Kaari {
    int etaisyys;
    struct Vertex *kohde;
    struct Kaari *seuraava;
} KAARI;

// Solmu (vertex) graafissa
typedef struct Vertex {
    char nimi[SOLMUNPITUUS];
    KAARI *kaaret;
    struct Vertex *seuraava;
} KARKI;

// Graafi (verkko)
typedef struct {
    KARKI *solmut;
} GRAAFI;

/* Prototyypit */
// Luo uusi tyhjä graafi
GRAAFI* graafiLuo(void);
// Vapauta graafi ja kaikki sen solmut sekä kaaret
void graafiVapauta(GRAAFI *g);
// Lue graafi tiedostosta, esim. "verkko_pieni.txt"
GRAAFI* graafiLueTiedosto(GRAAFI *g, const char *tiedostonNimi);
// Lisää tai päivittää kaaren: jos kaari solmusta lahto solmuun kohde on jo olemassa, päivitetään etäisyys; muulloin lisätään uusi
void graafiLisaaKaari(GRAAFI *g, const char *lahto, const char *kohde, int etaisyys);
// Poista solmu graafista (ja samalla kaikki siihen liittyvät kaaret)
GRAAFI* graafiPoistaSolmu(GRAAFI *g, const char *solmuNimi);
// Etsi lyhin reitti graafissa solmujen nimen perusteella ja kirjoita reitti sekä kokonaisetäisyys tiedostoon (append-tilassa)
void graafiEtsiLyhinReitti(GRAAFI *g, const char *lahto, const char *kohde, const char *tiedostonNimi);

#endif
