#include "prod_cons_MT.h"
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include "prod_cons_MT.c"

monitor m;

void monitor_init(monitor *m, int * passed_buffer) {
	m->consumer_location=0;
	m->producer_location=0;
	m->buffer_data_stored=0;
	m->buffer = passed_buffer;
	
}
int main(int argc, char **argv) {
	
    assert(argc == 4);

    int buffer_size = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);
    assert(buffer_size > 0);
    int buffer[buffer_size];

    pthread_t prod[num_producers];
    pthread_t cons[num_consumers];

    // Create producer and consumer threads
    for(int i = 0; i < num_producers; i++)
        pthread_create(&prod[i], NULL, &producer, &i);
    
    for(int i = 0; i < num_consumers; i++)
        pthread_create(&cons[i], NULL, &consumer, &i);

    // Join producer and consumer threads
    for(int i = 0; i < num_producers; i++)
        pthread_join(prod[i], NULL);
    
    for(int i = 0; i < num_consumers; i++)
        pthread_join(cons[i], NULL);

    return 0;
}
