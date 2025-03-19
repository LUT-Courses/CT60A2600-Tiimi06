#ifndef TIETO_H
#define TIETO_H

#define SUKUNIMIKOKO 30

typedef struct tieto {
    char sukunimi[SUKUNIMIKOKO];
    int lukumaara;
    struct tieto *pSeuraava;
    struct tieto *pEdellinen;
} TIETO;

typedef struct Node{ 
    char name[50];
    int maara;
    struct Node *vasen;
    struct Node *oikea;
} NODE;


typedef struct QueueNode{
    NODE *data;
    struct Queuenode *pSeuraava;
} QUEUENODE;

#endif