# ifndef MY_MEM_DOT_H    /* This is an "include guard" */
# define MY_MEM_DOT_H

// from my_mem
unsigned char *MEMORY;
unsigned int MAX_SIZE;
typedef struct blockType Block;
struct blockType;
Block *head;
Block *tail;
void printLL();
void printBlock(Block *b);
int inList(Block *target);
Block *createBlock(unsigned int size, unsigned int loc, char status, Block *prev, Block *next);
void insertBehind(Block *newBlock, Block *oldBlock);
void mem_init(unsigned char *my_memory, unsigned int my_mem_size);
void *my_malloc(unsigned size);
Block *leftmostFree(Block *b);
Block *rightmostFree(Block *b);
void merge(Block *a, Block *b);
void my_free(void *mem_pointer);
typedef struct mem_stats mem_stats_struct;
struct mem_stats;
void mem_get_stats(mem_stats_struct *mem_stats);
void print_stats(char *prefix);

// from test file
void runTests(unsigned int global_memory, unsigned char *global_mem_size);
void printpass(char testName[]);
void printfail(char testName[]);
void test_overload(unsigned int global_memory, unsigned char *global_mem_size, char name[]);
void test_alloc(unsigned int global_memory, unsigned char *global_mem_size, char name[]);
void test_free(unsigned int global_memory, unsigned char *global_mem_size, char name[]);
void test_merge(unsigned int global_memory, unsigned char *global_mem_size, char name[]);


// from main
int main(int argc, char **argv);



# endif /* MY_MEM_DOT_H */