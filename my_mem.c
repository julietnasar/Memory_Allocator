# include <stdio.h>
# include <stdlib.h>
# include <string.h>





unsigned char *MEMORY;
unsigned int MAX_SIZE;

// structure for memory location blocks
typedef struct blockType Block;
struct blockType {
    unsigned int size;       // size in mem locations of this block
    unsigned int loc; // relative loc at this point in memory (in relation to MEMORY allocated from init)
    char status;    // 'a' for allocated 'f' for free
    struct blockType *prev;    // pointer to previous Block
    struct blockType *next;    // pointer to next block
};

// head of the linked list & the current node must be global
Block *head;
Block *tail;



// --> oldBlock --> newBlock --> oldBlock.next
void insertFront(Block *newBlock, Block *oldBlock){

    oldBlock->next->prev = newBlock;
    newBlock->next = oldBlock->next;

    oldBlock->next = newBlock;
    newBlock->prev = oldBlock;
}

/*---------------------------------*/
// direction: 
// 'b' for backwards
// 'f' for forwards
// finds next free block going forwards or backwards
Block *findFurthestFree(char direction){
    // start at taul
    Block *cur = tail;
    // if 'b' go backwards
    if(direction == 'b'){
        while(cur->prev != NULL && cur->status == 'f'){
            cur = cur->prev;
        }
    }
    // if 'f' go forwards
    else if(direction == 'f'&& cur->status == 'f'){
        while(cur-> next != NULL){
            cur = cur->next;
        }
    }
    return cur;
}

// prints the linked list from head -> tail

void printLL(){

    Block *b = head;
    while(b->status != 't'){
        printf("[location: %d, size: %d, status: %c] -->",
        b->loc,
        b->size,
        b->status);
        b = b->next;
    }
    printf(" TAIL\n");
}

void printBlock(Block *b){
    while(b->status != 't'){
        printf("[location: %d, size: %d, status: %c] -->",
        b->loc,
        b->size,
        b->status);
        b = b->next;
    }
}

// function to create a Block
Block *createBlock(unsigned int size, unsigned int loc, char status, Block *prev, Block *next){
    
    Block *newBlock;

    newBlock = (Block *)malloc(sizeof(Block));

    newBlock->size = size;
    newBlock->loc;
    newBlock->status = status;
    newBlock->prev = prev;
    newBlock->next = next;
    
    
    return newBlock;
}

// -->  oldBlock.prev --> newBlock --> oldBlock --> 
void insertBehind(Block *newBlock, Block *oldBlock){

    // adjust oldBlock loc & size
    oldBlock->size = oldBlock->size - newBlock->size;   // new size is old size - size of new block
    newBlock->loc=oldBlock->loc;
    oldBlock->loc= oldBlock->loc + newBlock->size;      // new loc is old loc + size of new block


    // if at head
    if(oldBlock->prev == NULL){

        oldBlock->prev = newBlock;
        newBlock->next = oldBlock;

        head = newBlock;
        return;
    }

    

    // oldBlock->prev <-- newBlock --> oldBlock
    newBlock->next = oldBlock;
    newBlock->prev = oldBlock->prev;

    // oldBlock->prev --> newBlock <-- oldBlock
    newBlock->next->prev = newBlock;
    newBlock->prev->next = newBlock;
    
    
}

/*this routine is guaranteed to be called before any of the other routines, 
and can do whatever initialization is needed.  The memory to be managed is passed into this routine. */
void mem_init(unsigned char *my_memory, unsigned int my_mem_size){
    
    // assign global vars
    MEMORY = my_memory;
    MAX_SIZE = my_mem_size;

    //printf("%u\n%u\n", mem_lower_bound, mem_upper_bound);

    // initialize head block
    unsigned int size = my_mem_size;
    unsigned int running_size = my_mem_size;
    char status = 'f';         // entire memory free at first

    // the head will ALWAYS have NULL for prev
    // as user allocates mem, will fill in next
    head = createBlock(size, 0, status, NULL, NULL);
    // tail acts as NULL ptr with no real value except being at the end
    // but this is important and allows us to backtrack from the end of the list
    tail = createBlock(0, 0, 't', NULL, NULL);  // status is 't' for tail 
    
    head->next = tail;
    tail->prev = head;

}



//a function functionally equivalent to malloc() , but allocates it from the memory pool passed to mem_init() 
void *my_malloc(unsigned size){

    // validate size
    if(size <= 0){
        printf("invalid size input, size must be > 0, allocation failed");
        return NULL;
    }

    // first try and find a free block within the linked list
    Block *b = head;

    int diff;

    unsigned int loc;

    // if status is t we reached tail
    while(b->status != 't'){
        
        /*printf("[location: %d, size: %d, status: %c] -->",
        b->loc,
        b->size,
        b->status);*/

        // if we found a free block that is a fit size-wise    
        if(b->status == 'f' && b->size >= size){

            // get size difference    
            diff = b->size - size;

            // if not exact fit 
            if(diff > 0){
                
                
                // store b's starting loc
                loc = b->loc;
                
                // create new block at b's starting loc, 
                // of specified size,
                // with location at b's starting loc
                Block *newBlock = createBlock(size, loc, 'a', NULL, NULL);
                
                // insert newBlock behind b
                // b.prev --> newBlock --> b
                insertBehind(newBlock, b);
                

                // we allocated so we can return
                return newBlock;
                
            }
            
            
        }
        // keep looking for a suitable empty block
        b = b->next;
        
    }

    // if got here, we did not find an empty space big enough in the current 
    // linked list, so we will try to add on to the end

    unsigned int next_free_loc = tail->prev->loc + tail->prev->size+1;

    // if allocating this block goes beyond the upper bound, exit
    if(next_free_loc + size > MAX_SIZE){
        printf("OUT OF BOUNDS, no more space to allocate, allocation unsuccessful");
        return NULL;
    }

    // if within bounds create new block & insert right before tail
    // head --> .... tail.prev --> newBlock --> tail
    


    Block *newBlock = createBlock(next_free_loc, size, 'a', NULL, NULL); 
    
    tail->prev->next = newBlock;
    newBlock->prev = tail->prev;

    newBlock->next = tail;
    tail->prev = newBlock;

    
    return newBlock;

}

Block *leftmostFree(Block *b){
    Block *cur = b;
    // go left until reach head or hit non free block
    while(cur != head && cur->prev->status == 'f'){
        cur = cur->prev;
    }
    // return leftmost free
    return cur;
}

Block *rightmostFree(Block *b){
    Block *cur = b;
    // go right until reach head or hit non free block
    while(cur != tail && cur->next->status == 'f'){
        cur = cur->next;
    }
    // return rightmost free
    return cur;
}

// block a must be befpre block b location wise
// a ---> b ---> c
// a ------------> c
void merge(Block *a, Block *b){

    // a is acquiring b, so add
    // b's size to a's size
    a->size += (b->loc - a->loc);

    // skip over middle
    a->next = b->next;
    b->next->prev = a;
    
}



// a function equivalent to free() , but returns the memory to the pool passed to mem_init()
void my_free(void *mem_pointer){

    // get mem_pointer's offset from the beginning
    // of our entire memory block
    Block *b = (Block*)mem_pointer;
    int loc_target = b->loc;

    // go through ll starting with head to find the pointer
    Block *target = head;

    // while there is a next, go through linked list
    // until we reach the tail ('t')
    while(target->status != 't'){
        // if we found our target memory location, break
        if(target->loc == loc_target){
            break;
        }
        // otherwise continue the search
        target = target->next;
    }

    // at this point target either contains the block we were looking
    // for or it didn't find it and target is the tail

    // if not found return
    if(target->status == 't'){
        printf("target not found\n");
        return;
    }

    // if target already freed, return from func call
    if (target->status == 'f')
    {
        return;
    }

    // otherwise free the block
    // set target's status to free
    target->status = 'f';
    
    // check to see if we should merge with blocks behind or ahead
    // of the newly freed block

    Block *left = leftmostFree(target);
    if(left != target){
        merge(left, target);
    }

    Block *right = rightmostFree(target);
    if(right != target){
        merge(target, right);
    }
}


// structure for memory location blocks
typedef struct mem_stats mem_stats_struct;
struct mem_stats {
    int num_blocks_free;
	int num_blocks_used;
	int smallest_block_free;
	int largest_block_free;
	int smallest_block_used;
	int largest_block_used;
};

// provides statistics about the current allocation of the memory pool.
void mem_get_stats(mem_stats_struct *mem_stats){

    // first sum vars to 0
    int sum_free = 0;
    int sum_used = 0;

    // set to NULL
    int largest_free = 0;
    int largest_alloc = 0;
    int smallest_free = 0;
    int smallest_alloc = 0;

    // go through linked list starting with head
    Block *b = head;
    
    // go until we reach tail
    while(b->status != 't'){

        // increase sum stats
        char status = b->status;
        int size = b->size;
        if(status == 'f'){
            sum_free += 1; // increase sum free blocks

            // check if larger than largest free
            if(size > largest_free){
                largest_free = size;
            }
            // check if smaller than smallest free
            else if(size < largest_free){
                smallest_free = size;
            }

        }
        if(status == 'a'){
            sum_used += 1; // increase sum of used blocks

            // check if larger than largest free
            if(size > largest_alloc){
                largest_alloc = size;
            }
            // check if smaller than smallest alloc
            else if(size < largest_alloc){
                smallest_alloc = size;
            }
        }

        // get next mem block
        b = b->next;
    }

     // set stats to inputted mem_stats_struc
     mem_stats->num_blocks_free = sum_free;
     mem_stats->num_blocks_used = sum_used;
     mem_stats->largest_block_free = largest_free;
     mem_stats->largest_block_used = largest_alloc;
     mem_stats->smallest_block_free = smallest_free;
     mem_stats->smallest_block_used = smallest_alloc;
}


void print_stats(char *prefix) {

    mem_stats_struct *mem_stats;
    mem_stats = (mem_stats_struct *)malloc(sizeof(mem_stats_struct));

    mem_get_stats(mem_stats);
    printf("mem stats: %s: %d free blocks, %d used blocks, free blocks: smallest=%d largest=%d, used blocks: smallest=%d largest=%d\n",
	    prefix,
	    mem_stats->num_blocks_free,
	    mem_stats->num_blocks_used,
	    mem_stats->smallest_block_free,
	    mem_stats->largest_block_free,
	    mem_stats->smallest_block_used,
	    mem_stats->largest_block_used);
} 



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
    
} 

