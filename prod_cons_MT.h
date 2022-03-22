#ifndef PROD_CONS_MT
#define PROD_CONS_MT

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _monitor {
    pthread_mutex_t prod_lock, cons_lock, buffer_data_stored_lock;
    pthread_cond_t CVP, CVC;
	int consumer_location;
	int producer_location;
	int buffer_data_stored;
	int *buffer;
} monitor;

void monitor_init(monitor *m, int *buffer);

void *producer(void *thread_id);

void *consumer(void *thread_id);

#endif
