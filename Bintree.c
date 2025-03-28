#include "Bintree.h"
#include "TIETO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funktioiden esittely
void kirjoitaPreOrder(BNODE *pJuuri, FILE *pTiedosto);
void tulostaPuu(BNODE *pJuuri, int taso);


/* Leveyshaulle tarvittava jono */
typedef struct JonoSolmu {
    BNODE *data;
    struct JonoSolmu *pSeuraava;
} JONOSOLMU;

typedef struct Jono {
    JONOSOLMU *pEteen;
    JONOSOLMU *pTaakse;
} JONO;

void tulostaPuu(BNODE *pJuuri, int taso) {
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

void jonoLisaa(JONO *pJono, BNODE *pData) {
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
}

BNODE* jonoPoista(JONO *pJono) {
    if (!pJono->pEteen) return NULL;
    
    JONOSOLMU *pTemp = pJono->pEteen;
    BNODE *pData = pTemp->data;
    pJono->pEteen = pJono->pEteen->pSeuraava;
    
    if (!pJono->pEteen) pJono->pTaakse = NULL;
    free(pTemp);
    return pData;
}

void jonoVapauta(JONO *pJono) {
    while (pJono->pEteen) jonoPoista(pJono);
    free(pJono);
}


/* Binääripuun toteutus */
BNODE* binaariLuoNode(const char *pNimi, int iLukumaara) {
    if (!pNimi || strlen(pNimi) == 0) {
        printf("Virhe: Tyhjä nimi!\n");
        return NULL;
    }
    
    BNODE *pUusiNode;
    if ((pUusiNode = (BNODE*)malloc(sizeof(BNODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    
    strncpy(pUusiNode->name, pNimi, 49);
    pUusiNode->name[49] = '\0';
    pUusiNode->count = iLukumaara;
    pUusiNode->pVasen = pUusiNode->pOikea = NULL;
    
    return pUusiNode;
}

BNODE* binaariInsert(BNODE *pJuuri, const char *pNimi, int iLukumaara) {
    if (!pJuuri) {
        return binaariLuoNode(pNimi, iLukumaara);
    }
    
    if (iLukumaara < pJuuri->count) {
        pJuuri->pVasen = binaariInsert(pJuuri->pVasen, pNimi, iLukumaara);
    } else if (iLukumaara > pJuuri->count) {
        pJuuri->pOikea = binaariInsert(pJuuri->pOikea, pNimi, iLukumaara);
    }
    return pJuuri;
}

void binaariVapauta(BNODE *pJuuri) {
    if (pJuuri) {
        binaariVapauta(pJuuri->pVasen);
        binaariVapauta(pJuuri->pOikea);
        free(pJuuri);
    }
}

BNODE* binaariLueTiedosto(BNODE *pJuuri, const char *pTiedostonNimi) {
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
        char *pNimi = strtok(aRivi, ";\n");
        char *pLukumaaraStr = strtok(NULL, ";\n");
        
        if (!pNimi || !pLukumaaraStr) {
            printf("Virheellinen rivi: %s", aRivi);
            continue;
        }
        
        int iLukumaara = atoi(pLukumaaraStr);
        pJuuri = binaariInsert(pJuuri, pNimi, iLukumaara);
    }

    fclose(pTiedosto);
    return pJuuri;
}

void kirjoitaPreOrder(BNODE *pJuuri, FILE *pTiedosto) {
    if (!pJuuri) return;
    fprintf(pTiedosto, "%s,%d\n", pJuuri->name, pJuuri->count); // Juuri ensin
    kirjoitaPreOrder(pJuuri->pVasen, pTiedosto); // Vasen alipuu
    kirjoitaPreOrder(pJuuri->pOikea, pTiedosto); // Oikea alipuu
}

void binaariKirjoitaJarjestyksessa(BNODE *pJuuri, const char *pTiedostonNimi) {
    FILE *pTiedosto = fopen(pTiedostonNimi, "w");
    if (!pTiedosto) {
        perror("Tiedoston kirjoittamisessa virhe");
        exit(0);
    }
    kirjoitaPreOrder(pJuuri, pTiedosto); // Muutettu tähän
    fclose(pTiedosto);
}

// Syvyyshaku (in-order) 
// Syvyyshaku (PRE-ORDER) ei toiminut ainakaan codegraden mukaisesti
int syvyyshakuRekursiivinen(BNODE *pJuuri, int iHaettava, FILE *pTiedosto, int *loytyi, char *loydettyNimi) {
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

int syvyysHaku(BNODE *pJuuri, int iHaettava, const char *pTiedostonNimi, char *loydettyNimi) {
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
int leveysHaku(BNODE *pJuuri, const char *pHaettavaNimi, const char *pTiedostonNimi, int *loydettyLkm) {
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
        BNODE *pNykyinen = jonoPoista(pJono);
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
