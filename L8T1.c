#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "L8T1Kirjasto.h"

int main(void) {
    // osoittaa linkitetty listaan ensimmäiseen alkion osoiteeseen
    TIETO *pAlku = NULL;
    char *luettavaTNimi = NULL;
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
            printf("Main tallennetaan etuperin");
            tallennaEtuperin(pAlku);

        } else if(iValinta == 3){
            printf("Main tallennetaan takaperin");

            tallennaTakaperin(pAlku);

        }else if(iValinta == 4){
            // kokeillaan vapauta
            pAlku = tyhjennaLista(pAlku);
        } else if(iValinta == 0){
            printf("Lopetetaan.\n");
            exit(0);
        } else{
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);
    

    printf("\n");

   
   
    // vapautetaan muistit
    free(iValinta);
    iValinta = NULL;
    free(luettavaTNimi);
    luettavaTNimi = NULL;

    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}