#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_t idPierwszy, idDrugi, idTrzeci, idCzwarty, idPiaty;
pthread_key_t klucz;
pthread_mutex_t lock;
static pthread_once_t jeden = PTHREAD_ONCE_INIT;

struct informacje {
		char * napis;
		int numer;
	};


void generuj() {
	pthread_key_create (&klucz, NULL);
}

void *watek(void *info) {

	struct informacje *i;

	i = (struct informacje *) info;

 	pthread_once (&jeden, generuj);
  	pthread_setspecific(klucz, i -> napis);
	pthread_mutex_unlock(&lock);

	sleep(10);

	printf("Nazwa %s oraz numer %d\n", (char *) pthread_getspecific(klucz), i -> numer);

return NULL;
}

int main() {

	struct informacje info;

	pthread_mutex_init(&lock, NULL);
 	
	pthread_mutex_lock(&lock);
	info.napis = "watek 1";
	info.numer = 1;
	if (pthread_create(&idPierwszy, NULL, watek, (void*) (&info))) perror("pthread_create(1)");
	pthread_mutex_lock(&lock);
	//sleep(1);
	info.napis = "watek 2";
	info.numer = 2;
	if (pthread_create(&idDrugi, NULL, watek, (void*) (&info))) perror("pthread_create(2)");
	pthread_mutex_lock(&lock);	
	//sleep(1);
	info.napis = "watek 3";
	info.numer = 3;
	if (pthread_create(&idTrzeci, NULL, watek, (void*) (&info))) perror("pthread_create(3)");
	pthread_mutex_lock(&lock);	
	//sleep(1);
	info.napis = "watek 4";
	info.numer = 4;
	if (pthread_create(&idCzwarty, NULL, watek, (void*) (&info))) perror("pthread_create(4)");
	pthread_mutex_lock(&lock);	
	//sleep(1);
	info.napis = "watek 5";
	info.numer = 5;
	if (pthread_create(&idPiaty, NULL, watek, (void*) (&info))) perror("pthread_create(5)");
	

	pthread_join(idPierwszy,NULL);
	pthread_join(idDrugi,NULL);
	pthread_join(idTrzeci,NULL);
	pthread_join(idCzwarty,NULL);
	pthread_join(idPiaty,NULL);
	pthread_key_delete(klucz);
  	pthread_mutex_destroy(&lock);

return 0;
}
