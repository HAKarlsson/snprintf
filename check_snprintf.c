#include "CUnit/Basic.h"

int init_suite1(void) {
    return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
    return 0;
}

void testSTRING(void) 
{
    char buf[20];
    const char *str = "world";
    int len = snprintf(buf, 20, "hello, %s", str); 
    CU_ASSERT_STRING_EQUAL(buf, "hello, world");
    CU_ASSERT(len == 13);
}

void testINTEGER_0(void) 
{
    char buf[20];
    int len = snprintf(buf, 20, "hello, %d", 0); 
    CU_ASSERT_STRING_EQUAL(buf, "hello, 0");
    CU_ASSERT(len == 9);
}

void testINTEGER_N1(void) 
{
    char buf[20];
    int len = snprintf(buf, 20, "hello, %d", -1); 
    CU_ASSERT_STRING_EQUAL(buf, "hello, -1");
    CU_ASSERT(len == 10);
}

void testHEX_0(void) 
{
    char buf[20];
    int len = snprintf(buf, 20, "hello, 0x%x", 0); 
    CU_ASSERT_STRING_EQUAL(buf, "hello, 0x0");
    CU_ASSERT(len == 11);
}

void testHEX_N1(void) 
{
    char buf[20];
    int len = snprintf(buf, 20, "hello, 0x%x", -1); 
    CU_ASSERT_STRING_EQUAL(buf, "hello, 0xFFFFFFFF");
    CU_ASSERT(len == 18);
}

int main(void)
{
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (
           (NULL == CU_add_test(pSuite, "test with string", testSTRING)) ||
           (NULL == CU_add_test(pSuite, "test with int 0", testINTEGER_0)) ||
           (NULL == CU_add_test(pSuite, "test with int -1", testINTEGER_N1)) ||
           (NULL == CU_add_test(pSuite, "test with hex 0x0", testHEX_0)) ||
           (NULL == CU_add_test(pSuite, "test with hex 0xFFFFFFFF", testHEX_N1))
           ) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

