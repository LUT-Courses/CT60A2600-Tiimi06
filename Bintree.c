#include "Bintree.h"
#include "TIETO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Leveyshaulle tarvittava jono */
typedef struct JonoSolmu {
    BNODE *data;
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

void jono_lisaa(JONO *pJono, BNODE *pData) {
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

BNODE* jono_poista(JONO *pJono) {
    if (!pJono->pEteen) return NULL;
    
    JONOSOLMU *pTemp = pJono->pEteen;
    BNODE *pData = pTemp->data;
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
BNODE* binaariLuoNode(const char *pNimi, int iLukumaara) {
    if (!pNimi || strlen(pNimi) == 0) {
        printf("Virhe: Tyhjä nimi!\n");
        return NULL;
    }
    
    BNODE *pUusiNode = malloc(sizeof(BNODE));
    if (!pUusiNode) {
        perror("Muistinvaraus epäonnistui");
        return NULL;
    }
    
    strncpy(pUusiNode->name, pNimi, 49);
    pUusiNode->name[49] = '\0';
    pUusiNode->count = iLukumaara;
    pUusiNode->pVasen = pUusiNode->pOikea = NULL;
    
    return pUusiNode;
}
BNODE* binaariInsert(BNODE *pJuuri, const char *pNimi, int iLukumaara) {
    if (!pJuuri) return binaariLuoNode(pNimi, iLukumaara);
    
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

    // Ohita otsikko turvallisesti
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

/* In-order traversal tiedostoon */
static void kirjoita_jarjestyksessa_rekursiivinen(BNODE *pJuuri, FILE *pTiedosto) {
    if (!pJuuri) return;
    kirjoita_jarjestyksessa_rekursiivinen(pJuuri->pVasen, pTiedosto);
    fprintf(pTiedosto, "%s,%d\n", pJuuri->name, pJuuri->count);
    kirjoita_jarjestyksessa_rekursiivinen(pJuuri->pOikea, pTiedosto);
}

void binaariKirjoitaJarjestyksessa(BNODE *pJuuri, const char *pTiedostonNimi) {
    FILE *pTiedosto = NULL;
    if ((pTiedosto = fopen (pTiedostonNimi, "w")) == NULL) {
        perror ("Tiedoston kirjoitttamisessa virhe, lopetetaan.");
        exit(0);
    }
    kirjoita_jarjestyksessa_rekursiivinen(pJuuri, pTiedosto);
    fclose(pTiedosto);
}

/* Syvyyshaku (in-order) */
static int syvyyshaku_rekursiivinen(BNODE *pJuuri, int iHaettava, FILE *pTiedosto, int *loytyi, char *loydettyNimi) {
    if (!pJuuri || *loytyi) return 0;
    
    // Tutki vasenta lasta vain jos arvoa ei ole löytynyt
    if (!*loytyi) {
        syvyyshaku_rekursiivinen(pJuuri->pVasen, iHaettava, pTiedosto, loytyi, loydettyNimi);
    }
    
    // Kirjoita aina tiedostoon
    fprintf(pTiedosto, "%s,%d\n", pJuuri->name, pJuuri->count);
    
    // Tarkista löytyikö arvo
    if (pJuuri->count == iHaettava) {
        *loytyi = 1;
        strcpy(loydettyNimi, pJuuri->name);
        return 1; // Keskeytä välittömästi
    }
    
    // Tutki oikeaa lasta vain jos arvoa ei löytynyt
    if (!*loytyi) {
        syvyyshaku_rekursiivinen(pJuuri->pOikea, iHaettava, pTiedosto, loytyi, loydettyNimi);
    }
    
    return *loytyi;
}

int syvyysHaku(BNODE *pJuuri, int iHaettava, const char *pTiedostonNimi, char *loydettyNimi) {
    FILE *pTiedosto = fopen(pTiedostonNimi, "w");
    if (!pTiedosto) {
        perror("Tiedoston avaaminen epäonnistui");
        return 0;
    }

    int loytyi = 0;
    syvyyshaku_rekursiivinen(pJuuri, iHaettava, pTiedosto, &loytyi, loydettyNimi);
    fclose(pTiedosto);
    return loytyi;
}

/* Leveyshaku (BFS) */
int leveysHaku(BNODE *pJuuri, const char *pHaettavaNimi, const char *pTiedostonNimi, int *loydettyLkm) {
    if (!pJuuri) return 0;
    
    JONO *pJono = jono_luo();
    FILE *pTiedosto = fopen(pTiedostonNimi, "w");
    if (!pTiedosto) {
        perror("Tiedoston avaaminen epäonnistui");
        return 0;
    }

    int loytyi = 0;
    jono_lisaa(pJono, pJuuri);

    while (pJono->pEteen && !loytyi) {
        BNODE *pNykyinen = jono_poista(pJono);
        fprintf(pTiedosto, "%s,%d\n", pNykyinen->name, pNykyinen->count);
        
        if (strcmp(pNykyinen->name, pHaettavaNimi) == 0) {
            loytyi = 1;
            *loydettyLkm = pNykyinen->count;
        } else {
            if (pNykyinen->pVasen) jono_lisaa(pJono, pNykyinen->pVasen);
            if (pNykyinen->pOikea) jono_lisaa(pJono, pNykyinen->pOikea);
        }
    }
    
    fclose(pTiedosto);
    jono_vapauta(pJono);
    return loytyi;
}
void tulostaPuunRakenne(BNODE *pJuuri, int taso) {
    if (!pJuuri) return;
    tulostaPuunRakenne(pJuuri->pOikea, taso + 1);
    for (int i = 0; i < taso; i++) printf("    ");
    printf("%s (%d)\n", pJuuri->name, pJuuri->count);
    tulostaPuunRakenne(pJuuri->pVasen, taso + 1);
}