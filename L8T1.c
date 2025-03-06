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
            printf("Valinta1");
        }else if (iValinta == 2)
        {
            printf("valinta2");

        } else if(iValinta == 3){
            printf("Valinta3");
        }else if(iValinta == 4){
            printf("Valinta4");
        } else if(iValinta == 0){
            printf("Lopetetaan.\n");
            exit(0);
        } else{
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);
    

    luettavaTNimi = kysyNimi("Anna luettavan tiedoston nimi");
    printf("\n");

    // tämä aliohjlema pitää palauta osoitinmuutuja joka osoittaa linkitettylistaan ensimmäiseen alkion osoteesee
    pAlku = lueTiedosto(pAlku, luettavaTNimi);
    
    // kokeillaan tulosta
    tulostaAlkiot(pAlku);

    // kokeillaan vapauta
    pAlku = tyhjennaLista(pAlku);
    // vapautetaan muistit
    free(pAlku);
    pAlku = NULL;
    free(luettavaTNimi);
    luettavaTNimi = NULL;

    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}