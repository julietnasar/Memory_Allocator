# include <stdio.h>
# include <stdlib.h>
# include <string.h>


/*----------------------------------------------------
------------------- UTIL FUNCTIONS -------------------
----------------------------------------------------*/


// structure for memory location blocks
typedef struct blockType Block;
struct blockType {
    int start_loc;  // starting mem location of this memory block
    int size;       // size in mem locations of this block
    char status;    // 'a' for allocated 'f' for free
    struct blockType *prev;    // pointer to previous Block
    struct blockType *next;    // pointer to next block
};

// head of the linked list & the current node must be global
Block *head;
Block *cur;

// function to create a Block
Block *createBlock(int start_loc, int size, char status, Block *prev, Block *next){
    
    Block* newBlock;

    newBlock = (Block *)malloc(sizeOf(newBlock));

    newBlock->start_loc = start_loc;
    newBlock->size = size;
    newBlock->status = status;
    newBlock->prev = prev;
    newBlock->next = next;

    return newBlock;
}

// let upper bound be public so we know when we can't allocate any more memory
int upper_bound;

/*this routine is guaranteed to be called before any of the other routines, 
and can do whatever initialization is needed.  The memory to be managed is passed into this routine. */
void mem_init(unsigned char *my_memory, unsigned int my_mem_size){
    
    // set upper bound of memory
    // cannot go past here
    upper_bound = my_memory + my_mem_size;

    // initialize head block
    int startLoc = my_memory; // start at first location in memory
    int size = my_mem_size;
    char status = 'f';         // entire memory free at first

    // the head will ALWAYS have NULL for prev
    // as user allocates mem, will fill in next
    head = createBlock(startLoc, size, status, NULL, NULL);
    cur = head;   // for now cur is head


/*
    int cur;
    for(int i = 0; i < my_mem_size; i++){

        // cur is the ptr to the mem addr of my_mem + i
        cur = my_memory + i;
        printf("%u\t", cur);

    
    }
*/

}


//a function functionally equivalent to malloc() , but allocates it from the memory pool passed to mem_init() 
void *my_malloc(unsigned size){

    // set aside space to hold data of new block

    int prevEndLoc = cur->start_loc + cur->size;
    int loc = prevEndLoc + 1;

    // if allocating this block goes beyond the upper bound, exit
    if(loc + size > upper_bound){
        printf("OUT OF BOUNDS, no more space to allocate, allocation unsuccessful");
        return;
    }

    // if within bounds creare new block

    // find the previous block
    Block *prev;
    // if empty ll, head is prev
    if(head->next == NULL){
        prev = head;
    }
    // otherwise prev will be cur
    else{
        prev = cur;
    }

    Block *newBlock = createBlock(loc, size, 'a', prev, NULL); // next is null 

    cur->next = newBlock;  // set this block to be after cur
    cur = newBlock;        // set cur to be this block
    
}

// a function equivalent to free() , but returns the memory to the pool passed to mem_init()
void my_free(void *mem_pointer){



}
/*
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

