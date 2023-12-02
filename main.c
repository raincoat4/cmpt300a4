#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int* cscan( int noOfJobs, int* jobs){
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
            tracksTraversed+=198;
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

void compareFairness(int* scan, int* cscan, int* fcfs, int length){
    int maxDelayS=0;
    int maxDelayC=0;
    int sumScan=0;
    int sumCscan=0;
    int numOfdelayScan=0;
    int numOfdelayCscan=0;
    
    for(int i=0; i<length;i++){
        for(int j=0; j<length;j++){
            if(fcfs[j]==scan[i]){
                if(i-j>0){
                    sumScan+=i-j;
                    numOfdelayScan++;
                    if(i-j>maxDelayS){
                        maxDelayS=i-j;
                    }
                }
                
            }
        }
    }

    for(int i=0; i<length;i++){
        for(int j=0; j<length;j++){
            if(fcfs[j]==cscan[i]){
                if(i-j>0){
                    sumCscan+=i-j;
                    numOfdelayCscan++;
                    if(i-j>maxDelayC){
                        maxDelayC=i-j;
                    }
                }
                
              
            }
        }
    }

    printf("%d\n", sumScan);
    printf("%d\n", sumCscan);
    printf("Scan avg delay: %d\n", (int)(sumScan/numOfdelayScan));
    printf("CSCAN avg delay: %d\n", (int)(sumCscan/numOfdelayCscan));
    printf("Max SCAN delay: %d\n", maxDelayS);
    printf("Max CSCAN delay: %d\n", maxDelayC);
    
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    int* jobs;
    int* jobsCopy;
    int* jobsCompare;
    int* test; 
    int* testc;
    //since the original jobs array is destroyed due to the design, make a copy so we can print out the original
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
        jobsCompare = (int*)malloc((argc-1)*sizeof(int));
        if(jobsCompare == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }
        for(int i = 1; i < argc; i++){
            jobs[i-1] = atoi(argv[i]);
            jobsCopy[i-1] = atoi(argv[i]);
            jobsCompare[i-1] = atoi(argv[i]);
        }
        printf("original array\n");
        for(int i = 0; i < argc-1; i++){
            printf("%d ", jobsCompare[i]);
            if(i%10==0){
                printf("\n");
            }
        }
        printf("\n");

        test = scan(argc-1, jobs);
        testc = cscan(argc-1, jobsCopy);
        printf("order visited: ");
        for(int i = 0; i < argc-1; i++){
            printf("%d\t", test[i]);
            if(i%10==0){
                printf("\n");
            }
        }
        printf("\n");
        printf("tracks traversed: %d\n", test[argc-1]);
        
        printf("order visited: ");
        for(int i = 0; i < argc-1; i++){
            printf("%d\t", testc[i]);
            if(i%10==0){
                printf("\n");
            }
        }
        printf("\n");
        printf("tracks traversed: %d\n", testc[argc-1]);
        
        compareFairness(test, testc, jobsCompare, argc-1);
    }
    //else we just make a random list
    else if(argc == 1){
        
        jobs = (int*)malloc(50*sizeof(int));
        if(jobs == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }

        jobsCopy = (int*)malloc(50*sizeof(int));
        if(jobsCopy == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }
        jobsCompare = (int*)malloc(50*sizeof(int));
        if(jobsCompare == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }
        for(int i = 0; i < 50; i++){
            jobs[i] = rand()%200;
            jobsCopy[i] = jobs[i];
            jobsCompare[i]=jobs[i];
        }
        printf("original array\n");
        for(int i = 0; i < argc-1; i++){
            printf("%d ", jobsCompare[i]);
            if(i%10==0){
                printf("\n");
            }
        }
        printf("\n");
        test = scan(50, jobs);
        testc = cscan(50, jobsCopy);
        printf("SCAN order visited: ");
        for(int i = 0; i < 50; i++){
            printf("%d\t", test[i]);
            if(i%10==0){
                printf("\n");
            }
        }
        printf("\n");
        printf("SCAN tracks traversed: %d\n", test[50]);

        printf("\n");
        printf("CSCAN order visited: ");
        for(int i = 0; i < 50; i++){
            printf("%d\t", testc[i]);
            if(i%10==0){
                printf("\n");
            }
        }
        printf("\n");
        printf("CSCAN tracks traversed: %d\n", testc[50]);
        
        /*
        printf("\n");
        for(int i = 0; i < 50; i++){
            printf("%d ", stupidJobs[i]);
        }
        */
        
        compareFairness(test, testc, jobsCompare,49);
    }
    free(jobs);
    free(jobsCopy);
    free(test);
    free(testc);

}