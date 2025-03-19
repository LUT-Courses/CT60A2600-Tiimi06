#ifndef BINTREE_H
#define BINTREE_H

typedef struct Node {
    char name[50];
    int count;
    struct Node *pVasen;   // Osoitin vasempaan lapseen
    struct Node *pOikea;   // Osoitin oikeaan lapseen
} NODE;

/* Puun perustoiminnot */
NODE* binaariLuoNode(const char *pNimi, int iLukumaara);
NODE* binaariInsert(NODE *pJuuri, const char *pNimi, int iLukumaara);
void binaariVapauta(NODE *pJuuri);
NODE* binaariLueTiedosto(NODE *pJuuri, const char *pTiedostonNimi);

/* Tiedostoon kirjoitus ja haut */
void binaariKirjoitaJarjestyksessa(NODE *pJuuri, const char *pTiedostonNimi);
int syvyysHaku(NODE *pJuuri, int iHaettava, const char *pTiedostonNimi);
int leveysHaku(NODE *pJuuri, const char *pHaettavaNimi, const char *pTiedostonNimi);

#endif // BINTREE_H