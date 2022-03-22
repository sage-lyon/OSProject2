#include "prod_cons_MT.h"

extern monitor m;
extern int buffer_size, num_producers, num_consumers;

void monitor_init(monitor *m, int *buffer) {

    // Initialize monitor variables
	m->consumer_location = 0;
	m->producer_location = 0;
	m->buffer_data_stored = 0;
	m->buffer = buffer;

    // Initialize condition variables and locks
    pthread_cond_init(&m->CVP, NULL);
    pthread_cond_init(&m->CVC, NULL);
    pthread_mutex_init(&m->prod_lock, NULL);
    pthread_mutex_init(&m->cons_lock, NULL);
    pthread_mutex_init(&m->buffer_data_stored_lock, NULL);
	
}

void* producer(void * thread_id){
	printf("P%d: Producing %d values\n",*(int *)thread_id,buffer_size*2);
	
	for(int i = 0; i < buffer_size*2; i++){
		
        // Lock critical section
		pthread_mutex_lock(&m.prod_lock);

        // If the buffer is full wait on the condition variable
		while(m.buffer_data_stored >= buffer_size){
			printf("P%d: Blocked due to full buffer\n", *(int *)thread_id);
			pthread_cond_wait(&m.CVP, &m.prod_lock);
			printf("P%d: Done waiting on full buffer\n", *(int *)thread_id);
		}
		
	    // Write random number 0-10 to buffer	
		m.buffer[m.producer_location] = rand() % (11);
		printf("P%d: Writing %d to position %d\n", *(int *)thread_id, m.buffer[m.producer_location], m.producer_location);
		
        // Set new buffer position for producers
        m.producer_location = (m.producer_location + 1) % buffer_size;

        // Update amount of data stored in buffer
		pthread_mutex_lock(&m.buffer_data_stored_lock);
		m.buffer_data_stored += 1;
		pthread_mutex_unlock(&m.buffer_data_stored_lock);

        // Leaving critical section
		pthread_mutex_unlock(&m.prod_lock);

        // Signal to consumers that data has been written to buffer
		pthread_cond_signal(&m.CVC);
		
	}
	
	printf("P%d: Exiting\n",*(int *)thread_id);
	return NULL;
}


void * consumer(void * thread_id){
	printf("C%d: Consuming %d values\n",*(int *)thread_id, buffer_size*2);

    // Calculate the total number of items the thread has to consume
    int total_items = num_producers * buffer_size * 2;

    int items;

    // If thread id is 0, thread has to consume the evenly split number + the leftover
    if(*(int *)thread_id == 0)
        items = total_items / num_consumers + total_items % num_consumers;

    // If thread id is not 0, it will only consume the evenly split number of values
    else
       items = total_items / num_consumers; 
	
	for(int i = 0; i < items; i++){
		
		printf("C%d: Consuming %d values\n", *(int *)thread_id, items);
		
	    // Lock critical section	
		pthread_mutex_lock(&m.cons_lock);

        // If buffer is empty wait on the condition variable
		while(m.buffer_data_stored == 0){
			printf("C%d: Blocked due to full buffer\n",*(int *)thread_id);
			pthread_cond_wait(&m.CVC, &m.cons_lock);
			printf("C%d: Done waiting on empty buffer\n",*(int *)thread_id);
		}

	    // Read from buffer
        printf("C%d: Reading %d from position %d\n",*(int *)thread_id, m.buffer[m.consumer_location], m.consumer_location);

        // Set new consumer position
        m.consumer_location = (m.consumer_location + 1) % buffer_size;

        // Update amount of data stored in buffer
		pthread_mutex_lock(&m.buffer_data_stored_lock);
		m.buffer_data_stored -= 1;
		pthread_mutex_unlock(&m.buffer_data_stored_lock);


        // Unlock critical section
		pthread_mutex_unlock(&m.prod_lock);

        // Signal to producers that data has been consumed
		pthread_cond_signal(&m.CVP);
		
	}
	
	printf("P%d: Exiting\n",*(int *)thread_id);
	
	return NULL;
	
}
