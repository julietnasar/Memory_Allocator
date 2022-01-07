# include "my_mem.h"
//# include "my_mem.c"
# include <stdio.h>



/*    TEST FUNCTIONS     */

void printpass(char testName[]){
    printf("\n------------------------------ TEST %s PASSED ------------------------------\n", testName);
}

void printfail(char testName[]){
    printf("\n------------------------------ TEST %s FAILED ------------------------------\n", testName);
}

// test: what happens when the memory is overloaded
// conditional: should return null
void test_overload(unsigned int global_memory, unsigned char *global_mem_size, char name[]){

    mem_init(global_memory, global_mem_size);
    Block *res = my_malloc(global_mem_size+1);
    
    if(res == NULL){
        printpass(name);
    }
    else{
        printfail(name);
    }
}

// test: when memory is allocated it appears in the linked list
// conditional: every block returned by malloc is in the linked list
void test_alloc(unsigned int global_memory, unsigned char *global_mem_size, char name[]){

    mem_init(global_memory, global_mem_size);
    unsigned int sizes[] = {50, 20, 20, 20, 50, 0};
    Block *arr[4];

    for (int i = 0; sizes[i] != 0; i++)
    {
        char buf[1024];
        arr[i] = my_malloc(sizes[i]);
    }

    for (int i = 0; sizes[i] != 0; i++)
    {
        if(inList(arr[i]) == 0){
            printfail(name);
            return;
        }
    }
    printpass(name);
}


// test: when memory is freed it is marked as free
// free a block and see if it is marked that way 'f'
void test_free(unsigned int global_memory, unsigned char *global_mem_size, char name[]){

    mem_init(global_memory, global_mem_size);
    unsigned int sizes[] = {50, 20, 20, 20, 50, 0};
    Block *arr[4];
    for (int i = 0; sizes[i] != 0; i++)
    {
        char buf[1024];
        arr[i] = my_malloc(sizes[i]);
    }
    // free a space
    my_free(arr[2]);

    if(arr[2]->status == 'f'){
        printpass(name);
    }
    else{
        printfail(name);
    }
}

// test: when two adjacent memory locations are freed, they get merged
// free two adjacent blocks and check if merged
void test_merge(unsigned int global_memory, unsigned char *global_mem_size, char name[]){

    mem_init(global_memory, global_mem_size);
    unsigned int sizes[] = {20, 20, 20, 20, 20, 0};
    Block *arr[10];

    for (int i = 0; sizes[i] != 0; i++)
    {
        char buf[1024];
        arr[i] = my_malloc(sizes[i]);
    }

    // now we will free up spaces 2 & 3
    int totSize = arr[2]->size + arr[3]->size;

    // free adjacent spaces
    my_free(arr[2]);
    my_free(arr[3]);

    if(arr[2]->size == totSize){
        printpass(name);
    }
    else{
        printfail(name);
    }
}

void runTests(unsigned int global_memory, unsigned char *global_mem_size){

    test_overload(global_memory, global_mem_size, "OVERLOAD\0");
    test_alloc(global_memory, global_mem_size, "ALLOC\0");
    test_free(global_memory, global_mem_size, "FREE\0");
    test_merge(global_memory, global_mem_size, "MERGE\0");
}


