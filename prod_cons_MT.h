
typedef struct __monitor {
    pthread_cond_init(CVP);
	pthread_cond_init(CVC);
	pthread_mutex_init(producer_lock);
	pthread_mutex_init(consumer_lock);
	pthread_mutex_init(monitor_lock);
	int consumer_location;
	int producer_location;
	int buffer_data_stored;
	int *buffer;
} monitor;
