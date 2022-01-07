# ifndef MY_MEM_DOT_H    /* This is an "include guard" */
# define MY_MEM_DOT_H


unsigned char *MEMORY;
unsigned int MAX_SIZE;
typedef struct blockType Block;
struct blockType;
Block *head;
Block *tail;
typedef struct mem_stats mem_stats_struct;
struct mem_stats;

# endif /* MY_MEM_DOT_H */