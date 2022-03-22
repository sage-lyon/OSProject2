#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include "prod_cons_MT.h"

monitor m;
int buffer_size, num_producers, num_consumers;

int main(int argc, char **argv) {
	
    // Ensure correct number of arguments
    assert(argc == 4);

    // Assign variables according to arguments
    buffer_size = atoi(argv[1]);
    num_producers = atoi(argv[2]);
    num_consumers = atoi(argv[3]);

    // Ensure buffer_size is greater than 0 and create buffer
    assert(buffer_size > 0);
    int buffer[buffer_size];

    // Initialize monitor m
    monitor_init(&m, buffer);

    // Create list of producers and consumers
    pthread_t prod[num_producers];
    pthread_t cons[num_consumers];

    // Create id list for producers and consumers
    int prod_id[num_producers];
    int cons_id[num_consumers];

    // Create producer and consumer threads
    for(int i = 0; i < num_producers; i++){
        prod_id[i] = i;
        pthread_create(&prod[i], NULL, producer, &prod_id[i]);
    }
    
    for(int i = 0; i < num_consumers; i++){
        cons_id[i] = i;
        pthread_create(&cons[i], NULL, consumer, &cons_id[i]);
    }

    // Join producer and consumer threads
    for(int i = 0; i < num_producers; i++)
        pthread_join(prod[i], NULL);
    
    for(int i = 0; i < num_consumers; i++)
        pthread_join(cons[i], NULL);

    return 0;
}
