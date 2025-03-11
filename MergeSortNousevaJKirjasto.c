#include "TIETO.h"
#include "MergeSortNousevaKirjasto.h"
#include <stdio.h>

TIETO *puolita(TIETO *pAlku) {
    TIETO *pNopea = pAlku;
    TIETO *pHidas = pAlku;

    /* 
    Siirtää nopeampaa osoitinta kaksi askelta eteenpäin, ja hitaampaa yhden askelen verran, kunnes saavutetaan listan loppua.
    */
   while (pNopea != NULL && pNopea -> pSeuraava != NULL && pNopea -> pSeuraava -> pSeuraava != NULL) {

    pNopea = pNopea -> pSeuraava -> pSeuraava;
    pHidas = pHidas -> pSeuraava; 
   }
   TIETO *valiAikainen = pHidas -> pSeuraava;
   pHidas -> pSeuraava = NULL;

   if()
}