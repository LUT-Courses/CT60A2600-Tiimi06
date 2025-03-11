#ifndef MERGESORTLASKEVAJARJESTYS_H
#define MERGESORTLASKEVAJARJESTYS_H
#include "TIETO.h"

TIETO *puolittaa(TIETO *pAlku);
TIETO *mergeSortLaskeva(TIETO *pA);
TIETO *merge(TIETO *ekaOsa, TIETO *tokaOsa);

#endif