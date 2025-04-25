#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MainKirjasto.h"
#include "TilastoFaktatLista.h"
#include "MergeSortLaskevaJKirjasto.h"
#include "MergeSortNousevaJKirjasto.h"
#include "TIETO.h"
#include "Bintree.h"
#include "Graafi.h"

int leveysHaku(BSOLMU *pJuuri, const char *pHaettavaNimi, const char *pTiedostonNimi, int *loydettyLkm);
void binaariKirjoitaJarjestyksessa(BSOLMU *pJuuri, const char *pTiedostonNimi);
int syvyysHaku(BSOLMU *pJuuri, int iHaettava, const char *pTiedostonNimi, char *loydettyNimi);

int main(void) {
    TIETO *pAlku = NULL;
    BSOLMU *pBinJuuri = NULL;
    GRAAFI* pGraafi = NULL;

    char *luettavaTNimi = NULL, *kirjoitettavaTNimiEtu = NULL, *kirjoitettavaTNimiTaka = NULL, *poistettavaArvo = NULL;
    char *graafiTNimi = NULL;
    char poistettavaNimi[NIMIPITUUS] = "";

    int iValinta = 0, toinenValinta = 0, kolmasValinta = 0, neljasValinta = 0;
    int onNumero = 1, lukumaara = 0;

    char lahto[RIVILKM] = "", kohde[RIVILKM] = "", solmu[RIVILKM] = "";
    char reittiTiedosto[RIVILKM] = "", lahtoSolmu[RIVILKM] = "", kohdeSolmu[RIVILKM] = "";
    int etaisyys = 0;

    do {
        iValinta = paaValikko();

        if (iValinta == 1) { // Linkitetty lista
            do {
                toinenValinta = linkitettyValikko();

                if (toinenValinta == 1) {
                    luettavaTNimi = kysyNimi("Anna luettavan tiedoston nimi");
                    pAlku = lueTiedosto(pAlku, luettavaTNimi);
                    free(luettavaTNimi);
                    luettavaTNimi = NULL;
                } else if (toinenValinta == 2) {
                    if (pAlku != NULL) {
                        kirjoitettavaTNimiEtu = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                        tallennaEtuperin(pAlku, kirjoitettavaTNimiEtu);
                        free(kirjoitettavaTNimiEtu);
                        kirjoitettavaTNimiEtu = NULL;
                    } else {
                        printf("Lue tiedosto ennen kirjoitusta!\n");
                    }
                } else if (toinenValinta == 3) {
                    if (pAlku != NULL) {
                        kirjoitettavaTNimiTaka = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                        tallennaTakaperin(pAlku, kirjoitettavaTNimiTaka);
                        free(kirjoitettavaTNimiTaka);
                        kirjoitettavaTNimiTaka = NULL;
                    } else {
                        printf("Lue tiedosto ennen kirjoitusta!\n");
                    }
                } else if (toinenValinta == 4) {
                    pAlku = tyhjennaLista(pAlku);
                    printf("Lista tyhjennetty.\n");
                } else if (toinenValinta == 5) {
                    pAlku = mergeSortNouseva(pAlku);
                    printf("Lista lajiteltu nousevaan järjestykseen.\n");
                } else if (toinenValinta == 6) {
                    pAlku = mergeSortLaskeva(pAlku);
                    printf("Lista lajiteltu laskevaan järjestykseen.\n");
                } else if (toinenValinta == 7) {
                    if (pAlku != NULL) {
                        tilastoFaktaArpojaLista(pAlku);
                    } else {
                        printf("Lue tiedosto ennen tilastojen tulostusta!\n");
                    }
                } else if (toinenValinta == 0) {
                    printf("Palataan päävalikkoon.\n\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }

            } while (toinenValinta != 0);

        } else if (iValinta == 2) { // Binääripuu
            do {
                kolmasValinta = binaariValikko();
                char tiedostoNimi[100];
                int hakuLuku;
                char hakuNimi[50];

                switch (kolmasValinta) {
                    case 1:
                        printf("Anna luettavan tiedoston nimi: ");
                        scanf("%s", tiedostoNimi);
                        pBinJuuri = binaariLueTiedosto(pBinJuuri, tiedostoNimi);
                        break;

                    case 2:
                        if (pBinJuuri == NULL) {
                            printf("Lue tiedosto ensin!\n");
                            break;
                        }
                        printf("Anna kirjoittettavan tiedoston nimi: ");
                        scanf("%s", tiedostoNimi);
                        binaariKirjoitaJarjestyksessa(pBinJuuri, tiedostoNimi);
                        break;

                    case 3: {
                        char loydettyNimi[50] = "";
                        if (pBinJuuri == NULL) {
                            printf("Lue tiedosto ensin!\n");
                            break;
                        }
                        printf("Anna etsittävä arvo: ");
                        scanf("%d", &hakuLuku);
                        printf("Anna kirjoittettavan tiedoston nimi: ");
                        scanf("%s", tiedostoNimi);

                        if (syvyysHaku(pBinJuuri, hakuLuku, tiedostoNimi, loydettyNimi)) {
                            printf("Puussa on arvo '%s %d'.\n", loydettyNimi, hakuLuku);
                        } else {
                            printf("Puussa ei ole arvoa '%d'.\n", hakuLuku);
                        }
                        break;
                    }

                    case 4: {
                        int loydettyLkm = 0;
                        if (pBinJuuri == NULL) {
                            printf("Lue tiedosto ensin!\n");
                            break;
                        }
                        printf("Anna etsittävä arvo: ");
                        scanf("%s", hakuNimi);
                        printf("Anna kirjoittettavan tiedoston nimi: ");
                        scanf("%s", tiedostoNimi);

                        if (leveysHaku(pBinJuuri, hakuNimi, tiedostoNimi, &loydettyLkm)) {
                            printf("Puussa on arvo '%s %d'.\n", hakuNimi, loydettyLkm);
                        } else {
                            printf("Puussa ei ole arvoa '%s'.\n", hakuNimi);
                        }
                        break;
                    }

                    case 5: {
                        if (pBinJuuri == NULL) {
                            printf("Lue tiedosto ensin!\n");
                            break;
                        }
                        int iHaettavaArvo;
                        printf("Anna etsittävä arvo (numero): ");
                        scanf("%d", &iHaettavaArvo);

                        BSOLMU *tulos = binaariHaku(pBinJuuri, iHaettavaArvo);
                        if (tulos != NULL) {
                            printf("Arvo löytyi: %s, %d\n", tulos->name, tulos->count);
                        } else {
                            printf("Arvoa %d ei löytynyt binääripuusta.\n", iHaettavaArvo);
                        }
                        break;
                    }

                    case 6:
                        if (pBinJuuri == NULL) {
                            printf("Lue tiedosto ensin!\n");
                            break;
                        }
                        onNumero = 1;
                        poistettavaArvo = kysyNimi("Anna poistettava arvo");

                        for (int i = 0; poistettavaArvo[i] != '\0'; i++) {
                            if (!isdigit(poistettavaArvo[i])) {
                                onNumero = 0;
                                break;
                            }
                        }

                        if (onNumero) {
                            int arvo = atoi(poistettavaArvo);
                            if (etsiNimiLukumaaranPerusteella(pBinJuuri, arvo, poistettavaNimi)) {
                                printf("Poistetaan arvoa %s, %d... ", poistettavaNimi, arvo);
                            } else {
                                printf("Lukua %d vastaavaa solmua ei löytynyt.\n", arvo);
                                free(poistettavaArvo);
                                break;
                            }
                            pBinJuuri = binaariPoistaLukumaara(pBinJuuri, arvo);
                            printf("Poisto suoritettu.\n");
                        } else {
                            if (etsiLukumaaraNimenPerusteella(pBinJuuri, poistettavaArvo, &lukumaara)) {
                                printf("Poistetaan arvoa %s, %d... ", poistettavaArvo, lukumaara);
                            } else {
                                printf("Nimeä '%s' vastaavaa solmua ei löytynyt.\n", poistettavaArvo);
                                free(poistettavaArvo);
                                break;
                            }
                            pBinJuuri = binaariPoistaNimi(pBinJuuri, poistettavaArvo);
                            printf("Poisto suoritettu.\n");
                        }
                        free(poistettavaArvo);
                        poistettavaArvo = NULL;
                        break;

                    case 7:
                        if (pBinJuuri != NULL) {
                            tulostaPuu(pBinJuuri, 0);
                        } else {
                            printf("Lue tiedosto ennen puun tulostusta!\n");
                        }
                        break;

                    case 8:
                        if (pBinJuuri != NULL) {
                            tilastoFaktaArpojaBin(pBinJuuri);
                        } else {
                            printf("Lue tiedosto ennen tilastojen tulostusta!\n");
                        }
                        break;

                    case 0:
                        printf("Palataan päävalikkoon.\n\n");
                        break;

                    default:
                        printf("Virheellinen valinta!\n");
                }
            } while (kolmasValinta != 0);

        } else if (iValinta == 3) { // Graafi
            do {
                neljasValinta = graafiValikko();

                switch (neljasValinta) {
                    case 1:
                        graafiTNimi = kysyNimi("Anna luettavan tiedoston nimi");
                        printf("Luetaan tiedosto: %s\n", graafiTNimi);
                        if (pGraafi != NULL) {
                            graafiVapauta(pGraafi);
                        }
                        pGraafi = graafiLuo();
                        pGraafi = graafiLueTiedosto(pGraafi, graafiTNimi);
                        free(graafiTNimi);
                        graafiTNimi = NULL;
                        break;

                    case 2:
                        printf("Anna kaari (lähtösolmu;kohdesolmu;etäisyys): ");
                        scanf("%[^;];%[^;];%d", lahto, kohde, &etaisyys);
                        getchar();
                        graafiLisaaKaari(pGraafi, lahto, kohde, etaisyys);
                        break;

                    case 3:
                        printf("Anna poistettava solmu: ");
                        scanf("%s", solmu);
                        getchar();
                        pGraafi = graafiPoistaSolmu(pGraafi, solmu);
                        break;

                    case 4: {
                        int tiedostoKysyty = 0;
                        if (!tiedostoKysyty) {
                            printf("Anna reittitiedoston nimi: ");
                            scanf("%s", reittiTiedosto);
                            getchar();
                            tiedostoKysyty = 1;
                        } else {
                            printf("Käytetään edellistä reittitiedoston nimeä: %s\n", reittiTiedosto);
                        }
                        printf("Anna lähtösolmu: ");
                        scanf("%s", lahtoSolmu);
                        getchar();
                        printf("Anna kohdesolmu: ");
                        scanf("%s", kohdeSolmu);
                        getchar();
                        graafiEtsiLyhinReitti(pGraafi, lahtoSolmu, kohdeSolmu, reittiTiedosto);
                        break;
                    }

                    case 5:
                        // tilastofakta toiminto (ei toteutettu tässä)
                        break;

                    case 0:
                        printf("Palataan päävalikkoon.\n\n");
                        break;

                    default:
                        printf("Virheellinen valinta!\n");
                        break;
                }
            } while (neljasValinta != 0);

        } else if (iValinta == 0) {
            printf("Lopetetaan.\n\n");
        }

    } while (iValinta != 0);

    printf("Kiitos ohjelman käytöstä.\n");

    // Vapautetaan muistialueet
    pAlku = tyhjennaLista(pAlku);
    binaariVapauta(pBinJuuri);
    if (pGraafi != NULL) {
        graafiVapauta(pGraafi);
    }

    return 0;
}