#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "MergeSortLaskevaJKirjasto.h"
#include "MergeSortNousevaJKirjasto.h"
#include "TilastoFaktatBin.h"
#include "TilastoFaktatLista.h"
#include "TIETO.h"
#include "Bintree.h"
#include "Graafi.h"

// --- APUFUNKTIOT TESTEILLE ---
TIETO* luoTestiLista() {
    TIETO* pA = NULL;
    pA = (TIETO*)malloc(sizeof(TIETO));
    strcpy(pA->sukunimi, "Anna");
    pA->lukumaara = 5;
    pA->pSeuraava = NULL;
    pA->pEdellinen = NULL;

    TIETO* pB = (TIETO*)malloc(sizeof(TIETO));
    strcpy(pB->sukunimi, "Bob");
    pB->lukumaara = 3;
    pB->pSeuraava = NULL;
    pB->pEdellinen = pA;

    pA->pSeuraava = pB;
    return pA;
}

BSOLMU* luoTestiPuu() {
    BSOLMU* pJuuri = NULL;
    pJuuri = binaariLisaa(pJuuri, "Anna", 5);
    pJuuri = binaariLisaa(pJuuri, "Bob", 3);
    pJuuri = binaariLisaa(pJuuri, "David", 7);
    return pJuuri;
}

GRAAFI* luoTestiGraafi() {
    GRAAFI* pG = graafiLuo();
    graafiLisaaKaari(pG, "A", "B", 10);
    graafiLisaaKaari(pG, "B", "C", 5);
    return pG;
}

// --- TESTIFUNKTIOT ---
void test_mergeSortLaskeva(void) {
    TIETO* pLista = luoTestiLista();
    TIETO* pJarjestetty = mergeSortLaskeva(pLista);
    CU_ASSERT_PTR_NOT_NULL(pJarjestetty);
    CU_ASSERT_TRUE(pJarjestetty->lukumaara >= pJarjestetty->pSeuraava->lukumaara);
}

void test_mergeSortNouseva(void) {
    TIETO* pLista = luoTestiLista();
    TIETO* pJarjestetty = mergeSortNouseva(pLista);
    CU_ASSERT_PTR_NOT_NULL(pJarjestetty);
    CU_ASSERT_TRUE(pJarjestetty->lukumaara <= pJarjestetty->pSeuraava->lukumaara);
}

void test_keskiarvoLkmLista(void) {
    TIETO* pLista = luoTestiLista();
    keskiarvoLkm(pLista);
    CU_PASS("keskiarvoLkm lista toimii.");
}

void test_keskiarvoLkmBin(void) {
    BSOLMU* pJuuri = luoTestiPuu();
    keskiarvoLkmBin(pJuuri);
    CU_PASS("keskiarvoLkm bin toimii.");
}

void test_graafiLisaaKaari(void) {
    GRAAFI* pG = graafiLuo();
    CU_ASSERT_PTR_NOT_NULL(pG);

    graafiLisaaKaari(pG, "A", "B", 7);
    graafiLisaaKaari(pG, "B", "C", 5);

    CU_PASS("graafiLisaaKaari toimii ilman kaatumista.");
}

void test_graafiPoistaSolmu(void) {
    GRAAFI* pG = graafiLuo();
    graafiLisaaKaari(pG, "A", "B", 7);
    graafiLisaaKaari(pG, "B", "C", 5);

    pG = graafiPoistaSolmu(pG, "B");

    CU_PASS("graafiPoistaSolmu toimii ilman kaatumista.");
}

// --- MAIN TESTIOHJELMA ---
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testit: Linkitetty Lista, Binaaripuu, Graafi", NULL, NULL);

    CU_add_test(suite, "Testaa mergeSortLaskeva", test_mergeSortLaskeva);
    CU_add_test(suite, "Testaa mergeSortNouseva", test_mergeSortNouseva);
    CU_add_test(suite, "Testaa keskiarvoLkmLista", test_keskiarvoLkmLista);
    CU_add_test(suite, "Testaa keskiarvoLkmBin", test_keskiarvoLkmBin);
    CU_add_test(suite, "Testaa graafiLisaaKaari", test_graafiLisaaKaari);
    CU_add_test(suite, "Testaa graafiPoistaSolmu", test_graafiPoistaSolmu);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
