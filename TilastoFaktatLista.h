#ifndef TILASTOFAKTATKIRJASTO_H
#define TILASTOFAKTATKIRJASTO_H

#include <stdio.h>
#include <stdlib.h>
#include "TIETO.h"



void keskiarvoLkm (TIETO *pA);
void alleKeskiarvonLkm (TIETO *pA);
void yliKeskiarvonLkm (TIETO *pA);
void parittomatLkm(TIETO *pA);
void parillisetLkm(TIETO *pA);
void samatAlkukirjaimet(TIETO *pA);

#endif 