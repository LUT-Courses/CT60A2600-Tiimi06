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
   TIETO *pValiaikainen = pHidas -> pSeuraava;
   pHidas -> pSeuraava = NULL;

   if(pValiaikainen != NULL) {
    pValiaikainen -> pEdellinen = NULL;
   }

   return pValiaikainen;
}

TIETO *yhdista(TIETO *pEnsimmainen, TIETO *pToinen) {
    //Jos jompikumpi listoista on tyhjä, palauta toinen
    if (pEnsimmainen == NULL) {
        return pToinen;
    }
    if (pToinen == NULL) {
        return pEnsimmainen;
    }
    //Valitse pienempi arvo
    if(pEnsimmainen -> lukumaara < pToinen -> lukumaara) {
        pEnsimmainen -> pSeuraava = yhdista(pEnsimmainen -> pSeuraava, pToinen);
        if (pEnsimmainen -> pSeuraava != NULL) {
            pEnsimmainen -> pSeuraava -> pEdellinen = pEnsimmainen;
        }
        pEnsimmainen -> pEdellinen = NULL;
        return pEnsimmainen;
    }else{
        pToinen -> pSeuraava = yhdista(pEnsimmainen, pToinen -> pSeuraava);
        if(pToinen -> pSeuraava != NULL) {
            pToinen -> pSeuraava -> pEdellinen = pToinen;
        }
        pToinen -> pEdellinen = NULL;
        return pToinen;
    }
}

