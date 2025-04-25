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

//Lisään kommentin tähän, koska jostain syystä osa puskusta toimi edellisella kerralla ja osa ei puskennut.

int leveysHaku(BNODE *pJuuri, const char *pHaettavaNimi, const char *pTiedostonNimi, int *loydettyLkm);
void binaariKirjoitaJarjestyksessa(BNODE *pJuuri, const char *pTiedostonNimi);
int syvyysHaku(BNODE *pJuuri, int iHaettava, const char *pTiedostonNimi, char *loydettyNimi);

int main(void) {
    TIETO *pAlku = NULL;
    BNODE *pBinJuuri = NULL; // Lisätty binääripuun juuri
    GRAAFI* pGraafi = NULL;
    
    char *luettavaTNimi = NULL, *kirjoitettavaTNimiEtu = NULL, *kirjoitettavaTNimiTaka = NULL, *poistettavaArvo = NULL;
    char *graafiTNimi = NULL;

    
    char poistettavaNimi[NIMIPITUUS] = "";
  
    int iValinta = 0;
    int toinenValinta = 0;
    int kolmasValinta = 0;
    int neljasValinta = 0; //graph valikko
    int onNumero = 1;
    int lukumaara = 0;

    // graafin muuttujat
    char lahto[RIVILKM] = "", kohde[RIVILKM] = "", solmu[RIVILKM] = "";
    char reittiTiedosto[RIVILKM] = "", lahtoSolmu[RIVILKM] = "", kohdeSolmu[RIVILKM] = "";
    int etaisyys = 0;
    
    

    
    do {
        iValinta = paaValikko();
        
        if (iValinta == 1) { // Linkitetyn listan valikko
            do {
                toinenValinta = linkitettyValikko();
                
                if (toinenValinta == 1) {
                    luettavaTNimi = kysyNimi("Anna luettavan tiedoston nimi");
                    pAlku = lueTiedosto(pAlku, luettavaTNimi);
                    free(luettavaTNimi);
                    luettavaTNimi = NULL;
                } 
                else if (toinenValinta == 2) {
                    if (pAlku != NULL) {
                        kirjoitettavaTNimiEtu = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                        tallennaEtuperin(pAlku, kirjoitettavaTNimiEtu);
                        free(kirjoitettavaTNimiEtu);
                        kirjoitettavaTNimiEtu = NULL;
                    } else {
                        printf("Lue tiedosto ennen kirjoitusta!\n");
                    }
                } 
                else if (toinenValinta == 3) {
                    if(pAlku != NULL) {
                        kirjoitettavaTNimiTaka = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                        tallennaTakaperin(pAlku, kirjoitettavaTNimiTaka);
                        free(kirjoitettavaTNimiTaka);
                        kirjoitettavaTNimiTaka = NULL;
                    } else {
                        printf("Lue tiedosto ennen kirjoitusta!\n");
                    }
                } 
                else if (toinenValinta == 4) {
                    pAlku = tyhjennaLista(pAlku);
                    printf("Lista tyhjennetty.\n");
                } 
                else if (toinenValinta == 5) {
                    pAlku = mergeSortNouseva(pAlku);
                    printf("Lista lajiteltu nousevaan järjestykseen.\n");
                } 
                else if (toinenValinta == 6) {
                    pAlku = mergeSortLaskeva(pAlku);
                    printf("Lista lajiteltu laskevaan järjestykseen.\n");
                } 
                else if (toinenValinta == 7) {
                    if(pAlku != NULL) {
                        tilastoFaktaArpojaLista(pAlku);                    
                    } else {
                        printf("Lue tiedosto ennen tilastojen tulostusta!\n");
                    }
                } else if (toinenValinta == 0) {
                    printf("Palataan päävalikkoon.\n\n");
                } 
                else{
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }
                
            } while (toinenValinta != 0); // Linkitetyn listan valikko loppuu
        } else if (iValinta == 2) { // Binääripuun valikko
            do {
                kolmasValinta = binaariValikko();
                char tiedostoNimi[100];
                int hakuLuku;
                char hakuNimi[50];
                
                switch(kolmasValinta) {
                    case 1: // Lue tiedosto
                        printf("Anna luettavan tiedoston nimi: ");
                        scanf("%s", tiedostoNimi);
                        pBinJuuri = binaariLueTiedosto(pBinJuuri, tiedostoNimi);
                        break;
                        
                    case 2: // Kirjoita tiedostoon
                        if (pBinJuuri == NULL) {
                            printf("Lue tiedosto ensin!\n");
                            break;
                        }
                        printf("Anna kirjoittettavan tiedoston nimi: "); //Codegradessa typo niin laitoin tähänkin typon
                        scanf("%s", tiedostoNimi);
                        binaariKirjoitaJarjestyksessa(pBinJuuri, tiedostoNimi);
                        break;
                        
                        // Syvyyshaun käsittely
                        case 3: {
                            char loydettyNimi[50] = "";
                            if (pBinJuuri == NULL) {
                                printf("Lue tiedosto ensin!\n");
                                break;
                            }
                            
                            printf("Anna etsittävä arvo: "); //Ei jostain syystä puske kunnolla codegradessa
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

                        // Leveyshaun käsittely
                        case 4: {
                            int loydettyLkm = 0;
                            if (pBinJuuri == NULL) {
                                printf("Lue tiedosto ensin!\n");
                                break;
                            }
                            
                            printf("Anna etsittävä arvo: ");
                            scanf("%s", hakuNimi);
                            printf("Anna kirjoittettavan tiedoston nimi: "); //Codegraden typo
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

                            BNODE *tulos = binaariHaku(pBinJuuri, iHaettavaArvo);

                            if (tulos != NULL) {


                                printf("Arvo löytyi: %s, %d\n", tulos->name, tulos->count);
                            } else {

                                printf("Arvoa %d ei löytynyt binääripuusta.\n", iHaettavaArvo);
                            }

                        break;
                        }

                        case 6:
                            //tarkistetaan ensin että binääripuun juuri ei ole tyhjä
                            if (pBinJuuri == NULL) {
                                printf("Lue tiedosto ensin!\n");
                                break;
                            }

                            // Alusta onNumero aina 1 ennen syötteen tarkistusta
                            onNumero = 1;
                            // kysy käyttäjältä poistettava arvo, syöte voi olla joko numero tai kirjain
                            poistettavaArvo = kysyNimi("Anna poistettava arvo");

                            // käydään kaikki poistettavaArvon alkiot, jos yksi niistä on merkki niin
                            //asetetaan onNumero =1; 
                            for (int i = 0; poistettavaArvo[i] != '\0'; i++) {
                                if (!isdigit(poistettavaArvo[i])) {
                                    onNumero = 0;
                                    break;
                                }
                            }
                            // poisto numerolla
                            if (onNumero) {
                                
                                int arvo = atoi(poistettavaArvo);
                
                                // Haetaan ensin solmun nimi, jonka count vastaa annettua lukua
                                if (etsiNimiLukumaaranPerusteella(pBinJuuri, arvo, poistettavaNimi)) {
                                    printf("Poistetaan arvoa %s, %d... ", poistettavaNimi, arvo);
            
                                } else {
                                    printf("Lukua %d vastaavaa solmua ei löytynyt, poistaminen ei suoritettu.\n", arvo);
                                    free(poistettavaArvo);
                                    break;
                                }
                                pBinJuuri = binaariPoistaLukumaara(pBinJuuri, arvo);
                                printf("Poisto suoritettu.\n");
                                
                            // poisto nimellä
                            } else {
                                if (etsiLukumaaraNimenPerusteella(pBinJuuri, poistettavaArvo, &lukumaara)) {
                                    // Jos nimi löytyy tulostetaan myös sen lukumäärä
                                    printf("Poistetaan arvoa %s, %d... ", poistettavaArvo, lukumaara);
                                } else {
                                    // Jos nimeä ei löytynyt ollenkaan
                                    printf("Nimeä '%s' vastaavaa solmua ei löytynyt, poistaminen ei suoritettu.\n", poistettavaArvo);
                                    free(poistettavaArvo);
                                    break;
                                }
                               
                                pBinJuuri = binaariPoistaNimi(pBinJuuri, poistettavaArvo);
                                printf("Poisto suoritettu.\n");
                            }
                            //vapautetaan muistit
                            free(poistettavaArvo);
                            poistettavaArvo = NULL;
                            /*
                            free(poistettavaNimi);
                            poistettavaNimi = NULL;
                            */
                            break;
                        case 7: {
                            if(pBinJuuri != NULL) {
                            tulostaPuu(pBinJuuri, 0);
                            
                            } else {
                                printf("Lue tiedosto ennen puun tulostusta!\n");
                            }
                        break;
                        }

                        case 8: {
                            if(pBinJuuri != NULL) {
                            tilastoFaktaArpojaBin(pBinJuuri);
                            } else {
                                printf("Lue tiedosto ennen tilastojen tulostusta!\n");
                            }
                            break;
                        }

                        
                    case 0: // Palaa päävalikkoon
                        printf("Palataan päävalikkoon.\n\n");
                        break;
                        
                    default:
                        printf("Virheellinen valinta!\n");
                }
            } while(kolmasValinta != 0);

        } else if (iValinta == 3) {
            do {
                neljasValinta = graafiValikko();
                //sisäinen valikko
                switch(neljasValinta) {
                    
                    case 1:
                        graafiTNimi = kysyNimi("Anna luettavan tiedoston nimi");
                        printf("Luetaan tiedosto: %s\n", graafiTNimi); // Debug-tulostus
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
                             int tiedostoKysyty = 0;  // Lippu, joka kertoo onko nimi jo kysytty
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
                        //tilastofakta toiminto
                        break;
                    
                    case 0: // Palaa päävalikkoon
                        printf("Palataan päävalikkoon.\n\n");
                        break;
                    
                    default:
                        printf("Virheellinen valinta!\n");
    
                }
    

            } while(neljasValinta != 0);
           
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n\n"); 
        }
        
    } while(iValinta != 0); // Päävalikko loppuu

    printf("Kiitos ohjelman käytöstä.");
    pAlku = tyhjennaLista(pAlku);
    binaariVapauta(pBinJuuri);
    if (pGraafi != NULL) {
        graafiVapauta(pGraafi);
    }

    return 0;

}