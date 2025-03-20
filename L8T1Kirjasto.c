#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "L8T1Kirjasto.h"
#include "TilastoFaktatKirjasto.h"
#include "MergeSortLaskevaJKirjasto.h"
#include "MergeSortNousevaJKirjasto.h"
#include "TIETO.h"
#include "Bintree.h"

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
    // printf("Tiedosto '%s' luettu.\n", tiedostonNimi);

    fclose(Tiedosto);

    return(pA);
    
}

void tallennaEtuperin(TIETO *pA, char *tiedostonNimi) {
    TIETO *ptr = pA;
    FILE *Tiedosto = NULL;

    
 
    //Virheentarkistus
    if ((Tiedosto = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen lukemiseen varten ei onnistunut, lopetetaan.");
        exit(0);
    }

    // While loop jolla tallennetaan tiedot tiedostoon
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->sukunimi, ptr->lukumaara);
        ptr = ptr->pSeuraava;
    }

    fclose(Tiedosto);

    return;

}
void tallennaTakaperin(TIETO *pA, char *tiedostonNimi) {
    TIETO *ptr = pA;
    FILE *Tiedosto = NULL;

    //Virheentarkistus
    if ((Tiedosto = fopen(tiedostonNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen lukemiseen varten ei onnistunut, lopetetaan.");
        exit(0);
    }
    // Loopilla siirrytään listan perälle
    while (ptr->pSeuraava != NULL) {
        ptr = ptr->pSeuraava;
    }

    
    // While loop jolla tallennetaan tiedot tiedostoon takaperin
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->sukunimi, ptr->lukumaara);
        ptr = ptr->pEdellinen;
    }
    fclose(Tiedosto);
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


//Arpoo satunnaisen tilastofaktan tulostettavaksi
void tilastoFaktaArpoja(TIETO *pA) {
    srand(time(NULL));

    // Arvotaan satunnainen luku
    int arpa = rand() % 6; // 0 - 5 (6 erilaista faktatyyppiä)

    switch (arpa) {
        case 0:
            keskiarvoLkm(pA);
            break;
        case 1:
            yliKeskiarvonLkm(pA);
            break;
        case 2:
            alleKeskiarvonLkm(pA);
            break;
        case 3:
            parillisetLkm(pA);
            break;
        case 4:
            parittomatLkm(pA);
            break;
        case 5:
            samatAlkukirjaimet(pA);
            break;
        default:
            printf("Jokin meni pieleen faktan arpomisen aikana.\n");
    }
}

int paaValikko() {
    int paaValinta = 0;
    printf("Valitse käsiteltävä tietorakenne:\n");
    printf("1) Linkitetty lista\n");
    printf("2) Binääripuu\n"); // Lisätty puuttuva \n
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &paaValinta); // Lisätty &
    getchar();
    return paaValinta;
}

int linkitettyValikko() {
    int linkitettyValinta = 0;
    printf("\nValitse haluamasi toiminto (linkitetty lista):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Tallenna lista etuperin\n");
    printf("3) Tallenna lista takaperin\n");
    printf("4) Tyhjennä lista\n");
    printf("5) Järjestä nousevaan järjestykseen\n");
    printf("6) Järjestä laskevaan järjestykseen\n");
    printf("7) Tilastofaktat\n");
    printf("0) Palaa\n");
    printf("Anna valintasi: ");
    scanf("%d", &linkitettyValinta);
    getchar();
    return(linkitettyValinta);
}

int binaariValikko() { // Poista parametri
    int iValinta = 0;
    printf("\nValitse haluamasi toiminto (binääripuu):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita puun arvot tiedostoon\n");
    printf("3) Syvyyshaku\n");
    printf("4) Leveyshaku\n");
    printf("5) Tulosta puumaisessa muodossa\n");
    printf("6)Joku muu hieno toiminto\n");
    printf("0) Palaa\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}
