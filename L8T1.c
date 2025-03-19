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
                    luettavaTNimi = kysyNimi("Anna luettavan tiedoston nimi: ");
                    pAlku = lueTiedosto(pAlku, luettavaTNimi);
                    free(luettavaTNimi);
                    luettavaTNimi = NULL;
                } 
                else if (toinenValinta == 2) {
                    if (pAlku != NULL) {
                        kirjoitettavaTNimiEtu = kysyNimi("Anna kirjoitettavan tiedoston nimi: ");
                        tallennaEtuperin(pAlku, kirjoitettavaTNimiEtu);
                        free(kirjoitettavaTNimiEtu);
                        kirjoitettavaTNimiEtu = NULL;
                    } else {
                        printf("Lue tiedosto ennen kirjoitusta!\n");
                    }
                } 
                else if (toinenValinta == 3) {
                    if(pAlku != NULL) {
                        kirjoitettavaTNimiTaka = kysyNimi("Anna kirjoitettavan tiedoston nimi: ");
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
        } else if (iValinta == 2) {
            do {
                if (kolmasValinta == 1) {

                } else if(kolmasValinta == 2) {

                } else if(kolmasValinta == 3) {
                    
                } else if(kolmasValinta == 4) {
                    
                } else if(kolmasValinta == 5) {
                    
                } else if(kolmasValinta == 6) {
                    
                } else if(kolmasValinta == 0) {
                    
                } 
            }while (kolmasValinta != 0);
        }
        
    } while(iValinta != 0); // Päävalikko loppuu

    printf("Kiitos ohjelman käytöstä.\n");
    pAlku = tyhjennaLista(pAlku);
    
    return 0;
}