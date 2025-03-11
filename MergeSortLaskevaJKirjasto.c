#include "MergeSortLaskevaJKirjasto.h"
#include "TIETO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TIETO *puolittaa(TIETO *pAlku) {
    TIETO *valiaikainen = NULL;
    TIETO *nopea = pAlku;
    TIETO *hidas = pAlku;

    // siihen menneessä kun nopea pääsee listan loppuun, niin hidas osoitin muutuja osoittaa jo linkitetty listaan keskimmäisen alkion osoitteeseen
    while (nopea != NULL && nopea->pSeuraava != NULL && nopea->pSeuraava->pSeuraava != NULL) {
        //nopea liikkuu kaksi askelta eteenpäin
        nopea = nopea->pSeuraava->pSeuraava;
        // hidas liikkuu yksi askelta eteenpäin
        hidas = hidas->pSeuraava;
    }
    // jaetaan lista kahteen osaan
    valiaikainen = hidas->pSeuraava;
    // irrotetaan puolikkaat
    hidas->pSeuraava = NULL;

    if (valiaikainen != NULL) {
        valiaikainen->pEdellinen = NULL;
    }
    
    return(valiaikainen);

}

TIETO *merge(TIETO *ekaOsa, TIETO *tokaOsa) {
  
    if (ekaOsa == NULL) {
        return tokaOsa;
    }
    if (tokaOsa == NULL) {
        return ekaOsa;
    }

    if (ekaOsa->lukumaara > tokaOsa->lukumaara) {
        
        ekaOsa->pSeuraava = merge(ekaOsa->pSeuraava, tokaOsa);
        if (ekaOsa->pSeuraava != NULL) {
            ekaOsa->pSeuraava->pEdellinen = ekaOsa;
        }
        ekaOsa->pEdellinen = NULL;
        return ekaOsa;
    } else if (ekaOsa->lukumaara < tokaOsa->lukumaara) {
      
        tokaOsa->pSeuraava = merge(ekaOsa, tokaOsa->pSeuraava);
        if (tokaOsa->pSeuraava != NULL) {
            tokaOsa->pSeuraava->pEdellinen = tokaOsa;
        }
        tokaOsa->pEdellinen = NULL;
        return tokaOsa;
    } else {
       
        if (strcmp(ekaOsa->sukunimi, tokaOsa->sukunimi) < 0) {
           
            ekaOsa->pSeuraava = merge(ekaOsa->pSeuraava, tokaOsa);
            if (ekaOsa->pSeuraava != NULL) {
                ekaOsa->pSeuraava->pEdellinen = ekaOsa;
            }
            ekaOsa->pEdellinen = NULL;
            return ekaOsa;
        } else {
     
            tokaOsa->pSeuraava = merge(ekaOsa, tokaOsa->pSeuraava);
            if (tokaOsa->pSeuraava != NULL) {
                tokaOsa->pSeuraava->pEdellinen = tokaOsa;
            }
            tokaOsa->pEdellinen = NULL;
            return tokaOsa;
        }
    }
}

TIETO *mergeSortLaskeva(TIETO *pA) {
  
    TIETO *toinenOsa = NULL;
    // mikäli linkitetty lista on tyhjä tai siinä on vain yksi alkio, niin se on jo sortattu. Tässä tapauksessa palautetaan takaisin sitä lista.
    if (pA == NULL || pA->pSeuraava == NULL) {
        return pA;
    }

    // puolitetaan lista kahteen osaan
    toinenOsa = puolittaa(pA);
    
    // sortataan molemmat puolikkaat rekursiivisesti
    pA = mergeSortLaskeva(pA);
    toinenOsa = mergeSortLaskeva(toinenOsa);

    // yhdistetään sortattu puolikkaat
    return merge(pA, toinenOsa);
}