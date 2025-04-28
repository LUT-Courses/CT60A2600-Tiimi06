#include "MergeSortNousevaJKirjasto.h"
#include "TIETO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Apufunktio listan puolittamiseen
TIETO *nousevaPuolita(TIETO *pAlku) {
    TIETO *pNopea = pAlku;
    TIETO *pHidas = pAlku;

    while (pNopea != NULL && pNopea->pSeuraava != NULL && pNopea->pSeuraava->pSeuraava != NULL) {
        pNopea = pNopea->pSeuraava->pSeuraava;
        pHidas = pHidas->pSeuraava;
    }

    TIETO *pToinenOsa = pHidas->pSeuraava;
    pHidas->pSeuraava = NULL;

    if (pToinenOsa != NULL) {
        pToinenOsa->pEdellinen = NULL;
    }

    return pToinenOsa;
}

// Yhdistää kaksi järjestettyä listaa (nouseva järjestys)
TIETO *yhdista(TIETO *pEka, TIETO *pToka) {
    if (pEka == NULL) return pToka;
    if (pToka == NULL) return pEka;

    if (pEka->lukumaara < pToka->lukumaara) {
        pEka->pSeuraava = yhdista(pEka->pSeuraava, pToka);
        pEka->pSeuraava->pEdellinen = pEka;
        pEka->pEdellinen = NULL;
        return pEka;
    } else if (pEka->lukumaara > pToka->lukumaara) {
        pToka->pSeuraava = yhdista(pEka, pToka->pSeuraava);
        pToka->pSeuraava->pEdellinen = pToka;
        pToka->pEdellinen = NULL;
        return pToka;
    } else {
        if (strcmp(pEka->sukunimi, pToka->sukunimi) < 0) {
            pEka->pSeuraava = yhdista(pEka->pSeuraava, pToka);
            pEka->pSeuraava->pEdellinen = pEka;
            pEka->pEdellinen = NULL;
            return pEka;
        } else {
            pToka->pSeuraava = yhdista(pEka, pToka->pSeuraava);
            pToka->pSeuraava->pEdellinen = pToka;
            pToka->pEdellinen = NULL;
            return pToka;
        }
    }
}

// Pääfunktio merge sortille (nouseva)
TIETO *mergeSortNouseva(TIETO *pA) {
    if (pA == NULL || pA->pSeuraava == NULL) {
        return pA;
    }

    TIETO *pToinenOsa = nousevaPuolita(pA);
    pA = mergeSortNouseva(pA);
    pToinenOsa = mergeSortNouseva(pToinenOsa);

    return yhdista(pA, pToinenOsa);
}