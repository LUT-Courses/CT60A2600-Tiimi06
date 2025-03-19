#include "Bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Leveyshaulle tarvittava jono */
typedef struct JonoSolmu {
    NODE *data;
    struct JonoSolmu *pSeuraava;
} JONOSOLMU;

typedef struct Jono {
    JONOSOLMU *pEteen;
    JONOSOLMU *pTaakse;
} JONO;

/* Poistettu static-määreet ja korvattu calloc mallocilla */
JONO* jono_luo() {
    JONO *pUusiJono = malloc(sizeof(JONO));
    if (pUusiJono) {
        pUusiJono->pEteen = NULL;
        pUusiJono->pTaakse = NULL;
    }
    return pUusiJono;
}

void jono_lisaa(JONO *pJono, NODE *pData) {
    JONOSOLMU *pUusiSolmu = malloc(sizeof(JONOSOLMU));
    pUusiSolmu->data = pData;
    pUusiSolmu->pSeuraava = NULL;
    
    if (pJono->pTaakse) {
        pJono->pTaakse->pSeuraava = pUusiSolmu;
        pJono->pTaakse = pUusiSolmu;
    } else {
        pJono->pEteen = pJono->pTaakse = pUusiSolmu;
    }
}

NODE* jono_poista(JONO *pJono) {
    if (!pJono->pEteen) return NULL;
    
    JONOSOLMU *pTemp = pJono->pEteen;
    NODE *pData = pTemp->data;
    pJono->pEteen = pJono->pEteen->pSeuraava;
    
    if (!pJono->pEteen) pJono->pTaakse = NULL;
    free(pTemp);
    return pData;
}

void jono_vapauta(JONO *pJono) {
    while (pJono->pEteen) jono_poista(pJono);
    free(pJono);
}


/* Binääripuun toteutus */
NODE* binaariLuoNode(const char *pNimi, int iLukumaara) {
    NODE *pUusiNode = malloc(sizeof(NODE));
    strncpy(pUusiNode->name, pNimi, 49);
    pUusiNode->name[49] = '\0';
    pUusiNode->count = iLukumaara;
    pUusiNode->pVasen = pUusiNode->pOikea = NULL;
    return pUusiNode;
}

NODE* binaariInsert(NODE *pJuuri, const char *pNimi, int iLukumaara) {
    if (!pJuuri) return binaariLuoNode(pNimi, iLukumaara);
    
    if (iLukumaara < pJuuri->count) {
        pJuuri->pVasen = binaariInsert(pJuuri->pVasen, pNimi, iLukumaara);
    } else if (iLukumaara > pJuuri->count) {
        pJuuri->pOikea = binaariInsert(pJuuri->pOikea, pNimi, iLukumaara);
    }
    return pJuuri;
}

void binaariVapauta(NODE *pJuuri) {
    if (pJuuri) {
        binaariVapauta(pJuuri->pVasen);
        binaariVapauta(pJuuri->pOikea);
        free(pJuuri);
    }
}

NODE* binaariLueTiedosto(NODE *pJuuri, const char *pTiedostonNimi) {
    FILE *pTiedosto = NULL;
    if ((pTiedosto = fopen (pTiedostonNimi, "r")) == NULL) {
        perror ("Tiedoston lukemisessa virhe, lopetetaan.");
        exit(0);
    }
    
    char aRivi[100];
    fgets(aRivi, sizeof(aRivi), pTiedosto); // Ohitetaan otsikko
    
    binaariVapauta(pJuuri);
    pJuuri = NULL;
    
    while (fgets(aRivi, sizeof(aRivi), pTiedosto)) {
        char *pNimi = strtok(aRivi, ";\n");
        char *pLukumaaraStr = strtok(NULL, ";\n");
        int iLukumaara = atoi(pLukumaaraStr);
        pJuuri = binaariInsert(pJuuri, pNimi, iLukumaara);
    }
    
    fclose(pTiedosto);
    return pJuuri;
}

/* In-order traversal tiedostoon */
static void kirjoita_jarjestyksessa_rekursiivinen(NODE *pJuuri, FILE *pTiedosto) {
    if (!pJuuri) return;
    kirjoita_jarjestyksessa_rekursiivinen(pJuuri->pVasen, pTiedosto);
    fprintf(pTiedosto, "%s,%d\n", pJuuri->name, pJuuri->count);
    kirjoita_jarjestyksessa_rekursiivinen(pJuuri->pOikea, pTiedosto);
}

void binaariKirjoitaJarjestyksessa(NODE *pJuuri, const char *pTiedostonNimi) {
    FILE *pTiedosto = NULL;
    if ((pTiedosto = fopen (pTiedostonNimi, "w")) == NULL) {
        perror ("Tiedoston kirjoitttamisessa virhe, lopetetaan.");
        exit(0);
    }
    kirjoita_jarjestyksessa_rekursiivinen(pJuuri, pTiedosto);
    fclose(pTiedosto);
}

/* Syvyyshaku (in-order) */
static int syvyyshaku_rekursiivinen(NODE *pJuuri, int iHaettava, FILE *pTiedosto, int *loytyi) {
    if (!pJuuri || *loytyi) return 0;
    
    syvyyshaku_rekursiivinen(pJuuri->pVasen, iHaettava, pTiedosto, loytyi);
    fprintf(pTiedosto, "%s,%d\n", pJuuri->name, pJuuri->count);
    if (pJuuri->count == iHaettava) *loytyi = 1;
    syvyyshaku_rekursiivinen(pJuuri->pOikea, iHaettava, pTiedosto, loytyi);
    
    return *loytyi;
}

int syvyysHaku(NODE *pJuuri, int iHaettava, const char *pTiedostonNimi) {
    FILE *pTiedosto = NULL;
    if ((pTiedosto = fopen (pTiedostonNimi, "w")) == NULL) {
        perror ("Tiedoston kirjoitttamisessa virhe, lopetetaan.");
        exit(0);
    }
    
    int loytyi = 0;
    syvyyshaku_rekursiivinen(pJuuri, iHaettava, pTiedosto, &loytyi);
    fclose(pTiedosto);
    return loytyi;
}

/* Leveyshaku (BFS) */
int leveysHaku(NODE *pJuuri, const char *pHaettavaNimi, const char *pTiedostonNimi) {
    if (!pJuuri) return 0;
    
    JONO *pJono = jono_luo();
    FILE *pTiedosto = NULL;
    if ((pTiedosto = fopen (pTiedostonNimi, "w")) == NULL) {
        perror ("Tiedoston kirjoitttamisessa virhe, lopetetaan.");
        exit(0);
    }
    
    int loytyi = 0;
    jono_lisaa(pJono, pJuuri);
    
    while (pJono->pEteen && !loytyi) {
        NODE *pNykyinen = jono_poista(pJono);
        fprintf(pTiedosto, "%s,%d\n", pNykyinen->name, pNykyinen->count);
        
        if (strcmp(pNykyinen->name, pHaettavaNimi) == 0) {
            loytyi = 1;
        } else {
            if (pNykyinen->pVasen) jono_lisaa(pJono, pNykyinen->pVasen);
            if (pNykyinen->pOikea) jono_lisaa(pJono, pNykyinen->pOikea);
        }
    }
    
    fclose(pTiedosto);
    jono_vapauta(pJono);
    return loytyi;
}