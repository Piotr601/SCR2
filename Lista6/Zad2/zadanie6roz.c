#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_NAME 256

// STRUKTURA
struct stat dane_pliku;

// FILE DESKRYPTORY
int plik;
int mapplik;

// Dlugosci plikow
// -> dlugosc - dlugosc pliku do mapowania
int dlugosc;

// Wczytywana nazwa pliku
char nazwa[MAX_NAME];

// Wskaznik do pamieci
char* wskaznik_do_pamieci;

/* ----------------------------------------  /
/               PROGRAM MAIN                 /
/  ---------------------------------------- */

int main()
{

	// Otwarcie pliku do mapowania i sprawdzenie czy nie ma problemow
	if((mapplik=open("map.txt", O_RDWR)) < 0)
	{
		fprintf(stderr, " |-! Blad otwarcia pliku do mapowania\n");
	}

	while(1)
	{
		int pid = fork();
		
		if(pid > 0)
		{
			// Wczytywanie pliku do odczytu
			printf(" | Podaj nazwe pliku: ");
			scanf("%s", nazwa);

			// Otwieranie pliku do odczytu i sprawdzenie czy nie ma problemow
			if((plik = open(nazwa, O_RDONLY)) < 0 )
			{
				fprintf(stderr, " |-! Blad otwarcia pliku\n");
			}
			else
			{
				// dlugosc pliku
				fstat(plik, &dane_pliku);
				dlugosc = dane_pliku.st_size;

				// sprawdzenie czy plik nie ma bledow
				if(dlugosc < 0)
				{
					fprintf(stderr, "|-! Blad dlugosci pliku\n");
				}
				else
				{
					printf(" |-> Dlugosc tego pliku wynosi %d \n",dlugosc);

					// mapowanie 
					printf(" |--> Mapowanie ...");
					ftruncate(mapplik, dlugosc);
					wskaznik_do_pamieci = mmap(NULL, dlugosc, PROT_READ | PROT_WRITE, MAP_SHARED, mapplik, 0);

					// czytanie z pliku
					read(plik, wskaznik_do_pamieci, dlugosc);

					printf(" zakonczone :)\n");
					close(plik);
				}
			printf(" |\n");
			}
		}
		else if (pid == 0)
		{	
			// wyswietlanie w displayu
			execlp("display", "-update", "1", "-delay","2","map.txt", NULL);
		}
		else
		{
			fprintf(stderr, "Blad funkcji fork()\n");
		}
	}

	close(mapplik);
}


		
