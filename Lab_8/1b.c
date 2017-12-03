#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define NANO 1000000000L;

void* watek(void* numer) {

return NULL;
}

int main() {
	
	int i;
	pthread_t id[100];
 	struct timespec start, stop;
    	double czas;
    	long int stoper;
	
	clock_gettime(CLOCK_REALTIME, &start);

	for (i = 0; i < 100; i++) {
		pthread_create(&id[i], NULL, watek, (void*) (i));
		}

	for(i = 0; i < 100; i++) {
		pthread_join(id[i],NULL);
	}

	clock_gettime(CLOCK_REALTIME, &stop);

   	czas = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double) NANO;
    	stoper = stop.tv_nsec - start.tv_nsec;
    	printf("Czas w sekundach: %lf\nCzas w nanosekundach: %ld\n", czas, stoper);

return 0;
}
