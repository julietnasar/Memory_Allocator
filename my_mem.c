# include <stdio.h>

/*this routine is guaranteed to be called before any of the other routines, 
and can do whatever initialization is needed.  The memory to be managed is passed into this routine. */
void mem_init(unsigned char *my_memory, unsigned int my_mem_size){
    return 0;
}

/* a function functionally equivalent to malloc() , but allocates it from the memory pool passed to mem_init() */
void *my_malloc(unsigned size){
    return 0
}

/* a function equivalent to free() , but returns the memory to the pool passed to mem_init()*/
void my_free(void *mem_pointer){
    return 0;
}
/*provides statistics about the current allocation of the memory pool.*/
void mem_get_stats(mem_stats_ptr mem_stats_ptr){
    return 0;
}

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


int main(){
    return 0;
}