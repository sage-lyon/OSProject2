typedef struct __monitor {
    pthread_cond_init(CVP);
	pthread_cond_init(CVC);
	pthread_mutex_init(producer_lock);
	pthread_mutex_init(consumer_lock);
	pthread_mutex_init(monitor_lock);
	int consumer_location = 0;
	int producer_location = 0;
	int buffer_data_stored = 0;
} monitor;