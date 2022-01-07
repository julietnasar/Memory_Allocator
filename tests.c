# include <stdio.h>
# ifndef FOO_TESTS_H


/*    TEST FUNCTIONS     */

void printpass(char testName[]){
    printf("\n------------------------------ TEST %s PASSED ------------------------------\n", testName);
}

void printfail(char testName[]){
    printf("\n------------------------------ TEST %s FAILED ------------------------------\n", testName);
}

// test: what happens when the memory is overloaded
// conditional: should return null
void test_overload(global_memory, global_mem_size){

    char name[] = "OVERLOAD";

    mem_init(global_memory, global_mem_size);
    Block *res = my_malloc(global_mem_size+1);
    
    if(res == NULL){
        printpass(name);
    }
    else{
        printfail(name);
    }
}

// test: alloc allocates memory in the linked list
// conditional: all values returned by the alloc should be in the ll
void test_alloc(global_memory, global_mem_size){

    char name[] = "OVERLOAD";

}


void runTests(global_memory, global_mem_size){

    test_overload(global_memory, global_mem_size);



}