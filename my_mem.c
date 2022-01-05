# include <stdio.h>
# include <math.h>



/*----------------------------------------------------
------------------- UTIL FUNCTIONS -------------------
----------------------------------------------------*/

int myPow(int base, int exp){
    int ans = 1;
    for(int i = 0; i < exp; i++){
        ans = ans*base;
    }
    return ans;
}
/*
int blankRoot(int blank, int num){
    for(int i = 0; i < blank; i++){
        num = sqrt(num);
    }
    return num;
}*/

// returns array of exponents with specified base
// and exponent range
int fillExp(int arr[], int base, int expStart, int expEnd){
    int size = expEnd - expStart;
    // go through exponents & add to arr 
    for(int i = 0; i <= size; i++){
        arr[i] = myPow(base, expStart + i);
    }
}

int fillPartitions(int arr[]){
    return 0;
}

/*----------------------------------------------------
----------------------------------------------------*/


/*this routine is guaranteed to be called before any of the other routines, 
and can do whatever initialization is needed.  The memory to be managed is passed into this routine. */
// what data structure do you wanna use to store the memory?
void mem_init(unsigned char *my_memory, unsigned int my_mem_size){
    
    // create a stack with pointers to different sizes

    // get array of sizes for our stacks
    // base = 2, expStart = 2, expEnd = 11
    
    // vars for exponent arr
    int base = 2;
    int expStart = 0;
    // how many powers of two we can have
    // with this mem size
    int expEnd = log2(my_mem_size);

    
    // exponent arr
    static int expArr[expEnd - expStart];
    // fill array
    fillExp(expArr, base, expStart, expEnd); 


    
    for(int i = 0; i < (expEnd-expStart); i++){
        printf("%d\n", expArr[i]);
    }
    

   /* 
   strategy: have different stacks with different sizes memory chunks
   when the user asks for a chunk of memory, find the size that is closest
   to the memory size required, and allocate it

   if there is no free memory for that size, allocate from another stack

    know that a memory chunk is empty if 'e' stored in that spot
   */

    // represents number of sections we will have
    /*
    int numPartitions = expEnd - expStart;

    int sizePerPartition = my_mem_size/numPartitions;

    printf("%d", sizePerPartition);
    */


}

/*
//a function functionally equivalent to malloc() , but allocates it from the memory pool passed to mem_init() 
void *my_malloc(unsigned size){
}

// a function equivalent to free() , but returns the memory to the pool passed to mem_init()
void my_free(void *mem_pointer){
}
// provides statistics about the current allocation of the memory pool.
void mem_get_stats(mem_stats_ptr mem_stats_ptr){
}
*/
/*
void print_stats(char *prefix) {
  mem_stats_struct mem_stats;

  mem_get_stats(&mem_stats);
  printf("mem stats: %s: %d free blocks, %d used blocks, free blocks: smallest=%d largest=%d, used blocks: smallest=%d largest=%d\n",
	 prefix,
	 mem_stats.num_blocks_free,
	 mem_stats.num_blocks_used,
	 mem_stats.smallest_block_free,
	 mem_stats.largest_block_free,
	 mem_stats.smallest_block_used,
	 mem_stats.largest_block_used);
} 
*/


int main(int argc, char **argv)
{

    unsigned int global_mem_size = 1024 * 1024;
    unsigned char *global_memory = malloc(global_mem_size);

    mem_init(global_memory, global_mem_size);
    
    //print_stats("init");

    /*
    unsigned char *ptr_array[10];
    unsigned int sizes[] = {50, 20, 20, 20, 50, 0};

    for (int i = 0; sizes[i] != 0; i++)
    {
        char buf[1024];
        ptr_array[i] = my_malloc(sizes[i]);

        sprintf(buf, "after iteration %d size %d", i, sizes[i]);
        print_stats(buf);
    }

    my_free(ptr_array[1]);
    print_stats("after free #1");

    my_free(ptr_array[3]);
    print_stats("after free #3");

    my_free(ptr_array[2]);
    print_stats("after free #2");

    my_free(ptr_array[0]);
    print_stats("after free #0");

    my_free(ptr_array[4]);
    print_stats("after free #4"); */
    
} 

