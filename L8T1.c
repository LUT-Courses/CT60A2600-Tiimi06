#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L8T1Kirjasto.h"
#include "TilastoFaktatKirjasto.h"
#include "MergeSortLaskevaJKirjasto.h"
#include "MergeSortNousevaJKirjasto.h"
#include "TIETO.h"
#include "Bintree.h"


int main(void) {
    TIETO *pAlku = NULL;
    BNODE *pBinJuuri = NULL; // Lisätty binääripuun juuri
    char *luettavaTNimi = NULL, *kirjoitettavaTNimiEtu = NULL, *kirjoitettavaTNimiTaka = NULL;
    int iValinta = 0;
    int toinenValinta = 0;
    int kolmasValinta = 0;

    
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
                        tilastoFaktaArpoja(pAlku);
                    } else {
                        printf("Lue tiedosto ennen tilastojen tulostusta!\n");
                    }
                } 
                else if (toinenValinta != 0) {
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
                        printf("Anna kirjoitettavan tiedoston nimi: ");
                        scanf("%s", tiedostoNimi);
                        binaariKirjoitaJarjestyksessa(pBinJuuri, tiedostoNimi);
                        break;
                        
                        // Syvyyshaun käsittely
                        case 3: {
                            char loydettyNimi[50] = "";
                            int hakuLuku;
                            if (pBinJuuri == NULL) {
                                printf("Lue tiedosto ensin!\n");
                                break;
                            }
                            
                            printf("Anna etsittävä lukumäärä: ");
                            scanf("%d", &hakuLuku);
                            printf("Anna kirjoitettavan tiedoston nimi: ");
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
                            char hakuNimi[50];
                            int loydettyLkm = 0;
                            if (pBinJuuri == NULL) {
                                printf("Lue tiedosto ensin!\n");
                                break;
                            }
                            
                            printf("Anna etsittävä nimi: ");
                            scanf("%s", hakuNimi);
                            printf("Anna kirjoitettavan tiedoston nimi: ");
                            scanf("%s", tiedostoNimi);
                            
                            if (leveysHaku(pBinJuuri, hakuNimi, tiedostoNimi, &loydettyLkm)) {
                                printf("Puussa on arvo '%s %d'.\n", hakuNimi, loydettyLkm);
                            } else {
                                printf("Puussa ei ole arvoa '%s'.\n", hakuNimi);
                            }
                            break;
                        }
                        
                    case 0: // Palaa päävalikkoon
                        printf("Palataan päävalikkoon.\n");
                        break;
                        
                    default:
                        printf("Virheellinen valinta!\n");
                }
            } while(kolmasValinta != 0);
        }
        
    } while(iValinta != 0); // Päävalikko loppuu

    printf("Kiitos ohjelman käytöstä.\n");
    pAlku = tyhjennaLista(pAlku);
    binaariVapauta(pBinJuuri);

    return 0;

}