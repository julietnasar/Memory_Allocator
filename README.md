## Memory_Allocator
# Goal: provide a functional implementation of a memory allocator
# Implementation

To implement the memory allocator, I used a doubly linked list as my underlying data structure made up of Block structures.

Block Structure:
```c
typedef struct blockType Block;
struct blockType {
    unsigned int size;       // size in mem locations of this block
    unsigned int loc; // relative loc at this point in memory (in relation to MEMORY allocated from init)
    char status;    // 'a' for allocated 'f' for free
    struct blockType *prev;    // pointer to previous Block
    struct blockType *next;    // pointer to next block
};
```
Each Block has a size, which is the number of memory locations in the Block, a relative location with the first Block starting from 0, a status which is 'f' if the Block is free, 'a' if the Block has been allocated, and 't' in the special case that that Block is the tail, a pointer to the previous Block and a pointer to the next Block.


When the memory is first initilaized, the head and tail of the linked list are defined with the head being a free block that takes up the entire memory space allocated and the tail being after the head.
```c
    // the head will ALWAYS have NULL for prev
    // as user allocates mem, will fill in next
    head = createBlock(size, 0, status, NULL, NULL);
    // tail acts as NULL ptr with no real value except being at the end
    // but this is important and allows us to backtrack from the end of the list
    tail = createBlock(0, 0, 't', NULL, NULL);  // status is 't' for tail 
    
    head->next = tail;
    tail->prev = head;
```

The beauty of the double nature of the doubly linked list comes when traversal is neccesary. A problem that plagues memory allocators is freeing up consecutive free space blocks. 
For example lets say you have this memory structure:
alloc -> alloc -> alloc
you free the first block
free -> alloc -> alloc
you free the last block
free -> alloc -> free
you free the middle block
free -> free -> free

These three free blocks should be automatically merged to create a larger contiguous space in memory. 

I implemented this by checking the leftmost and rightmost free Blocks on either side of a newly freed block and merging them. See the code below

```c
    // check to see if we should merge with blocks behind or ahead of the newly freed block

    // find leftmost free block & rightmost free block
    Block *left = leftmostFree(target);
    Block *right = rightmostFree(target);

    // if both leftmost & rightmost free blocks, merge leftmost with rightmost
    if(left != target && right != target){
        merge(left, right);
    }
    // if just found leftmost free, merge with target
    else if(left != target){
        merge(left, target);
    }
    // if just found rightmost free, merge with target
    else{
        merge(target, right);
    }
```


# Functions Supported
- ```void mem_init(unsigned char *my_memory, unsigned int my_mem_size)``` : this routine is guaranteed to be called before any of the other routines, and can do whatever initialization is needed.  The memory to be managed is passed into this routine.
- ```void *my_malloc(unsigned size)``` : a function functionally equivalent to malloc() , but allocates it from the memory pool passed to mem_init().
- ```void my_free(void *mem_pointer)``` : a function equivalent to free() , but returns the memory to the pool passed to mem_init().
- ```void mem_get_stats(mem_stats_ptr mem_stats_ptr)``` : provides statistics about the current allocation of the memory pool.  mem_stats_ptr is defined as:

```c
typedef struct  {
  int num_blocks_used;
  int num_blocks_free;
  int smallest_block_free;
  int smallest_block_used;
  int largest_block_free;
  int largest_block_used;
} mem_stats_struct, *mem_stats_ptr;
```
- ```void printLL()``` : prints the linked list from head -> tail
- ```void printBlock(Block *b)``` : prints a specific Block
- ```Block *createBlock(unsigned int size, unsigned int loc, char status, Block *prev, Block *next)``` : creates a new Block, inserting in front of *prev and behind *next
- ```void insertBehind(Block *newBlock, Block *oldBlock)``` : insterts newBlock behind oldBlock in the linked list
- ```void merge(Block *a, Block *b)``` : merges from Block a to Block b
- ```Block *leftmostFree(Block *b)``` : returns leftmost free Block from *b
- ```Block *rightmostFree(Block *b)``` : returns rightmost free Block from *b

