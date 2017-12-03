#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_t idPierwszy, idDrugi;

void zakonczenie(void *numer) {
	printf("Funkcja finalizujaca dla watku #%d\n", (int) numer);
}

void *watekPierwszy(void *numer) {

	pthread_cleanup_push(zakonczenie, numer);

	printf("[#%d] Uruchomiono watek Pierwszy #%d\n", (int)numer, (int)numer);
	
	sleep(2);

	pthread_cancel(idDrugi);
	printf("[#%d] Wyslano pierwszy sygnal przerwania dla watku Drugiego\n", (int)numer);

	sleep(2);

	//pthread_cancel(idDrugi);
	//printf("[#%d] Wyslano drugi sygnal przerwania dla watku Drugiego\n", (int)numer);

	pthread_cleanup_pop(1);
	
return NULL;
}

void *watekDrugi(void *numer) {

	pthread_cleanup_push(zakonczenie, numer);

	if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL)) perror("pthread_setcancelstate");

	printf("[#%d] Uruchomiono watek Drugi #%d (przez kilka sekund nie mozna go anulowac)\n", (int) numer, (int)numer);
	sleep(3);

	printf("[#%d] Watek #%d mozna juz anulowac\n", (int) numer, (int)numer);

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) perror("pthread_setcancelstate");
	
	sleep(10);

	pthread_cleanup_pop(0);
	
return NULL;
}

int main() {

	if (pthread_create(&idPierwszy, NULL, watekPierwszy, (void*) (1))) perror("pthread_create(1)");
	if (pthread_create(&idDrugi, NULL, watekDrugi, (void*) (2))) perror("pthread_create(2)");

	pthread_join(idPierwszy,NULL);
	pthread_join(idDrugi,NULL);

return 0;
}
