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
        /* code */
    } while (iValinta == 0);
    

    luettavaTNimi = kysyNimi("Anna luettavan tiedoston nimi");
    printf("\n");

    // tämä aliohjlema pitää palauta osoitinmuutuja joka osoittaa linkitettylistaan ensimmäiseen alkion osoteesee
    pAlku = lueTiedosto(pAlku, luettavaTNimi);
    
    // kokeillaan tulosta
    tulostaAlkiot(pAlku);

    // kokeillaan vapauta
    pAlku = tyhjennaLista(pAlku);
    // vapautetaan muistit
    free(luettavaTNimi);
    luettavaTNimi = NULL;

    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}