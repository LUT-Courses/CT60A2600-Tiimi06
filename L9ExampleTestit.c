#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

void test_example() {
    CU_ASSERT(1 + 1 == 2);
}

char* test_example2() {
    char* nimi[30] = "";

    printf("Anna nimi: ");
    fgets(nimi, 30, stdin);
    nimi[strlen(nimi)-1] = '\0';
    CU_ASSERT_STRING_EQUAL(nimi, "kalle");
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test Suite", NULL, NULL);
    CU_add_test(suite, "Test Example", test_example);
    CU_add_test(suite, "Testexample2", test_example2);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}