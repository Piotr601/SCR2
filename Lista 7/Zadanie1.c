#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ILOSC_WATKOW 20

void* komunikat(void *id_watku)
{
	long watek_id;
	watek_id = (long) id_watku;
	printf("Hello SCR. Written by thread: %ld\n", watek_id);

	pthread_exit(NULL);
}

int main()
{
	long tworzenie_watku;

	pthread_t id_watku[ILOSC_WATKOW];

	for(long k=0; k < ILOSC_WATKOW; k++)
	{
		printf(" > Create %ld\n",k);
		tworzenie_watku = pthread_create(&id_watku[k], NULL, komunikat, ((void*)k));
		
		if(tworzenie_watku)
		{
			fprintf(stderr, "Blad przy tworzeniu watku\n");
			return 3;
		}
	}

	for(long k=0; k < ILOSC_WATKOW; k++)
	{
		pthread_join(id_watku[k],NULL);
	}

	pthread_exit(NULL);

	return 0;
}