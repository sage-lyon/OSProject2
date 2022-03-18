

void *producer(int thread_id_number){
	printf("P%d: Producing %d values", buffer_size*2);
	
	for(int i = 0; i++; i < buffer_Size*2){
		
		pthread_mutex_lock(&m->producer_lock);
		while(&m->buffer_data_stored >= buffer_size){
			printf("P%d: Blocked due to full buffer", thread_id_number);
			pthread_cond_wait(&m->CVP,&m->producer_lock);
			printf("P%d: Done waiting on full buffer", thread_id_number);
		}
		
		int x = rand() % (11);
		
		printf("P%d: Writing %d to position %d", thread_id_number, x, &m->producer_location);
		
		buffer[&m->producer_location] = x;
		
		if(&m->producer_location >= buffer_size){
			&m->producer_location = 0;
		}
		else{
			&m->producer_location += 1;
		}
		pthread_mutex_lock(&m->buffer_data_stored_lock);
		&m->buffer_data_stored+=1;
		pthread_mutex_unlock(&m->buffer_data_stored_lock);
		pthread_mutex_unlock(&m->producer_lock);
		pthread_cond_signal(&m->CVC);
		
	}
	
	printf("P%d: Exiting",thread_id_number);
	
}


void consumer(int thread_id_number){
	printf("C%d: Consuming %d values", buffer_size*2);
	
	int x = num_producers*(buffer_size*2) % num_consumers;
	int k = num_producers*(buffer_size*2) / 2;
	int total_number_of_items_to_consume;
	int data_consumed;
	
	if(thread_id_number == num_producers){
		total_number_of_items_to_consume = k + x;
	}
	else{
		total_number_of_items_to_consume = k;
	}
	
	for(int i = 0; i++; i < total_number_of_items_to_consume){
		
		
		printf("C%d: Consuming %d values",thread_id_number,total_number_of_items_to_consume);
		
		
		pthread_mutex_lock(&m->consumer_lock);
		while(&m->buffer_data_stored == 0){
			printf("C%d: Blocked due to full buffer",thread_id_number);
			pthread_cond_wait(&m->CVC,&m->consumer_lock);
			printf("C%d: Done waiting on empty buffer",thread_id_number);
		}
		
		if(consumer_location == buffer_size){
			data_consumed = buffer[consumer_location];
			printf("C%d: Reading %d from position %d",thread_id_number,data_consumed,&m->consumer_location);
			buffer[&m->consumer_location] = NULL;
			&m->consumer_location = 0;
		}
		else{
			data_consumed = buffer[&m->consumer_location];
			printf("C%d: Reading %d from position %d",thread_id_number,data_consumed,&m->consumer_location);
			buffer[&m->consumer_location] = NULL;
			&m->consumer_location += 1;
		}
		pthread_mutex_lock(&m->buffer_data_stored_lock);
		&m->buffer_data_stored-=1;
		pthread_mutex_unlock(&m->buffer_data_stored_lock);
		pthread_mutex_unlock(&m->producer_lock);
		pthread_cond_signal(&m->CVP);
		
	}
	
	printf("P%d: Exiting",thread_id_number);
	
	
	
}