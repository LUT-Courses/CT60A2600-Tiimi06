#include "TilastoFaktatBin.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

// Luodaan apufuktiot eri tilastofaktoja varten.
static void laskeKeskiarvo(BNODE *pNode, int *iLkm, int *iSumma) {
    if (pNode == NULL) return;
    (*iLkm)++;
    (*iSumma) += pNode->count;
    laskeKeskiarvo(pNode->pVasen, iLkm, iSumma);
    laskeKeskiarvo(pNode->pOikea, iLkm, iSumma);
}

static void laskeYliKeskiarvon(BNODE *pNode, double fKeskiarvo, int *iYli) {
    if (pNode == NULL) return;
    if (pNode->count > fKeskiarvo) (*iYli)++;
    laskeYliKeskiarvon(pNode->pVasen, fKeskiarvo, iYli);
    laskeYliKeskiarvon(pNode->pOikea, fKeskiarvo, iYli);
}

static void laskeAlleKeskiarvon(BNODE *pNode, double fKeskiarvo, int *iAli) {
    if (pNode == NULL) return;
    if (pNode->count < fKeskiarvo) (*iAli)++;
    laskeAlleKeskiarvon(pNode->pVasen, fKeskiarvo, iAli);
    laskeAlleKeskiarvon(pNode->pOikea, fKeskiarvo, iAli);
}

static void laskeParittomat(BNODE *pNode, int *iLkm) {
    if (pNode == NULL) return;
    if (pNode->count % 2 != 0) (*iLkm)++;
    laskeParittomat(pNode->pVasen, iLkm);
    laskeParittomat(pNode->pOikea, iLkm);
}