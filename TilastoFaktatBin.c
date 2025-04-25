#include "TilastoFaktatBin.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

// Luodaan apufuktiot eri tilastofaktoja varten.
 void laskeKeskiarvo(BNODE *pNode, int *iLkm, int *iSumma) {
    if (pNode == NULL) return;


    (*iLkm)++;

    (*iSumma) += pNode->count;

    laskeKeskiarvo(pNode->pVasen, iLkm, iSumma);
    laskeKeskiarvo(pNode->pOikea, iLkm, iSumma);
}

 void laskeYliKeskiarvon(BNODE *pNode, double fKeskiarvo, int *iYli){

    if (pNode == NULL) return;

    if (pNode->count > fKeskiarvo) {
        (*iYli)++;
        }


    laskeYliKeskiarvon(pNode->pVasen, fKeskiarvo, iYli);
    laskeYliKeskiarvon(pNode->pOikea, fKeskiarvo, iYli);
}

 void laskeAlleKeskiarvon(BNODE *pNode, double fKeskiarvo, int *iAli) {
     if (pNode == NULL) return;


    if (pNode->count < fKeskiarvo){
            (*iAli)++;
    } 

    laskeAlleKeskiarvon(pNode->pVasen, fKeskiarvo, iAli);

    laskeAlleKeskiarvon(pNode->pOikea, fKeskiarvo, iAli);

}

 void laskeParittomat(BNODE *pNode, int *iLkm) {
    if (pNode == NULL) return;

    
    if (pNode->count % 2 != 0){
    (*iLkm)++;
    } 

    laskeParittomat(pNode->pVasen, iLkm);

    laskeParittomat(pNode->pOikea, iLkm);
}




 void laskeParilliset(BNODE *pNode, int *iLkm) {
    if (pNode == NULL) return;

    if (pNode->count % 2 == 0) {
        (*iLkm)++;
    }
    laskeParilliset(pNode->pVasen, iLkm);


    laskeParilliset(pNode->pOikea, iLkm);
}


 void etsiYleisin(BNODE *pNode, int *max, char *cKirjain, char *yleisinNimi) {
    if (pNode == NULL) return;

    if (pNode->count > *max) {
        *max = pNode->count;
        *cKirjain = pNode->name[0];
        strcpy(yleisinNimi, pNode->name);
    }
    etsiYleisin(pNode->pVasen, max, cKirjain, yleisinNimi);
    etsiYleisin(pNode->pOikea, max, cKirjain, yleisinNimi);
}

 void laskeSamatAlkukirjaimet(BNODE *pNode, char cKirjain, int *iLkm) {
        if (pNode == NULL) return;

    if (pNode->name[0] == cKirjain){
        (*iLkm)++;

    } 
    laskeSamatAlkukirjaimet(pNode->pVasen, cKirjain, iLkm);


    laskeSamatAlkukirjaimet(pNode->pOikea, cKirjain, iLkm);
}


// Ohjelma laskee nimien esiintymismäärän mukaan keskiarvon

void keskiarvoLkmBin(BNODE *pJuuri) {

    int iLkm = 0;
    int iSumma = 0;


    laskeKeskiarvo(pJuuri, &iLkm, &iSumma);

    double fKeskiarvo = (double)iSumma / iLkm;
    printf("Nimien keskimääräinen esiintymismäärä on: %.2f\n", fKeskiarvo);
}

// Laskee nimien lukumäärän, jotka esiintyvät keskiarvon yläpuolella binääripuussa
void yliKeskiarvonLkmBin(BNODE *pJuuri) {

    int iSumma = 0;

    int iLkm = 0;
    int iYli = 0;
    laskeKeskiarvo(pJuuri, &iLkm, &iSumma);


    double fKeskiarvo = (double)iSumma / iLkm;
    laskeYliKeskiarvon(pJuuri, fKeskiarvo, &iYli);


    printf("Yli keskiarvon (%.2f) olevien nimien lukumäärä on: %d\n", fKeskiarvo, iYli);
}

// Laskee nimien lukumäärän, jotka esiintyvät keskiarvon alapuolella binääripuussa
void alleKeskiarvonLkmBin(BNODE *pJuuri) {

    int iSumma = 0;
    int iLkm = 0;
    int iAli = 0;


    laskeKeskiarvo(pJuuri, &iLkm, &iSumma);
    double fKeskiarvo = (double)iSumma / iLkm;
    laskeAlleKeskiarvon(pJuuri, fKeskiarvo, &iAli);



    printf("Alle keskiarvon (%.2f) olevien nimien lukumäärä on: %d\n", fKeskiarvo, iAli);
}

// Laskee nimien lukumäärän, jotka esiintyvät parittomasti binääripuussa
void parittomatLkmBin(BNODE *pJuuri) {

    int iLkm = 0;
    laskeParittomat(pJuuri, &iLkm);

    printf("Nimet joiden esiintyvyys on pariton, lukumäärä on: %d\n", iLkm);
}



// Laskee nimien lukumäärän, jotka esiintyvät parillisesti binääripuussa
void parillisetLkmBin(BNODE *pJuuri) {

    int iLkm = 0;
    laskeParilliset(pJuuri, &iLkm);


    printf("Nimet joiden esiintyvyys on parillinen, lukumäärä on: %d\n", iLkm);

}

// Laskee nimien lukumäärän, joilla on sama alkukirjain kuin yleisimmällä nimellä binääripuussa
void samatAlkukirjaimetBin(BNODE *pJuuri) {

    char cKirjain;
    int max = INT_MIN;
    char yleisinNimi[NIMIPITUUS];


    etsiYleisin(pJuuri, &max, &cKirjain, yleisinNimi);
    int iLkm = 0;
    laskeSamatAlkukirjaimet(pJuuri, cKirjain, &iLkm);


    printf("Nimien lukumäärä, jotka alkavat samalla kirjaimella kuin yleisin nimi '%s' on: %d\n", yleisinNimi, iLkm);

}

