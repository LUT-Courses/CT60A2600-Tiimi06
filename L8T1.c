#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "L8T1Kirjasto.h"
#include "TilastoFaktatKirjasto.h"
#include "MergeSortLaskevaJKirjasto.h"
#include "MergeSortNousevaJKirjasto.h"
#include "TIETO.h"

int main(void) {
    // osoittaa linkitetty listaan ensimmäiseen alkion osoiteeseen
    TIETO *pAlku = NULL;
    char *luettavaTNimi = NULL, *kirjoitettavaTNimiEtu = NULL, *kirjoitettavaTNimiTaka = NULL;
    int iValinta = 0;




    do
    {
        iValinta = valikko();
        if(iValinta == 1){
            luettavaTNimi = kysyNimi("Anna luettavan tiedoston nimi");
             // tämä aliohjlema pitää palauta osoitinmuutuja joka osoittaa linkitettylistaan ensimmäiseen alkion osoteesee
            pAlku = lueTiedosto(pAlku, luettavaTNimi);
            //muutos1
            free(luettavaTNimi);
            luettavaTNimi = NULL;
        }else if (iValinta == 2)
        {
            if(pAlku != NULL){
                kirjoitettavaTNimiEtu = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                tallennaEtuperin(pAlku, kirjoitettavaTNimiEtu);
                //muutos2
                free(kirjoitettavaTNimiEtu);
                kirjoitettavaTNimiEtu = NULL;
            }else{
                printf("Lue tiedosto ennen kirjoitusta!");
            }
            

        } else if(iValinta == 3){
            if(pAlku != NULL){
                kirjoitettavaTNimiTaka = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                tallennaTakaperin(pAlku, kirjoitettavaTNimiTaka);
                //muutos3
                free(kirjoitettavaTNimiTaka);
                kirjoitettavaTNimiTaka = NULL;
            }else{
                printf("Lue tiedosto ennen kirjoitusta!");
            }
            

        }
        else if(iValinta == 4) {
            // tähän pitää laittaa tyhjennä lista
            pAlku = tyhjennaLista(pAlku);
            printf("Lista tyhjennetty.\n");


            
            /*
            pAlku = mergeSortNouseva(pAlku);
            printf("Lista lajiteltu nousevaan järjestykseen.\n");
            */
        }
         else if(iValinta == 5) {
            // Järjestä nousevaan järjestykseen
            pAlku = mergeSortNouseva(pAlku);
            printf("Lista lajiteltu nousevaan järjestykseen.\n");
            //tyhjennaLista(pAlku); Listan tyhjennys, mutta ei läpäise codegradea.
            //pAlku = NULL;
            /*
            pAlku = mergeSortLaskeva(pAlku);
            printf("Lista lajitelty laskevaan järjestykseen.\n");
            */

        } else if(iValinta == 6){
            // Järjestä laskevaan järjestykseen
            pAlku = mergeSortLaskeva(pAlku);
            printf("Lista lajitelty laskevaan järjestykseen.\n");
            //tyhjennaLista(pAlku); Listan tyhjennys, mutta ei läpäise codegradea.
            //pAlku = NULL;

            /*
            if(pAlku != NULL){
                tilastoFaktaArpoja(pAlku);
            }else{
                printf("Lue tiedosto ennen tilastojen tulostusta!\n");
            }
            */
        } else if(iValinta == 7){
            //Tilastofakta

            if(pAlku != NULL){
                tilastoFaktaArpoja(pAlku);
            }else{
                printf("Lue tiedosto ennen tilastojen tulostusta!\n");
            }
            

        } else if(iValinta == 0){
            printf("Lopetetaan.\n");

        } else{
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n"); 
    } while (iValinta != 0);
    


   
    printf("Kiitos ohjelman käytöstä.\n");

    // vapautetaan muistit
    free(luettavaTNimi);
    luettavaTNimi = NULL;

    free(kirjoitettavaTNimiEtu);
    kirjoitettavaTNimiEtu = NULL;

    free(kirjoitettavaTNimiTaka);
    kirjoitettavaTNimiTaka = NULL;
    // ehkä korjaa ongelman?
    pAlku = tyhjennaLista(pAlku);
    
    return(0);
}

//TÄMÄ ON KORJATTUS VERSIO