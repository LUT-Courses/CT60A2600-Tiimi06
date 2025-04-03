#include "Graafi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/////////////////////////////////////////////////////////////////////////
// Graafin perustoiminnot

// Luo uuden tyhjän graafin
GRAAFI* graafiLuo(void) {
    GRAAFI *g = (GRAAFI*)malloc(sizeof(GRAAFI));
    if (g == NULL) {
        perror("Muistin varaus graafille epäonnistui");
        exit(1);
    }
    g->solmut = NULL;
    return g;
}

// Vapauttaa kaaret solmusta
static void vapautaKaaret(KAARI *k) {
    while (k) {
        KAARI *temp = k;
        k = k->seuraava;
        free(temp);
    }
}

// Vapauttaa graafin ja kaikki sen solmut ja kaaret
void graafiVapauta(GRAAFI *g) {
    if (g == NULL)
        return;
    VERTEX *s = g->solmut;
    while (s) {
        vapautaKaaret(s->kaaret);
        VERTEX *temp = s;
        s = s->seuraava;
        free(temp);
    }
    free(g);
}

/////////////////////////////////////////////////////////////////////////
// Solmujen ja kaarien hallinta

// Apufunktio: Etsii graafista solmun annetun nimen perusteella
static VERTEX* etsiSolmu(GRAAFI *g, const char *nimi) {
    VERTEX *s = g->solmut;
    while (s) {
        if (strcmp(s->nimi, nimi) == 0)
            return s;
        s = s->seuraava;
    }
    return NULL;
}

// Apufunktio: Lisää uusi solmu, jos sitä ei löydy; palauttaa solmun osoittimen
static VERTEX* lisaaSolmu(GRAAFI *g, const char *nimi) {
    VERTEX *s = etsiSolmu(g, nimi);
    if (s != NULL)
        return s;
    s = (VERTEX*)malloc(sizeof(VERTEX));
    if (s == NULL) {
        perror("Muistin varaus solmulle epäonnistui");
        exit(1);
    }
    strncpy(s->nimi, nimi, SOLMUNPITUUS - 1);
    s->nimi[SOLMUNPITUUS - 1] = '\0';
    s->kaaret = NULL;
    s->seuraava = g->solmut;
    g->solmut = s;
    return s;
}

// Lisää tai päivittää kaaren graafiin
void graafiLisaaKaari(GRAAFI *g, const char *lahto, const char *kohde, int etaisyys) {
    VERTEX *sLahto = lisaaSolmu(g, lahto);
    VERTEX *sKohde = lisaaSolmu(g, kohde);
    
    KAARI *k = sLahto->kaaret;
    while (k) {
        if (strcmp(k->kohde->nimi, kohde) == 0) {
            // Kaari löytyy, päivitetään etäisyys
            k->etaisyys = etaisyys;
            return;
        }
        k = k->seuraava;
    }
    // Lisätään uusi kaari solmusta lahto solmuun kohde
    k = (KAARI*)malloc(sizeof(KAARI));
    if (k == NULL) {
        perror("Muistin varaus kaarelle epäonnistui");
        exit(1);
    }
    k->etaisyys = etaisyys;
    k->kohde = sKohde;
    k->seuraava = sLahto->kaaret;
    sLahto->kaaret = k;
    
    // Lisätään myös kaari toiseen suuntaan, jotta graafi toimii kaksisuuntaisesti
    KAARI *k2 = sKohde->kaaret;
    while (k2) {
        if (strcmp(k2->kohde->nimi, lahto) == 0) {
            k2->etaisyys = etaisyys;
            return;
        }
        k2 = k2->seuraava;
    }
    k2 = (KAARI*)malloc(sizeof(KAARI));
    if (k2 == NULL) {
        perror("Muistin varaus kaarelle epäonnistui");
        exit(1);
    }
    k2->etaisyys = etaisyys;
    k2->kohde = sLahto;
    k2->seuraava = sKohde->kaaret;
    sKohde->kaaret = k2;
}

/////////////////////////////////////////////////////////////////////////
// Graafin tiedostosta lukeminen

// Lukee graafin tiedostosta, jossa tiedot ovat muodossa:
// Solmu1;Solmu2;Solmujen välinen etäisyys
// Ensimmäinen rivi on otsikko, joka ohitetaan.
GRAAFI* graafiLueTiedosto(GRAAFI *g, const char *tiedostonNimi) {
    FILE *Tiedosto = NULL;
    char rivi[RIVILKM] = "";

    if ((Tiedosto = fopen(tiedostonNimi, "r")) == NULL) {
        perror("Tiedoston avaamisessa virhe, lopetetaan");
        exit(0);
    }
    
    // Jos graafi on jo olemassa, vapautetaan se
    if (g != NULL) {
        graafiVapauta(g);
    }
    g = graafiLuo();
    
    // Ohitetaan otsikkorivi
    if (fgets(rivi, sizeof(rivi), Tiedosto) == NULL) {
        fclose(Tiedosto);
        return g;
    }
    
    //ehkä pitäisi skipata otsikko riviä?
    // Luetaan rivi kerrallaan
    while (fgets(rivi, sizeof(rivi), Tiedosto)) {
        char *solmu1 = NULL, *solmu2 = NULL, etaisyysStr = NULL;
        // Poistetaan mahdolliset rivinvaihtomerkit
        rivi[strcspn(rivi, "\r\n")] = '\0';
        
        if ((solmu1 = strtok(rivi, ";\n")) == NULL) {
            printf("Tiedoston pilkkominen ei onnistunut\n");
        }

        if ((solmu2 = strtok(NULL, ";\n")) == NULL) {
            printf("Tiedoston pilkkominen ei onnistunut\n");
            exit(0);
        }

        if ((etaisyysStr = strtok(NULL, ";\n")) == NULL) {
            printf("Tiedoston pilkkominen ei onnistunut\n");
            exit(0);
        }
        
        if (!solmu1 || !solmu2 || !etaisyysStr) {
            printf("Virheellinen rivi: %s\n", rivi);
            continue;
        }
        
        int etaisyys = atoi(etaisyysStr);
        graafiLisaaKaari(g, solmu1, solmu2, etaisyys);
    }
    
    fclose(Tiedosto);
    return g;
}

/////////////////////////////////////////////////////////////////////////
// Graafin solmun poistaminen

// Poistaa solmun ja kaikki siihen liittyvät kaaret graafista
GRAAFI* graafiPoistaSolmu(GRAAFI *g, const char *solmuNimi) {
    VERTEX *s = g->solmut, *edellinen = NULL;
    // Etsi poistettava solmu
    while (s) {
        if (strcmp(s->nimi, solmuNimi) == 0)
            break;
        edellinen = s;
        s = s->seuraava;
    }
    if (s == NULL) {
        printf("Solmua %s ei löytynyt.\n", solmuNimi);
        return g;
    }
    // Vapauta solmun kaaret
    vapautaKaaret(s->kaaret);
    // Poista solmu graafista
    if (edellinen == NULL)
        g->solmut = s->seuraava;
    else
        edellinen->seuraava = s->seuraava;
    free(s);
    
    // Poista kaikista muista solmuista kaaret, jotka osoittavat poistettuun solmuun
    s = g->solmut;
    while (s) {
        KAARI *k = s->kaaret, *ed = NULL;
        while (k) {
            if (strcmp(k->kohde->nimi, solmuNimi) == 0) {
                if (ed == NULL)
                    s->kaaret = k->seuraava;
                else
                    ed->seuraava = k->seuraava;
                free(k);
                break;  // oletetaan, että kyseinen kaari esiintyy vain kerran
            }
            ed = k;
            k = k->seuraava;
        }
        s = s->seuraava;
    }
    printf("Poistetaan solmua %s... Poisto suoritettu.\n", solmuNimi);
    return g;
}

/////////////////////////////////////////////////////////////////////////
// Lyhimmän reitin etsiminen Dijkstran algoritmilla

// Apufunktio: Laskee graafin solmujen lukumäärän
static int laskeSolmut(GRAAFI *g) {
    int n = 0;
    VERTEX *s = g->solmut;
    while (s) {
        n++;
        s = s->seuraava;
    }
    return n;
}

// Apufunktio: Hakee solmun indeksin taulukosta
static int etsiIndeksi(VERTEX **taulukko, int n, VERTEX *s) {
    for (int i = 0; i < n; i++) {
        if (taulukko[i] == s)
            return i;
    }
    return -1;
}

// Etsi lyhin reitti Dijkstran algoritmilla.
// Kirjoittaa reitin ja kokonaisetäisyyden tiedostoon (append-tilassa)
void graafiEtsiLyhinReitti(GRAAFI *g, const char *lahto, const char *kohde, const char *tiedostonNimi) {
    int n = laskeSolmut(g);
    if (n == 0) return;
    
    // Luo taulukko kaikista solmuista
    VERTEX **solmut = (VERTEX**)malloc(n * sizeof(VERTEX*));
    int idx = 0;
    VERTEX *s = g->solmut;
    while (s) {
        solmut[idx++] = s;
        s = s->seuraava;
    }
    
    // Alusta etäisyys-, edeltäjä- ja valintataulukot
    int *etaisyys = (int*)malloc(n * sizeof(int));
    int *edeltaja = (int*)malloc(n * sizeof(int));
    int *valittu = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        etaisyys[i] = INF;
        edeltaja[i] = -1;
        valittu[i] = 0;
    }
    
    // Etsi lähtö- ja kohdesolmujen indeksit
    int lahtoInd = -1, kohdeInd = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(solmut[i]->nimi, lahto) == 0)
            lahtoInd = i;
        if (strcmp(solmut[i]->nimi, kohde) == 0)
            kohdeInd = i;
    }
    if (lahtoInd == -1 || kohdeInd == -1) {
        printf("Lähtö- tai kohdesolmua ei löytynyt.\n");
        free(solmut); free(etaisyys); free(edeltaja); free(valittu);
        return;
    }
    
    etaisyys[lahtoInd] = 0;
    
    // Dijkstran algoritmi
    for (int i = 0; i < n; i++) {
        int min = INF, u = -1;
        for (int j = 0; j < n; j++) {
            if (!valittu[j] && etaisyys[j] < min) {
                min = etaisyys[j];
                u = j;
            }
        }
        if (u == -1) break;
        valittu[u] = 1;
        
        KAARI *kaari = solmut[u]->kaaret;
        while (kaari) {
            int v = etsiIndeksi(solmut, n, kaari->kohde);
            if (v != -1 && !valittu[v] && etaisyys[u] + kaari->etaisyys < etaisyys[v]) {
                etaisyys[v] = etaisyys[u] + kaari->etaisyys;
                edeltaja[v] = u;
            }
            kaari = kaari->seuraava;
        }
    }
    
    // Rakennetaan reitti taaksepäin
    if (etaisyys[kohdeInd] == INF) {
        printf("Reittiä solmujen %s ja %s välillä ei löytynyt.\n", lahto, kohde);
    } else {
        int *reitinIndeksit = (int*)malloc(n * sizeof(int));
        int reittiPituus = 0;
        int v = kohdeInd;
        while (v != -1) {
            reitinIndeksit[reittiPituus++] = v;
            v = edeltaja[v];
        }
        char reittiTeksti[500] = "";
        for (int i = reittiPituus - 1; i >= 0; i--) {
            strcat(reittiTeksti, solmut[reitinIndeksit[i]]->nimi);
            if (i > 0)
                strcat(reittiTeksti, " -> ");
        }
        char tuloste[600];
        sprintf(tuloste, "%s = %d\n", reittiTeksti, etaisyys[kohdeInd]);
        
        // Kirjoitetaan tuloste tiedostoon append-tilassa
        FILE *Tiedosto = fopen(tiedostonNimi, "a");
        if (Tiedosto) {
            Tiedostouts(tuloste, Tiedosto);
            fclose(Tiedosto);
        } else {
            perror("Reittitiedoston avaaminen epäonnistui");
        }
        free(reitinIndeksit);
    }
    
    free(solmut); free(etaisyys); free(edeltaja); free(valittu);
}

/////////////////////////////////////////////////////////////////////////
// Lopuksi graafin vapautus on jo toteutettu yllä graafiVapauta()-funktiolla.
