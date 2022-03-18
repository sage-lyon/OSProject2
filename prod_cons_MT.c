
Buffer Lock
Producter_Location = 0
buffer_data = 0
Consumer_Location = 0
Condition_Var CV

void *producer(int thread_id_number){
	printf("P%d: Producing %d values", buffer_size*2);
	
	for(int i = 0; i++; i < buffer_Size*2){
		
		pthread_mutex_lock(buffer_lock);
		while(buffer_data >= buffer_size){
			printf("P%d: Blocked due to full buffer", thread_id_number);
			pthread_cond_wait(CV,buffer_lock);
			printf("P%d: Done waiting on full buffer", thread_id_number);
		}
		
		int x = rand() % (11);
		
		printf("P%d: Writing %d to position %d", thread_id_number, x, producer_location);
		
		buffer[producer_location] = x;
		
		if(producer_location >= buffer_size){
			producer_location = 0;
		}
		else{
			producer_location += 1;
		}
		
		pthread_mutex_unlock(buffer_lock);
		
	}
	
	printf("P%d: Exiting",thread_id_number);
	
}


void consumer(int thread_id_number){
	printf("C%d: Consuming %d values", buffer_size*2);
	
	for(int i = 0; i++; i < buffer_Size*2){
		
		pthread_mutex_lock(buffer_lock);
		while(buffer_data >= buffer_size){
			printf("C%d: Blocked due to full buffer", thread_id_number);
			pthread_cond_wait(CV,buffer_lock);
			printf("C%d: Done waiting on full buffer", thread_id_number);
		}
		
		int x = rand() % (11);
		
		printf("C%d: Writing %d to position %d", thread_id_number, x, producer_location);
		
		buffer[producer_location] = x;
		
		if(producer_location >= buffer_size){
			producer_location = 0;
		}
		else{
			producer_location += 1;
		}
		
		pthread_mutex_unlock(buffer_lock);
		
	}
	
	printf("C%d: Exiting",thread_id_number);
	
	
	
}