
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "inc/PriorityQueue.h"





PQueue * pq = NULL;
int init_suite1(void) // 0 Success. ? - Falha
{
     pq = NewPQueue();
     return 0;
}

/* The suite cleanup function.
 *
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    CleanPQueue(pq);
    return 0;
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void testFPRINTF(void)
{
    int i1 = 10;

//    if (NULL != temp_file) {
  //      CU_ASSERT(0 == fprintf(temp_file, ""));
    //    CU_ASSERT(2 == fprintf(temp_file, "Q\n"));
  //      CU_ASSERT(7 == fprintf(temp_file, "i1 = %d", i1));
  //  }
}

/* Simple test of fread().
 * Reads the data previously written by testFPRINTF()
 * and checks whether the expected characters are present.
 * Must be run after testFPRINTF().
 */
void testFREAD(void)
{
    unsigned char buffer[20];

  //  if (NULL != temp_file) {
   //     rewind(temp_file);
    //    CU_ASSERT(9 == fread(buffer, sizeof(unsigned char), 20, temp_file));
  //      CU_ASSERT(0 == strncmp(buffer, "Q\ni1 = 10", 9));
    //}
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */


void testeinsercoes_simples(void)
{
    CU_ASSERT_EQUAL(Enqueue(pq,1,1), 0);
    CU_ASSERT_EQUAL(Enqueue(pq,2,4), 1);
    CU_ASSERT_EQUAL(Enqueue(pq,3,3), 2);
}
void testeremocoes_simples(void)
{
    CU_ASSERT_EQUAL(Dequeue(pq),2);
    CU_ASSERT_EQUAL(Dequeue(pq),3);
    CU_ASSERT_EQUAL(Dequeue(pq),1);
    CleanPQueue(pq);
    CU_ASSERT_EQUAL(GetPQueueSize(pq),0);
}

void teste2insercoes_simples(void)
{
    CU_ASSERT_EQUAL(Enqueue(pq,1,1), 0);
    CU_ASSERT_EQUAL(Enqueue(pq,2,4), 1);
    CU_ASSERT_EQUAL(Enqueue(pq,3,3), 2);
}

void remocoesvazias(void)
{
    Dequeue(pq);
    Dequeue(pq);
    CU_ASSERT_EQUAL(GetPQueueSize(pq),0);
}
void insercaocomeco(void)
{
    Enqueue(pq, 10, 10);
    CU_ASSERT_EQUAL(Dequeue(pq),10);
    Enqueue(pq, 10, 10);
    Enqueue(pq,15,10);
    CU_ASSERT_EQUAL(Dequeue(pq),10);
    CleanPQueue(pq);
}

void insercaomeio(void){
    Enqueue(pq, 10,15);
    Enqueue(pq, 20, 30);
    CU_ASSERT_EQUAL(Enqueue(pq,30, 20),2);
    CU_ASSERT_EQUAL(Dequeue(pq),20);
    CleanPQueue(pq);
}

void insercaofim(void)
{
    Enqueue(pq, 10, 100);
    Enqueue(pq, 20, 90);
    CU_ASSERT_EQUAL(Enqueue(pq,30,80),2);
    Enqueue(pq,40,80);
    Dequeue(pq);
    Dequeue(pq);
    CU_ASSERT_EQUAL(Dequeue(pq),30);
    CleanPQueue(pq);
}


void testeAbsurdo(void)
{
    Enqueue(pq,10,-10);
    Enqueue(pq,50,50);
    Enqueue(pq,20,300);
    CU_ASSERT_EQUAL(Dequeue(pq),20);
    CU_ASSERT_EQUAL(Dequeue(pq),50);
    CU_ASSERT_EQUAL(Dequeue(pq),10);
}



int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1 Simples", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if (
        (NULL == CU_add_test(pSuite, "Teste de Insercoes Simples()", testeinsercoes_simples) )
        ||
        (NULL == CU_add_test(pSuite, "Teste de Remocoes Simples()", testeremocoes_simples) )
        ||
        (NULL == CU_add_test(pSuite, "Teste de Insercoes pos limpo()", teste2insercoes_simples) )
        )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_pSuite pSuite2 = NULL;
    pSuite2 = CU_add_suite("Suite_2 Casos Estranhos", init_suite1, clean_suite1);
    if (NULL == pSuite2) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite2, "Texte de Insercoes Comeco()", insercaocomeco) )
            ||
            (NULL == CU_add_test(pSuite2, "Texte de Insercoes Meio()", insercaomeio)
            )
            ||
            (NULL == CU_add_test(pSuite2, "Texte de Insercoes Fins()",insercaofim))
            ||
            ((NULL == CU_add_test(pSuite2, "Texte absurdo()",testeAbsurdo))
            )
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
