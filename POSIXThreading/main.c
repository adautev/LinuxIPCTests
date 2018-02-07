#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include "phylosophers.h"
sem_t kick_off; //An initial blocker, as there are no guarantees phylosophers will not try eating "at the same time"
sem_t device[PHYLOSOPHERS_COUNT];

void *have_lunch(void *arguments) { //Should parse arguments at some point. :D
    //Sleep random time, so concurrency can be simulated.
    int r = rand() % 10; 
    sleep(r);
    int phylosopher_number = (int *)arguments; //That's the point    
    printf("%*cPhylosopher %d thinks...\n", phylosopher_number*4, ' ', phylosopher_number);        
    short right_device = (phylosopher_number+1) % PHYLOSOPHERS_COUNT;
    short left_device = phylosopher_number;
    printf("%*cPhylosopher %d waiting for left device %d and right device %d\n", phylosopher_number*4, ' ', phylosopher_number, left_device, right_device);
    sem_wait(&device[left_device]);        
    sem_wait(&device[right_device]);
    printf("%*cPhylosopher %d eats...\n", phylosopher_number*4, ' ', phylosopher_number);
    sem_post(&device[phylosopher_number]);
    sem_post(&device[(phylosopher_number+1) % PHYLOSOPHERS_COUNT]);        
    pthread_exit(0);
}

int main(int argc, char **argv)
{    
    pthread_t phylosophers[PHYLOSOPHERS_COUNT]; 
    //Initialize semaphores with initial value 1 + the let's fo semaphore, so it can hold off the hungry phylosophers. (:
   
    for(int i=0;i<PHYLOSOPHERS_COUNT;i++) {
        sem_init(&device[i], 0, 1);    
    }
    for (int i = 0; i < PHYLOSOPHERS_COUNT; i++) {
        pthread_create(&phylosophers[i], NULL, &have_lunch, i);        
    }
	
    for (int i = 0; i < PHYLOSOPHERS_COUNT; i++) {        
        pthread_join(phylosophers[i], NULL);
    }
    for (int i = 0; i < PHYLOSOPHERS_COUNT; i++) {        
        sem_destroy(&device[i]);
    }
    
        return 0;
}
