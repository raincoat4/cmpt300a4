#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
int* cScan( int noOfJobs, int* jobs){
    int* order = (int*)malloc((noOfJobs+1)*sizeof(int));
    if(order == NULL){
        return NULL;
    }
    int jobsLeft = noOfJobs;
    int head = jobs[0];
    int tracksTraversed = 0;
    while(jobsLeft > 0){
        tracksTraversed += 1;
        for(int i = 0; i < noOfJobs; i++){
            if(head == jobs[i]){
                order[noOfJobs-jobsLeft] = jobs[i];
                jobs[i] = -1;
                jobsLeft -= 1;
            }
        }
        
        if(head >= 199){
            head = 0;
        }
        else{
            head += 1;
        }
    }
    order[noOfJobs] = tracksTraversed;
    return order;
}

int* scan(int noOfJobs, int* jobs){ // this works
    //+1 because the last element in the array will be the tracks traversed
    int* order = (int*)malloc((noOfJobs+1)*sizeof(int));
    if(order == NULL){
        return NULL;
    }
    int jobsLeft = noOfJobs;
    int head = jobs[0];
    int tracksTraversed = 0;
    bool movingLeft = true;
    while(jobsLeft > 0){
        tracksTraversed += 1;
        for(int i = 0; i < noOfJobs; i++){
            if(head == jobs[i]){
                order[noOfJobs-jobsLeft] = jobs[i];
                jobs[i] = -1;
                jobsLeft -= 1;
            }
        }
        if(head <= 0){
            movingLeft = false;
        }
        if(head >= 199){
            movingLeft = true;
        }

        if(movingLeft){
            head -= 1;
        }
        else{
            head += 1;
        }
    }
    order[noOfJobs] = tracksTraversed;
    return order;
}

int main(int argc, char* argv[]){
    int* jobs;
    int* jobsCopy; //since the original jobs array is destroyed due to the design, make a copy so we can print out the original
    //and also calculate delay

    //if user inputs arguments
    //gotta convert them all to ints
    //also noOfJobs would be argc-1
    if(argc > 1){
        jobs = (int*)malloc((argc-1)*sizeof(int));
        if(jobs == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }

        jobsCopy = (int*)malloc((argc-1)*sizeof(int));
        if(jobsCopy == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }
        for(int i = 1; i < argc; i++){
            jobs[i-1] = atoi(argv[i]);
            jobsCopy[i-1] = atoi(argv[i]);
        }

        int* test = scan(argc-1, jobs);
        printf("order visited: ");
        for(int i = 0; i < argc-1; i++){
            printf("%d ", test[i]);
        }
        printf("\n");
        printf("tracks traversed: %d\n", test[argc-1]);
        /* prints original array
        for(int i = 0; i < argc-1; i++){
            printf("%d ", stupidJobs[i]);
        }
        */
    }
    //else we just make a random list
    else if(argc == 1){
        jobs = (int*)malloc(50*sizeof(int));
        if(jobs == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }

        jobsCopy = (int*)malloc((argc-1)*sizeof(int));
        if(jobsCopy == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }
        for(int i = 0; i < 50; i++){
            jobs[i] = rand()%200;
            jobsCopy[i] = jobs[i];
        }
        int* test = scan(50, jobs);
        printf("order visited: ");
        for(int i = 0; i < 50; i++){
            printf("%d ", test[i]);
        }
        printf("\n");
        printf("tracks traversed: %d\n", test[50]);
        /*
        printf("\n");
        for(int i = 0; i < 50; i++){
            printf("%d ", stupidJobs[i]);
        }
        */
    }
    
}