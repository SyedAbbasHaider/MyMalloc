#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 
 //gettimeofday(struct timeval * tv, struct timezone * tz);
 
void* arr[200];

double time_takenA;
double time_takenB;
double time_takenC;
double time_takenD;
double time_takenE;
double time_takenF;

//record runtime for each workload
//gettimeofday(struct timeval * tv, struct timezone * tz);


//run all the workload 100 time, use a loop but for loop is not working

//int i;

//malloc() 1 byte and immediately free it - 150 time
void workloadA(){

    clock_t start, end;
    start = clock();
    int i;
    for (i = 0; i <= 150; i++)
    {
        arr[i] = malloc(1);                         //malloc 1 byte at a time
        printf("malloed workloadA");
        free(arr[i]);                                  //immediately free it
        printf("freed workloadA");
    }

    end = clock();
    time_takenA = ((double) end - start) / CLOCKS_PER_SEC;
    

}


//malloc() 1 byte, store the pointer in an array - do this 150 times
//Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
void workloadB(){

    clock_t start, end;
    start = clock();

    int i;
    //malloc 150 times
    for (i = 0; i <= 150; i++)
    {
        arr[i] = malloc(1);
        //when malloced 50 times run free
        printf("malloced workloadB");
        if (i = 50)
        {
            //free those 50 bytes
            for ( i = 0; i <= 50; i++)
            {
                free(arr[i]);
                printf("freed workloadB");
            }    
        }
    }

    end = clock();

    time_takenB = ((double) end - start) / CLOCKS_PER_SEC;

}

void workloadC(){

    clock_t start, end;

    start = clock();

    int i;

    //choose random number
    int ran = rand();

    if (ran % 2 == 0)
    {
        for (i = 0; i <= 50; i++)
    {
            arr[i] = malloc(1);
    }
    printf("malloced workloadC");
    }
    
    else
    {
        for (i = 0; i <= 50; i++)
        {
            while (malloc(i) != 0)
            {
                free(arr[i]);
            }
        }
        
    }
    printf("freed workloadC");

    end = clock();

    time_takenC = ((double) end - start) / CLOCKS_PER_SEC;
}


void workloadD(){

    clock_t start, end;

    start = clock();

    int i;

    //randomly choose a number between 1 and 64
    int remnum;
    remnum = rand() % 64 + 1;

    //randomly choose between a randomly-sized malloc() or free()ing a pointer
    int ran = rand();
    for (i = 0; i <= 50; i++)
    {
        if (ran % 2 == 0)
        {
            arr[i] = malloc(remnum);
        }
        //printf("malloed workloadD");
        else            //else gives error when print is put above it
        {
            free(arr[i]);
            printf("freed workloadD");
        }    
    }

    end = clock();
    time_takenD = ((double) end - start) / CLOCKS_PER_SEC;

}
   

/*

//workloadE free 1 and 3 then free middle one
void workloadE(){

    clock_t start, end;
    start = clock();

    //choose a random mnumber
    int ran;
    ran = rand();

    end = clock();
    time_takenE = ((double) end - start) / CLOCKS_PER_SEC;

}





//do some test here
void workloadF(){

    clock_t start, end;
    start = clock();


    end = clock();
    ((double) end - start) / CLOCKS_PER_SEC;

}
*/

//calculate time 
double totaltime = time_takenA + time_takenB + time_takenC + time_takenD;


