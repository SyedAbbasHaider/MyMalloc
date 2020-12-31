#include <stdio.h>
#include <stdlib.h>

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )       //defining macro for malloc calls
#define free( x ) myfree( x, __FILE__, __LINE__ )           //defining macro for free calls

//Big chunk of memory for allocation
static char myblock[4097];

//struct for the metadata of each block
typedef struct metadata
{
    //char* data;
    size_t remsize;                                      //size of block described by it
    int isfree;                                             //to tell if space is allocated before. 1-yes and 0-no  
    struct metadata *next_node;                             //pointing to the next metadata in linked list
    struct metadata *curr_node;
    struct metadata *prev_node;
}node;

//pointer that points to the start of the memory
//struct metadata *root; = (void*)myblock;                      //type is void because we dont know the type of data for allocation yet

void initialize();
void merge();
void split(node *head, size_t sizewanted);
void mymalloc(size_t sizewanted);
void myfree(void* ptr);


