#include "TilastoFaktatBin.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

// Luodaan apufuktiot eri tilastofaktoja varten.
static void laskeKeskiarvo(BNODE *pNode, int *iLkm, int *iSumma) {


    (*iLkm)++;

    (*iSumma) += pNode->count;

    laskeKeskiarvo(pNode->pVasen, iLkm, iSumma);
    laskeKeskiarvo(pNode->pOikea, iLkm, iSumma);
}

static void laskeYliKeskiarvon(BNODE *pNode, double fKeskiarvo, int *iYli){


    if (pNode->count > fKeskiarvo) {
        (*iYli)++;
        }


    laskeYliKeskiarvon(pNode->pVasen, fKeskiarvo, iYli);
    laskeYliKeskiarvon(pNode->pOikea, fKeskiarvo, iYli);
}

static void laskeAlleKeskiarvon(BNODE *pNode, double fKeskiarvo, int *iAli) {
 

    if (pNode->count < fKeskiarvo){
            (*iAli)++;
    } 

    laskeAlleKeskiarvon(pNode->pVasen, fKeskiarvo, iAli);

    laskeAlleKeskiarvon(pNode->pOikea, fKeskiarvo, iAli);

}

static void laskeParittomat(BNODE *pNode, int *iLkm) {

    
    if (pNode->count % 2 != 0){
    (*iLkm)++;
    } 

    laskeParittomat(pNode->pVasen, iLkm);

    laskeParittomat(pNode->pOikea, iLkm);
}




static void laskeParilliset(BNODE *pNode, int *iLkm) {

    if (pNode->count % 2 == 0) {
        (*iLkm)++;
    }
    laskeParilliset(pNode->pVasen, iLkm);


    laskeParilliset(pNode->pOikea, iLkm);
}


static void etsiYleisin(BNODE *pNode, int *max, char *cKirjain, char *yleisinNimi) {

    if (pNode->count > *max) {
        *max = pNode->count;
        *cKirjain = pNode->name[0];
        strcpy(yleisinNimi, pNode->name);
    }
    etsiYleisin(pNode->pVasen, max, cKirjain, yleisinNimi);
    etsiYleisin(pNode->pOikea, max, cKirjain, yleisinNimi);
}

static void laskeSamatAlkukirjaimet(BNODE *pNode, char cKirjain, int *iLkm) {
    if (pNode->name[0] == cKirjain){
        (*iLkm)++;

    } 
    laskeSamatAlkukirjaimet(pNode->pVasen, cKirjain, iLkm);

    
    laskeSamatAlkukirjaimet(pNode->pOikea, cKirjain, iLkm);
}