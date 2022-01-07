
# include "my_mem.h"
# include "my_mem.c"
# include "tests.c"
# include <stdio.h>


int main(int argc, char **argv)
{

    unsigned int global_mem_size = 1024 * 1024;
    unsigned char *global_memory = malloc(global_mem_size);

    mem_init(global_memory, global_mem_size);

    print_stats("init");

    
    unsigned char *ptr_array[10];
    unsigned int sizes[] = {50, 20, 20, 20, 50, 0};

    for (int i = 0; sizes[i] != 0; i++)
    {
        char buf[1024];
        ptr_array[i] = my_malloc(sizes[i]);

        sprintf(buf, "after iteration %d size %d", i, sizes[i]);
        print_stats(buf);
        printLL();
    }

    my_free(ptr_array[1]);
    print_stats("after free #1");
    printLL();

    my_free(ptr_array[3]);
    print_stats("after free #3");
    printLL();

    my_free(ptr_array[2]);
    print_stats("after free #2");
    printLL();

    my_free(ptr_array[0]);
    print_stats("after free #0");
    printLL();

    my_free(ptr_array[4]);
    print_stats("after free #4"); 
    printLL();

    printf("\n\n------------------------------ TESTING ------------------------------\n\n");
    runTests(global_memory, global_mem_size);
    
}


