#ifndef MERGESORTLASKEVAJARJESTYS_H
#define MERGESORTLASKEVAJARJESTYS_H
#include "TIETO.h"


TIETO *puolittaa(TIETO *pAlku);
TIETO *merge(TIETO *ekaOsa, TIETO *tokaOsa);
TIETO *mergeSortLaskeva(TIETO *pA);

#endif