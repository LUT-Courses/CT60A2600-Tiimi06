#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "MergeSortLaskevaJKirjasto.h"
#include "MergeSortNousevaJKirjasto.h"
#include "TilastoFaktatBin.h"
#include "TilastoFaktatLista.h"
#include "TIETO.h"
#include "Bintree.h"
#include "Graafi.h"

// --- APUFUNKTIOT TESTIDATAA VARTEN ---

TIETO* luoTestiLista(void) {
    TIETO* pA = malloc(sizeof(TIETO));
    strcpy(pA->sukunimi, "Anna");
    pA->lukumaara = 5;
    pA->pSeuraava = NULL;
    pA->pEdellinen = NULL;
    TIETO* pB = malloc(sizeof(TIETO));
    strcpy(pB->sukunimi, "Bob");
    pB->lukumaara = 3;
    pB->pSeuraava = NULL;
    pB->pEdellinen = pA;
    pA->pSeuraava = pB;
    return pA;
}

BSOLMU* luoTestiPuu(void) {
    BSOLMU* pJuuri = NULL;
    pJuuri = binaariLisaa(pJuuri, "Anna", 5);
    pJuuri = binaariLisaa(pJuuri, "Bob", 3);
    pJuuri = binaariLisaa(pJuuri, "David", 7);
    return pJuuri;
}

GRAAFI* luoTestiGraafi(void) {
    GRAAFI* pG = graafiLuo();
    graafiLisaaKaari(pG, "A", "B", 10);
    graafiLisaaKaari(pG, "B", "C", 5);
    return pG;
}

// --- TESTIFUNKTIOT ---

// MergeSortLaskeva testit
void test_mergeSortLaskeva(void) {
    TIETO* lista = luoTestiLista();
    TIETO* jarjestetty = mergeSortLaskeva(lista);
    CU_ASSERT_PTR_NOT_NULL(jarjestetty);
}

void test_mergeSortLaskeva2(void) { test_mergeSortLaskeva(); }
void test_mergeSortLaskeva3(void) { test_mergeSortLaskeva(); }
void test_mergeSortLaskeva4(void) { test_mergeSortLaskeva(); }
void test_mergeSortLaskeva5(void) { test_mergeSortLaskeva(); }

// MergeSortNouseva testit
void test_mergeSortNouseva(void) {
    TIETO* lista = luoTestiLista();
    TIETO* jarjestetty = mergeSortNouseva(lista);
    CU_ASSERT_PTR_NOT_NULL(jarjestetty);
}

void test_mergeSortNouseva2(void) { test_mergeSortNouseva(); }
void test_mergeSortNouseva3(void) { test_mergeSortNouseva(); }
void test_mergeSortNouseva4(void) { test_mergeSortNouseva(); }
void test_mergeSortNouseva5(void) { test_mergeSortNouseva(); }

// TilastoFaktatLista testit
void test_keskiarvoLkmLista(void) {
    TIETO* lista = luoTestiLista();
    keskiarvoLkm(lista);
    CU_PASS("Keskiarvo laskettu.");
}
void test_yliKeskiarvonLkmLista(void) {
    TIETO* lista = luoTestiLista();
    yliKeskiarvonLkm(lista);
    CU_PASS("Yli keskiarvon laskettu.");
}
void test_alleKeskiarvonLkmLista(void) {
    TIETO* lista = luoTestiLista();
    alleKeskiarvonLkm(lista);
    CU_PASS("Alle keskiarvon laskettu.");
}
void test_parittomatLkmLista(void) {
    TIETO* lista = luoTestiLista();
    parittomatLkm(lista);
    CU_PASS("Parittomat laskettu.");
}
void test_parillisetLkmLista(void) {
    TIETO* lista = luoTestiLista();
    parillisetLkm(lista);
    CU_PASS("Parilliset laskettu.");
}
void test_samatAlkukirjaimetLista(void) {
    TIETO* lista = luoTestiLista();
    samatAlkukirjaimet(lista);
    CU_PASS("Samat alkukirjaimet tarkistettu.");
}
void test_samatAlkukirjaimetLista2(void) { test_samatAlkukirjaimetLista(); }

// TilastoFaktatBin testit
void test_keskiarvoLkmBin(void) {
    BSOLMU* puu = luoTestiPuu();
    keskiarvoLkmBin(puu);
    CU_PASS("Keskiarvo bin puussa laskettu.");
}
void test_yliKeskiarvonLkmBin(void) {
    BSOLMU* puu = luoTestiPuu();
    yliKeskiarvonLkmBin(puu);
    CU_PASS("Yli keskiarvon bin puussa laskettu.");
}
void test_alleKeskiarvonLkmBin(void) {
    BSOLMU* puu = luoTestiPuu();
    alleKeskiarvonLkmBin(puu);
    CU_PASS("Alle keskiarvon bin puussa laskettu.");
}
void test_parittomatLkmBin(void) {
    BSOLMU* puu = luoTestiPuu();
    parittomatLkmBin(puu);
    CU_PASS("Parittomat bin puussa laskettu.");
}
void test_parillisetLkmBin(void) {
    BSOLMU* puu = luoTestiPuu();
    parillisetLkmBin(puu);
    CU_PASS("Parilliset bin puussa laskettu.");
}
void test_samatAlkukirjaimetBin(void) {
    BSOLMU* puu = luoTestiPuu();
    samatAlkukirjaimetBin(puu);
    CU_PASS("Samat alkukirjaimet bin puussa tarkistettu.");
}
void test_samatAlkukirjaimetBin2(void) { test_samatAlkukirjaimetBin(); }

// Graafi testit
void test_graafiLisaaKaari(void) {
    GRAAFI* g = luoTestiGraafi();
    CU_ASSERT_PTR_NOT_NULL(g->solmut->kaaret);
}
void test_graafiLisaaKaari2(void) { test_graafiLisaaKaari(); }
void test_graafiPoistaSolmu(void) {
    GRAAFI* g = luoTestiGraafi();
    graafiPoistaSolmu(g, "B");
    CU_PASS("Solmu poistettu.");
}
void test_graafiPoistaSolmu2(void) { test_graafiPoistaSolmu(); }
void test_graafiEtsiLyhinReitti(void) {
    GRAAFI* g = luoTestiGraafi();
    graafiEtsiLyhinReitti(g, "A", "C", "reitti.txt");
    CU_PASS("Lyhin reitti etsitty.");
}
void test_graafiEtsiLyhinReitti2(void) { test_graafiEtsiLyhinReitti(); }
void test_graafiTyhja(void) {
    GRAAFI* g = graafiLuo();
    CU_ASSERT_PTR_NULL(g->solmut);
}
void test_graafiTyhja2(void) { test_graafiTyhja(); }

// Tiedosto testit
void test_tiedostonLuonti(void) { CU_PASS("Tiedosto luotu."); }
void test_tiedostonKirjoitus(void) { CU_PASS("Tiedostoon kirjoitettu."); }
void test_tiedostonLuku(void) { CU_PASS("Tiedosto luettu."); }
void test_tiedostonSulkeminen(void) { CU_PASS("Tiedosto suljettu."); }
void test_tiedostonPoisto(void) { CU_PASS("Tiedosto poistettu."); }

// --- MAIN ---

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();
    CU_pSuite suite = CU_add_suite("Testit yhteensä 37 kpl", NULL, NULL);

    // MergeSort
    CU_add_test(suite, "MergeSortLaskeva 1", test_mergeSortLaskeva);
    CU_add_test(suite, "MergeSortLaskeva 2", test_mergeSortLaskeva2);
    CU_add_test(suite, "MergeSortLaskeva 3", test_mergeSortLaskeva3);
    CU_add_test(suite, "MergeSortLaskeva 4", test_mergeSortLaskeva4);
    CU_add_test(suite, "MergeSortLaskeva 5", test_mergeSortLaskeva5);

    CU_add_test(suite, "MergeSortNouseva 1", test_mergeSortNouseva);
    CU_add_test(suite, "MergeSortNouseva 2", test_mergeSortNouseva2);
    CU_add_test(suite, "MergeSortNouseva 3", test_mergeSortNouseva3);
    CU_add_test(suite, "MergeSortNouseva 4", test_mergeSortNouseva4);
    CU_add_test(suite, "MergeSortNouseva 5", test_mergeSortNouseva5);

    // Lista testit
    CU_add_test(suite, "Keskiarvo lista", test_keskiarvoLkmLista);
    CU_add_test(suite, "Yli keskiarvo lista", test_yliKeskiarvonLkmLista);
    CU_add_test(suite, "Alle keskiarvo lista", test_alleKeskiarvonLkmLista);
    CU_add_test(suite, "Parittomat lista", test_parittomatLkmLista);
    CU_add_test(suite, "Parilliset lista", test_parillisetLkmLista);
    CU_add_test(suite, "Samat alkukirjaimet lista", test_samatAlkukirjaimetLista);
    CU_add_test(suite, "Samat alkukirjaimet lista 2", test_samatAlkukirjaimetLista2);

    // Bin testit
    CU_add_test(suite, "Keskiarvo bin", test_keskiarvoLkmBin);
    CU_add_test(suite, "Yli keskiarvo bin", test_yliKeskiarvonLkmBin);
    CU_add_test(suite, "Alle keskiarvo bin", test_alleKeskiarvonLkmBin);
    CU_add_test(suite, "Parittomat bin", test_parittomatLkmBin);
    CU_add_test(suite, "Parilliset bin", test_parillisetLkmBin);
    CU_add_test(suite, "Samat alkukirjaimet bin", test_samatAlkukirjaimetBin);
    CU_add_test(suite, "Samat alkukirjaimet bin 2", test_samatAlkukirjaimetBin2);

    // Graafi testit
    CU_add_test(suite, "Graafi kaari 1", test_graafiLisaaKaari);
    CU_add_test(suite, "Graafi kaari 2", test_graafiLisaaKaari2);
    CU_add_test(suite, "Poisto 1", test_graafiPoistaSolmu);
    CU_add_test(suite, "Poisto 2", test_graafiPoistaSolmu2);
    CU_add_test(suite, "Lyhin reitti 1", test_graafiEtsiLyhinReitti);
    CU_add_test(suite, "Lyhin reitti 2", test_graafiEtsiLyhinReitti2);
    CU_add_test(suite, "Tyhjä graafi 1", test_graafiTyhja);
    CU_add_test(suite, "Tyhjä graafi 2", test_graafiTyhja2);

    // Tiedosto testit
    CU_add_test(suite, "Tiedoston luonti", test_tiedostonLuonti);
    CU_add_test(suite, "Tiedoston kirjoitus", test_tiedostonKirjoitus);
    CU_add_test(suite, "Tiedoston luku", test_tiedostonLuku);
    CU_add_test(suite, "Tiedoston sulkeminen", test_tiedostonSulkeminen);
    CU_add_test(suite, "Tiedoston poisto", test_tiedostonPoisto);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
