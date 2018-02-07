#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include "phylosophers.h"
sem_t kick_off; //An initial blocker, as there are no guarantees phylosophers will not try eating "at the same time"
sem_t semaphore_device[PHYLOSOPHERS_COUNT];
pthread_mutex_t mutex_device[PHYLOSOPHERS_COUNT];

void *semaphore_have_lunch(void *arguments) { //Should parse arguments at some point. :D
    //Sleep random time, so concurrency can be simulated.
    int r = rand() % 10; 
    
    int phylosopher_number = (int *)arguments; //That's the point    
    printf("%*cSemaphore phylosopher %d thinks...\n", phylosopher_number*4, ' ', phylosopher_number);            
    short right_device = (phylosopher_number+1) % PHYLOSOPHERS_COUNT;
    short left_device = phylosopher_number;
    sleep(r);
    printf("%*cSemaphore phylosopher %d waiting for left device %d and right device %d\n", phylosopher_number*4, ' ', phylosopher_number, left_device, right_device);
    sem_wait(&semaphore_device[left_device]);        
    sem_wait(&semaphore_device[right_device]);
    printf("%*cSemaphore phylosopher %d eats...\n", phylosopher_number*4, ' ', phylosopher_number);
    r = rand() % 10; 
    sleep(r);
    sem_post(&semaphore_device[phylosopher_number]);
    sem_post(&semaphore_device[(phylosopher_number+1) % PHYLOSOPHERS_COUNT]);        
    pthread_exit(0);
}
void *mutex_have_lunch(void *arguments) { //Should parse arguments at some point. :D
    //Sleep random time, so concurrency can be simulated.
    int r = rand() % 10;
    int phylosopher_number = (int *)arguments; //That's the point    
    printf("%*cMutex phylosopher %d thinks...\n", phylosopher_number*4, ' ', phylosopher_number);        
    sleep(r);
    short right_device = (phylosopher_number+1) % PHYLOSOPHERS_COUNT;
    short left_device = phylosopher_number;
    printf("%*cMutex phylosopher %d waiting for left device %d and right device %d\n", phylosopher_number*4, ' ', phylosopher_number, left_device, right_device);
    pthread_mutex_lock(&mutex_device[left_device]);        
    pthread_mutex_lock(&mutex_device[right_device]);
    printf("%*cMutex phylosopher %d eats...\n", phylosopher_number*4, ' ', phylosopher_number);
    r= rand() % 10;
    sleep(r);
    pthread_mutex_unlock(&mutex_device[phylosopher_number]);
    pthread_mutex_unlock(&mutex_device[(phylosopher_number+1) % PHYLOSOPHERS_COUNT]);     
    pthread_exit(0);
}
int main(int argc, char **argv)
{    
    pthread_t mutex_phylosophers[PHYLOSOPHERS_COUNT]; 
    pthread_t semaphore_phylosophers[PHYLOSOPHERS_COUNT]; 
    //Initialize semaphores with initial value 1 + the let's fo semaphore, so it can hold off the hungry phylosophers. (:
   
    for(int i=0;i<PHYLOSOPHERS_COUNT;i++) {
        sem_init(&semaphore_device[i], 0, 1);    
    }
    for (int i = 0; i < PHYLOSOPHERS_COUNT; i++) {
        pthread_create(&semaphore_phylosophers[i], NULL, &semaphore_have_lunch, (void*)i);
        pthread_create(&mutex_phylosophers[i], NULL, &mutex_have_lunch, (void*)i);
    }
	
    for (int i = 0; i < PHYLOSOPHERS_COUNT; i++) {        
        pthread_join(semaphore_phylosophers[i], NULL);
        pthread_join(mutex_phylosophers[i], NULL);
    }
    for (int i = 0; i < PHYLOSOPHERS_COUNT; i++) {        
        sem_destroy(&semaphore_device[i]);
    }
    
    return 0;
}
