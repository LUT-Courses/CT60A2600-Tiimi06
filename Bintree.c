#include "Bintree.h"
#include "TIETO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funktioiden esittely
void kirjoitaEsiJarjestys(BSOLMU *pJuuri, FILE *pTiedosto);
void tulostaPuu(BSOLMU *pJuuri, int taso);
int maksimi(int a, int b);
int tarkistaKorkeus(BSOLMU *node);
void paivitaKorkeus(BSOLMU *node);
int tarkistaTasapaino(BSOLMU *node);
BSOLMU* pyoritaOikealle(BSOLMU *y);
BSOLMU* pyoritaVasemmalle(BSOLMU *x);
BSOLMU* binaariHaku(BSOLMU *pJuuri, int haettavaArvo);


/* Leveyshaulle tarvittava jono */
typedef struct JonoSolmu {
    BSOLMU *data;
    struct JonoSolmu *pSeuraava;
} JONOSOLMU;

typedef struct Jono {
    JONOSOLMU *pEteen;
    JONOSOLMU *pTaakse;
} JONO;

void tulostaPuu(BSOLMU *pJuuri, int taso) {
    if (pJuuri == NULL) {
        return;
    }

    tulostaPuu(pJuuri->pOikea, taso + 1);

    for (int i = 0; i < taso; i++) {
        printf("|   ");
    }
    printf("|-- %s (%d)\n", pJuuri->name, pJuuri->count);

    tulostaPuu(pJuuri->pVasen, taso + 1);
}
JONO* jonoLuo() {
    JONO *pUusiJono;
    if ((pUusiJono = (JONO*)malloc(sizeof(JONO))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    pUusiJono->pEteen = NULL;
    pUusiJono->pTaakse = NULL;
    return pUusiJono;
}

void jonoLisaa(JONO *pJono, BSOLMU *pData) {
    JONOSOLMU *pUusiSolmu;
    if ((pUusiSolmu = (JONOSOLMU*)malloc(sizeof(JONOSOLMU))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    pUusiSolmu->data = pData;
    pUusiSolmu->pSeuraava = NULL;
    
    if (pJono->pTaakse) {
        pJono->pTaakse->pSeuraava = pUusiSolmu;
        pJono->pTaakse = pUusiSolmu;
    } else {
        pJono->pEteen = pJono->pTaakse = pUusiSolmu;
    }
    return;
}

BSOLMU* jonoPoista(JONO *pJono) {
    if (!pJono->pEteen) return NULL;
    
    JONOSOLMU *pTemp = pJono->pEteen;
    BSOLMU *pData = pTemp->data;
    pJono->pEteen = pJono->pEteen->pSeuraava;
    
    if (!pJono->pEteen) pJono->pTaakse = NULL;
    free(pTemp);
    return pData;
}

void jonoVapauta(JONO *pJono) {
    while (pJono->pEteen) jonoPoista(pJono);
    free(pJono);
    return;
}


/* Binääripuun toteutus */
BSOLMU* binaariLuoSolmu(const char *pNimi, int iLukumaara) {
    if (!pNimi || strlen(pNimi) == 0) {
        printf("Virhe: Tyhjä nimi!\n");
        return NULL;
    }
    
    BSOLMU *pUusiNode;
    if ((pUusiNode = (BSOLMU*)malloc(sizeof(BSOLMU))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    
    strncpy(pUusiNode->name, pNimi, 49);
    pUusiNode->name[49] = '\0';
    pUusiNode->count = iLukumaara;
    pUusiNode->pVasen = pUusiNode->pOikea = NULL;
    
    pUusiNode->height = 1; // Lisätty korkeuden alustus
    return pUusiNode;
}

BSOLMU* binaariLisaa(BSOLMU *pJuuri, const char *pNimi, int iLukumaara) {
    if (!pJuuri) {
        return binaariLuoSolmu(pNimi, iLukumaara);
    }

    if (iLukumaara < pJuuri->count) {
        pJuuri->pVasen = binaariLisaa(pJuuri->pVasen, pNimi, iLukumaara);
    } 
    else if (iLukumaara > pJuuri->count) {
        pJuuri->pOikea = binaariLisaa(pJuuri->pOikea, pNimi, iLukumaara);
    } 
    // Jos numerot ovat samat, vertaile NIMIÄ
    else {
        int cmp = strcmp(pNimi, pJuuri->name);
        if (cmp < 0) {
            pJuuri->pVasen = binaariLisaa(pJuuri->pVasen, pNimi, iLukumaara);
        } else {
            pJuuri->pOikea = binaariLisaa(pJuuri->pOikea, pNimi, iLukumaara);
        }
    }

    // Päivitä solmun korkeus
    paivitaKorkeus(pJuuri);

    // Tarkista tasapaino
    int tasapaino = tarkistaTasapaino(pJuuri); 

    // Vasen Vasen -tapaus
    if (tasapaino > 1 && iLukumaara < pJuuri->pVasen->count)
        return pyoritaOikealle(pJuuri);

    // Oikea Oikea -tapaus
    if (tasapaino < -1 && iLukumaara > pJuuri->pOikea->count)
        return pyoritaVasemmalle(pJuuri);

    // Vasen Oikea -tapaus
    if (tasapaino > 1 && iLukumaara > pJuuri->pVasen->count) {
        pJuuri->pVasen = pyoritaVasemmalle(pJuuri->pVasen);
        return pyoritaOikealle(pJuuri);
    }

    // Oikea Vasen -tapaus
    if (tasapaino < -1 && iLukumaara < pJuuri->pOikea->count) {
        pJuuri->pOikea = pyoritaOikealle(pJuuri->pOikea);
        return pyoritaVasemmalle(pJuuri);
    }

    return pJuuri;
}

void binaariVapauta(BSOLMU *pJuuri) {
    if (pJuuri) {
        binaariVapauta(pJuuri->pVasen);
        binaariVapauta(pJuuri->pOikea);
        free(pJuuri);
    }
    return;
}

BSOLMU* binaariLueTiedosto(BSOLMU *pJuuri, const char *pTiedostonNimi) {
    FILE *pTiedosto = NULL;
    char aRivi[100] = {0};
    
    if ((pTiedosto = fopen(pTiedostonNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui");
        return pJuuri; // Älä sulje ohjelmaa, palauta nykyinen juuri
    }
    // ohita otsikko
    if (fgets(aRivi, sizeof(aRivi), pTiedosto) == NULL) {
        fclose(pTiedosto);
        return pJuuri;
    }

    // Tyhjennä vanha puu VAIN jos uusi tiedosto on validi
    binaariVapauta(pJuuri);
    pJuuri = NULL;

    while (fgets(aRivi, sizeof(aRivi), pTiedosto)) {
        char *p1, *p2;
        if ((p1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan %s.\n", aRivi, p1);
            exit(0);
        }
        if ((p2 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan %s.\n", aRivi, p2);
            exit(0);
        }
        
        int iLukumaara = atoi(p2);
        pJuuri = binaariLisaa(pJuuri, p1, iLukumaara);
    }

    fclose(pTiedosto);
    return pJuuri;
}


void kirjoitaEsiJarjestys(BSOLMU *pJuuri, FILE *pTiedosto) {
    if (!pJuuri) return;
    fprintf(pTiedosto, "%s,%d\n", pJuuri->name, pJuuri->count); // Juuri ensin
    kirjoitaEsiJarjestys(pJuuri->pVasen, pTiedosto); // Vasen alipuu
    kirjoitaEsiJarjestys(pJuuri->pOikea, pTiedosto); // Oikea alipuu
    return;
}

void binaariKirjoitaJarjestyksessa(BSOLMU *pJuuri, const char *pTiedostonNimi) {
    FILE *pTiedosto = NULL;
    if((pTiedosto = fopen (pTiedostonNimi, "w")) == NULL) {
        perror("Tiedoston kirjoittamisessa virhe, lopetetaan");
        exit(0);
    }
    kirjoitaEsiJarjestys(pJuuri, pTiedosto); // Muutettu tähän
    fclose(pTiedosto);
    return;
}


// Syvyyshaku (PRE-ORDER) ei toiminut ainakaan codegraden mukaisesti
int syvyyshakuRekursiivinen(BSOLMU *pJuuri, int iHaettava, FILE *pTiedosto, int *loytyi, char *loydettyNimi) {
    if (!pJuuri || *loytyi) return 0;

    // 1. Kirjoita NYKYINEN solmu aina ensin (pre-order)
    fprintf(pTiedosto, "%s,%d\n", pJuuri->name, pJuuri->count);

    // 2. Tarkista löytyikö arvo
    if (pJuuri->count == iHaettava) {
        *loytyi = 1;
        strcpy(loydettyNimi, pJuuri->name);
        return 1;
    }

    // 3. Tutki vasenta lasta vain jos ei vielä löytynyt
    if (!*loytyi) {
        syvyyshakuRekursiivinen(pJuuri->pVasen, iHaettava, pTiedosto, loytyi, loydettyNimi);
    }

    // 4. Tutki oikeaa lasta vain jos ei vielä löytynyt
    if (!*loytyi) {
        syvyyshakuRekursiivinen(pJuuri->pOikea, iHaettava, pTiedosto, loytyi, loydettyNimi);
    }

    return *loytyi;
}

int syvyysHaku(BSOLMU *pJuuri, int iHaettava, const char *pTiedostonNimi, char *loydettyNimi) {
    FILE *pTiedosto = NULL;

    if((pTiedosto = fopen(pTiedostonNimi, "w")) == NULL) {
        perror("Tiedoston kirjoittamisessa virhe, lopetetaan.");
        exit(0);
    }

    int loytyi = 0;
    syvyyshakuRekursiivinen(pJuuri, iHaettava, pTiedosto, &loytyi, loydettyNimi);
    fclose(pTiedosto);
    return loytyi;
}

/* Leveyshaku (BFS) */
int leveysHaku(BSOLMU *pJuuri, const char *pHaettavaNimi, const char *pTiedostonNimi, int *loydettyLkm) {
    if (!pJuuri) return 0;
    
    JONO *pJono = jonoLuo();
    FILE *pTiedosto = NULL;
    
    if ((pTiedosto = fopen(pTiedostonNimi,"w")) == NULL) {
        perror("Tiedoston kirjoittamisessa virhe, lopetetaan.");
        exit(0);
    }

    int loytyi = 0;
    jonoLisaa(pJono, pJuuri);

    while (pJono->pEteen && !loytyi) {
        BSOLMU *pNykyinen = jonoPoista(pJono);
        fprintf(pTiedosto, "%s,%d\n", pNykyinen->name, pNykyinen->count);
        
        if (strcmp(pNykyinen->name, pHaettavaNimi) == 0) {
            loytyi = 1;
            *loydettyLkm = pNykyinen->count;
        } else {
            if (pNykyinen->pVasen) jonoLisaa(pJono, pNykyinen->pVasen);
            if (pNykyinen->pOikea) jonoLisaa(pJono, pNykyinen->pOikea);
        }
    }
    
    fclose(pTiedosto);
    jonoVapauta(pJono);
    return loytyi;
}
//uusi lisäys
int etsiNimiLukumaaranPerusteella(BSOLMU *pJuuri, int arvo, char *nimi) {
    if (pJuuri == NULL)
        return 0;
    if (pJuuri->count == arvo) {
        strcpy(nimi, pJuuri->name);
        return 1;
    }
    if (etsiNimiLukumaaranPerusteella(pJuuri->pVasen, arvo, nimi))
        return 1;
    if (etsiNimiLukumaaranPerusteella(pJuuri->pOikea, arvo, nimi))
        return 1;
    return 0;
}

/* Poistaa solmun, jonka count vastaa annettua iLukumaaraa */
BSOLMU* binaariPoistaLukumaara(BSOLMU *pJuuri, int iLukumaara) {
    if (pJuuri == NULL)
        return NULL;
    
    if (iLukumaara < pJuuri->count) {
        pJuuri->pVasen = binaariPoistaLukumaara(pJuuri->pVasen, iLukumaara);
    } else if (iLukumaara > pJuuri->count) {
        pJuuri->pOikea = binaariPoistaLukumaara(pJuuri->pOikea, iLukumaara);
    } else {
        // Solmu löytyi: poistetaan se
        if (pJuuri->pVasen == NULL && pJuuri->pOikea == NULL) {
            free(pJuuri);
            return NULL;
        } else if (pJuuri->pVasen == NULL) {
            BSOLMU *temp = pJuuri->pOikea;
            free(pJuuri);
            return temp;
        } else if (pJuuri->pOikea == NULL) {
            BSOLMU *temp = pJuuri->pVasen;
            free(pJuuri);
            return temp;
        } else {
            
            BSOLMU *temp = pJuuri->pOikea;
            while (temp && temp->pVasen != NULL) {
                temp = temp->pVasen;
            }
           
            strcpy(pJuuri->name, temp->name);
            pJuuri->count = temp->count;
          
            pJuuri->pOikea = binaariPoistaLukumaara(pJuuri->pOikea, temp->count);
        }
    }
    return pJuuri;
}

/* Apufunktio, joka rekursiivisesti poistaa solmun nimen perusteella.
   'poistettu' kertoo, onko poistotoimenpide suoritettu.
*/
BSOLMU* binaariPoistaNimiRekursiivisesti(BSOLMU *pJuuri, const char *pNimi, int *poistettu) {
    if (pJuuri == NULL)
        return NULL;
    
    if (!(*poistettu) && strcmp(pJuuri->name, pNimi) == 0) {
        *poistettu = 1;
        return binaariPoistaLukumaara(pJuuri, pJuuri->count);
    }
    
    if (!(*poistettu))
        pJuuri->pVasen = binaariPoistaNimiRekursiivisesti(pJuuri->pVasen, pNimi, poistettu);
    if (!(*poistettu))
        pJuuri->pOikea = binaariPoistaNimiRekursiivisesti(pJuuri->pOikea, pNimi, poistettu);
    
    return pJuuri;
}

/* Poistaa solmun nimen perusteella, eli ensimmäisen osuman, joka vastaa annettua pNimi-arvoa */
BSOLMU* binaariPoistaNimi(BSOLMU *pJuuri, const char *pNimi) {
    int poistettu = 0;
    return binaariPoistaNimiRekursiivisesti(pJuuri, pNimi, &poistettu);
}

int etsiLukumaaraNimenPerusteella(BSOLMU *pJuuri, const char *pNimi, int *arvo) {
    if (pJuuri == NULL) {
        return 0;
    }
    if (strcmp(pJuuri->name, pNimi) == 0) {
        *arvo = pJuuri->count;
        return 1;
    }
    if (etsiLukumaaraNimenPerusteella(pJuuri->pVasen, pNimi, arvo)) {
        return 1;
    }
    if (etsiLukumaaraNimenPerusteella(pJuuri->pOikea, pNimi, arvo)) {
        return 1;
    }
    return 0;
}

int maksimi(int a, int b) {
    return (a > b) ? a : b;
}

int tarkistaKorkeus(BSOLMU *node) {
    if (node == NULL) return 0;
    return node -> height;
}

void paivitaKorkeus (BSOLMU *node) {
    if(node == NULL) return;
    node -> height = 1 + maksimi(tarkistaKorkeus(node -> pVasen), tarkistaKorkeus(node -> pOikea));
    return;
}

int tarkistaTasapaino(BSOLMU *node) {
    if (node == NULL) return 0;  // Korjattu return-lauseke
    return tarkistaKorkeus(node->pVasen) - tarkistaKorkeus(node->pOikea);
}

BSOLMU* pyoritaOikealle(BSOLMU *y) {
    BSOLMU *x = y->pVasen;
    BSOLMU *T2 = x->pOikea;

    x->pOikea = y;
    y->pVasen = T2;

    paivitaKorkeus(y);  
    paivitaKorkeus(x);

    return x;
}

BSOLMU* pyoritaVasemmalle(BSOLMU *x) {
    BSOLMU *y = x->pOikea;
    BSOLMU *T2 = y->pVasen;

    y->pVasen = x;
    x->pOikea = T2;

    paivitaKorkeus(x);  
    paivitaKorkeus(y);

    return y;
}

// Binäärihaun toteutus
BSOLMU* binaariHaku(BSOLMU *pJuuri, int iHaettavaArvo) {
    if (pJuuri == NULL) {
        return NULL; 
    }

    if (iHaettavaArvo == pJuuri->count) {
        return pJuuri; 
    } 

    else if (iHaettavaArvo < pJuuri->count) {

        return binaariHaku(pJuuri->pVasen, iHaettavaArvo); 
    } else {

        return binaariHaku(pJuuri->pOikea, iHaettavaArvo); 
    }
}
