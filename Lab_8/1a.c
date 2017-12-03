#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define NANO 1000000000L;

int main() {
    
    int child_pid[100], status, k, i;
    struct timespec start, stop;
    double czas;
    long int stoper;

    clock_gettime(CLOCK_REALTIME, &start);

    for (k = 0; k < 100; k++) {

	child_pid[k] = fork();

    	if (child_pid[k] == 0) {
		exit(0);
    	} else {
		
	}

	}
 
    for (i = 0; i < 100; i++) { 
	child_pid[i] = wait(&status);
	}

    clock_gettime(CLOCK_REALTIME, &stop);

    czas = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / (double) NANO;
    stoper = stop.tv_nsec - start.tv_nsec;
    printf("Czas w sekundach: %lf\nCzas w nanosekundach: %ld\n", czas, stoper);

return 0;
}
