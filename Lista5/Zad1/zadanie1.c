#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFF_LENGTH 256 // maksymalna dlugosc bufora

// ARGUEMNTY
// argc - 2 (ilosc argumentow podczas wywolania)
// argv[0] - ./a.out (wywolanie programu)
// argv[1] - tekst.txt (nazwa pliku txt)

int main(int argc, char* argv[])
{
	// Zdefiniowanie bufora i pipe
	int potok_fd[2];
	pipe(potok_fd);

	int pid = fork();

	// Obsluga pliku
	FILE* plik;
	int i=0;

	// Kod rodzica
	if(pid > 0)
	{
		// Zdefiniowanie bufora
		char bufor[MAX_BUFF_LENGTH];

		// Jezeli nie znaleziono pliku
		if ((plik = fopen(argv[1], "r")) == NULL)
		{
			fprintf(stderr, "Blad odczytu pliku\n");
			exit(2);
		}
		// Jezeli znaleziono plik
		else
		{
			// ZAMKNIECIE POTOKU CZYTAJACEGO
			close(potok_fd[0]);

			// Otwarcie pliku podanego jako argument | do odczytu
			plik = fopen(argv[1], "r");

			// Wczytanie zawartosci pliku
			while (fgets(bufor, MAX_BUFF_LENGTH, plik))
			{	
				// Wczytywanie do bufora
				if(write(potok_fd[1], bufor, MAX_BUFF_LENGTH) >= 0)
				{
					i++;
				}
				// Blad wczytania do bufora
				else if(write(potok_fd[1], bufor, MAX_BUFF_LENGTH) < 0)
				{
					fprintf(stderr, "Blad wpisania do bufora\n");
					exit(3);
				}
			}

			// Zamkniecie pliku
			printf("Ilosc zczytanych buforow: %d\n",i);
			fclose(plik);
		}
	}

	// Kod dziecka
	else if (pid == 0)
	{
		printf("\n");

		// ZAMKNIECIE POTOKU WCZYTUJACEGO
		close(potok_fd[1]);

		// Zdefiniowanie bufora
		char bufor[MAX_BUFF_LENGTH];

		// Czytanie z bufora
		while (read(potok_fd[0], bufor, MAX_BUFF_LENGTH))
		{
			// Wyswietlanie zawartosci bufora
			printf("#\n > %s#\n", bufor);
		}
	}

	// Kod bledu
	else
	{
		fprintf(stderr, "Blad funkcji fork()\n");
	}
}