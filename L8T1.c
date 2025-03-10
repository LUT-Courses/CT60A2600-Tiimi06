#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "L8T1Kirjasto.h"
#include "TilastoFaktatKirjasto.h"
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
        }else if (iValinta == 2)
        {
            if(pAlku != NULL){
                kirjoitettavaTNimiEtu = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                tallennaEtuperin(pAlku, kirjoitettavaTNimiEtu);
            }else{
                printf("Lue tiedosto ennen kirjoitusta!");
            }
            

        } else if(iValinta == 3){
            if(pAlku != NULL){
                kirjoitettavaTNimiTaka = kysyNimi("Anna kirjoitettavan tiedoston nimi");
                tallennaTakaperin(pAlku, kirjoitettavaTNimiTaka);
            }else{
                printf("Lue tiedosto ennen kirjoitusta!");
            }
            

        }else if(iValinta == 6){

            if(pAlku != NULL){
                tilastoFaktaApoja(pAlku);
            }else{
                printf("Lue tiedosto ennen tilastojen tulostusta!\n");
            }
            
        }else if(iValinta == 7){
            pAlku = tyhjennaLista(pAlku);
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
    
    return(0);
}