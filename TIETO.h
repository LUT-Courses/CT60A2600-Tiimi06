#ifndef TIETO_H
#define TIETO_H

#define SUKUNIMIKOKO 30

typedef struct tieto {
    char sukunimi[SUKUNIMIKOKO];
    int lukumaara;
    struct tieto *pSeuraava;
    struct tieto *pEdellinen;
} TIETO;

#endif // TIETO_H