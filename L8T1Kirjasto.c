#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "L8T1Kirjasto.h"

char *kysyNimi(char *pPromtti) {
    char valiaikainenMuutuja[TIEDOSTONKOKO] = "";
    char *valiaikainenTaulukko = NULL;

    printf("%s: ", pPromtti);
    scanf("%s", valiaikainenMuutuja);
    getchar();

    //varataan muisti väliaikaiselle taulukolle
    if ((valiaikainenTaulukko = (char*)malloc((strlen(valiaikainenMuutuja) + 1) * sizeof(char))) == NULL) {
        perror("Muistin varaaminen väliaikaiselle nimi taulukolle ei onnistunut, lopetetaan.");
        exit(0);
    }

    strcpy(valiaikainenTaulukko, valiaikainenMuutuja);

    return(valiaikainenTaulukko);
}

TIETO *lisaaAlkio(TIETO *pAlku, char *sukuNimi, int lkm) {
    TIETO *pUusi = NULL, *ptr = NULL; //luodaan uusi alkio talennetaan sen pUusi. Ptr on liukuri, joka auttaa meitä lisäämään uusi alkio listaan.

    // varataan uudelle alkiolle muistia
    if ((pUusi = (TIETO*)malloc(sizeof(TIETO))) == NULL) {
        perror("Muistin varaaminen uudelle linkitettylistan alkiolle ei onnistunut, lopetetaan.");
        exit(0);
    }

    // määritetään uuden alkion/olion jäsenmuutujat
    strcpy(pUusi->sukunimi, sukuNimi);
    pUusi->lukumaara = lkm;
    pUusi->pSeuraava = NULL;
    pUusi->pEdellinen = NULL;

    // lisätään uusi alkio/olio linkitetty listaan
    //tarkistetaan onko lista tyhjä, jos on. Asetetaan sen ensimmäiseksi arvoksi uusiluotu olio
    // jos listassa on jotain laitetaan uusi alkio listan viimeiseksi jäseneksi.
    if (pAlku == NULL) {
        pAlku = pUusi;
    } else {
        //etsitään listan viimeinen alkio while loopin avulla
        ptr = pAlku;
        while (ptr->pSeuraava != NULL) {
            ptr = ptr->pSeuraava;
        }

        // laitetaan listan viimeisen alkion jäsenmuutuja "pSeuraava" osoittamaan uuden alkion osoitteeseen
        // Ja laitetaan uuden alkion jäsenmuutuja "pEdellinen" osoittamaan linkitetty listan viimeisen alkion osoitteeseen
        ptr->pSeuraava = pUusi;
        pUusi->pEdellinen = ptr;
    }

    return(pAlku);
}

TIETO *lueTiedosto(TIETO *pA, char *tiedostonNimi) {
    FILE *Tiedosto = NULL;
    char aRivi[TIEDOSTONKOKO] = "", *p1 = NULL, *p2 = NULL;
    int lukumaara = 0;

    if ((Tiedosto = fopen(tiedostonNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen lukemiseen varten ei onnistunut, lopetetaan.");
        exit(0);
    }

    // luetiedosto rivin pois
    fgets(aRivi, TIEDOSTONKOKO, Tiedosto);

    while (fgets(aRivi, TIEDOSTONKOKO, Tiedosto) != NULL) {

        // tarkisetaan ensin että luettu rivi ei ole rivinvaihto
        if (aRivi[0] != '\n') {

            if ((p1 = strtok(aRivi, ";")) == NULL) {
                printf("Rivin pilkkominen ei onnistunut, lopetetaan.\n");
                exit(0);
            }


            if ((p2 = strtok(NULL, ";")) == NULL) {
                printf("Rivin pilkkominen ei onnistunut, lopetetaan.\n");
                exit(0);
            }

            // cästätään p2 tietotyyppi integriksi
            lukumaara = atoi(p2);

            pA = lisaaAlkio(pA, p1, lukumaara);

            // luo sellainen aliohjelma lisaaAlkio(TIETO *pA, char *sukuNimi, int lukuMaara), tämä palauta pA
        }
    }

    fclose(Tiedosto);

    return(pA);
    
}

void tulostaAlkiot(TIETO *pA) {
    TIETO *ptr = pA;

    while (ptr != NULL) {
        printf("Sukunimi: %s, Määrä: %d.\n", ptr->sukunimi, ptr->lukumaara);
        ptr = ptr->pSeuraava;
    }

    return;

}


TIETO *tyhjennaLista(TIETO *pA) {
    TIETO *ptr = pA;

    while (ptr != NULL) {
        pA = ptr->pSeuraava;
        free(ptr);
        ptr = pA;
    }

    return(pA);
}
