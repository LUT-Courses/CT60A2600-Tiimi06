#include "TilastoFaktatKirjasto.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>



void keskiarvoLkm (TIETO *pA){
    TIETO *ptr = pA;
    int iLkm = 0;
    int iSumma = 0;
    while(ptr != NULL){
        iLkm ++;
        iSumma += ptr -> lukumaara;
        ptr = ptr -> pSeuraava;
    }

    double fKeskiarvo = (double) iSumma / iLkm;

    printf("Nimien keskimääräinen esiintymismäärä on: %.2f\n", fKeskiarvo);

    

}


void yliKeskiarvonLkm (TIETO *pA){

    int iSumma = 0;
    int iLkm = 0;
    int iYli = 0;
    TIETO *ptr = pA;

    while(ptr != NULL){
        iLkm ++;
        iSumma += ptr -> lukumaara;
        ptr = ptr -> pSeuraava;
    }

    double fKeskiarvo = (double) iSumma / iLkm;

    while(pA){
        if(pA -> lukumaara > fKeskiarvo){
            iYli ++;
        }
        pA = pA -> pSeuraava;
    }

    printf("Yli keskiarvon (%.2f) olevien nimien lukumäärä on: %d\n", fKeskiarvo ,iYli);

}

void alleKeskiarvonLkm (TIETO *pA){

    int iSumma = 0;
    int iLkm = 0;
    int iAli = 0;
    TIETO *ptr = pA;

    while(ptr != NULL){
        iLkm ++;
        iSumma += ptr -> lukumaara;
        ptr = ptr -> pSeuraava;
    }

    double fKeskiarvo = (double) iSumma / iLkm;

    while(pA){
        if(pA -> lukumaara < fKeskiarvo){
            iAli ++;
        }
        pA = pA -> pSeuraava;
    }

    printf("Alle keskiarvon (%.2f) olevien nimien lukumäärä on: %d\n", fKeskiarvo ,iAli);

}

void parittomatLkm(TIETO *pA){
    int iLkm = 0;
    while(pA){
        if(pA -> lukumaara % 2 != 0){
            iLkm ++;
        }
        pA = pA -> pSeuraava;
    }

    printf("Nimet joiden esiintyvyys on pariton, lukumäärä on: %d\n", iLkm);
}

void parillisetLkm(TIETO *pA){
    int iLkm = 0;
    while(pA){
        if(pA -> lukumaara % 2 == 0){
            iLkm ++;
        }
        pA = pA -> pSeuraava;
    }

    printf("Nimet joiden esiintyvyys on parillinen, lukumäärä on: %d\n", iLkm);
}

void samatAlkukirjaimet(TIETO *pA){
    char cKirjain;
    int max = INT_MIN;
    char yleisinNimi[SUKUNIMIKOKO];
    TIETO *ptr = pA;

    while(ptr != NULL){
        if(ptr -> lukumaara> max){
            max = ptr -> lukumaara;
            cKirjain = ptr -> sukunimi[0];
            strcpy(yleisinNimi,  ptr -> sukunimi);

        }
        ptr = ptr -> pSeuraava;
    }
    
    int iLkm = 0;
    while(pA){
        if(pA -> sukunimi[0] == cKirjain){
            iLkm ++;
        }
        pA = pA -> pSeuraava;
    }

    printf("Nimien lukumäärä, jotka alkavat samalla kirjaimella kuin yleisin nimi '%s' on: %d", yleisinNimi, iLkm);
}