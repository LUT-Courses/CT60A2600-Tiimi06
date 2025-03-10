#include "TilastoFaktatKirjasto.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>



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