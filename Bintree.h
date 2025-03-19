#ifndef BINTREE_H
#define BINTREE_H

typedef struct BinNode {
    char name[50];
    int count;
    struct BinNode *pVasen;
    struct BinNode *pOikea;
} BNODE;

/* Prototyypit */
BNODE* binaariLuoNode(const char *pNimi, int iLukumaara);
BNODE* binaariInsert(BNODE *pJuuri, const char *pNimi, int iLukumaara);
void binaariVapauta(BNODE *pJuuri);
BNODE* binaariLueTiedosto(BNODE *pJuuri, const char *pTiedostonNimi);


#endif // BINTREE_H