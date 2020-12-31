#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

node* head;                                                         //pointer to the head of an array

int errorcount;                                                     //count number of time error occurs

head = (void *) myblock;

//initialize metadata for the first time
void initialize(){
    head -> remsize = myblock - sizeof(node);
    head -> isfree = 1;
    head -> next_node = NULL;                                       //there is no next metadata block yet
}


//split function to split the memory, pointer to the metadata block and size of chuck to be allocated
void split(node *head, size_t sizewanted){
    node *new = head + sizewanted + sizeof(node);
    new -> remsize = (head -> remsize) - sizeof(node) - sizewanted;
    new -> isfree = 1;                                                 //memory is not yet allocated
    new -> next_node = head -> next_node;                              //points to the next free chunk
    head -> remsize = sizewanted;
    head -> isfree = 0;                                                //memory is allocated
    head -> next_node = new;
    }



void mymalloc(size_t sizewanted){ 


    void* result;                                                       //to return the starting address of allocated chunk

    if (sizewanted < 0)
    {
        printf("ERROR: please enter a valid size to malloc");
        return;
    }

    if ((sizewanted + sizeof(node)) > myblock)
    {
        printf("ERROR: size to high");
        return;
    }

    //check if memory initialized
    if (!(head -> remsize))
    {
        initialize();
    }
    

    node* curr_node = head;                                         //temporary pointer to point to the start of the metadata list
    node* prev_node;
      
    //if chunk of memory fit the required size.
    if (sizewanted == (curr_node->remsize))                                
    {
        curr_node->isfree = 0;
        result = ++curr_node;
        printf("block allocated");
    }
    //split the memory because it is too big
    else if (curr_node->remsize > (sizewanted + sizeof(node)))
    {
        split(curr_node, sizewanted);
        printf("block allocated with a split");
    }
    else
    {
        //no memory left
        result = NULL;
        printf("no memory remain");
        return;
    }
}

//function to merge two consecutive spaces
void merge(){
    node* curr_node;
    node* prev_node;
    while (curr_node != NULL)
    {
        if (curr_node->isfree && curr_node->next_node->isfree)
        {
            curr_node->remsize += (curr_node->next_node->remsize) + sizeof(node);
            curr_node->next_node = curr_node->next_node->next_node;
        }
        prev_node = curr_node;
        curr_node = curr_node->next_node;
    }
}


void myfree(void* ptr){
    node* curr_node = ptr;
    //--curr_node;
    curr_node->isfree = 1;
    merge();
    
}