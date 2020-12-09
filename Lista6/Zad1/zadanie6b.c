#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_BUFF_LENGTH 1
#define MAX_NAME 256

// STRUKTURA
struct stat dane_pliku;

// FILE DESKRYPTORY
int plik;
int mapplik;

// Dlugosci plikow
// -> dlugosc - dlugosc pliku do mapowania
// -> dlugosc1 - dlugosc pliku odczytanego
int dlugosc, dlugosc1;

// Wczytywana nazwa pliku
char nazwa[MAX_NAME];

// Bufor (do zapisu)
char bufor[MAX_BUFF_LENGTH];

// Wskaznik do pamieci
char* wskaznik_do_pamieci;

/* ----------------------------------------  /
/               PROGRAM MAIN                 /
/  ---------------------------------------- */

int main()
{
	// Otwarcie pliku do mapowania i sprawdzenie czy nie ma problemow
	if((mapplik=open("map.txt",O_RDWR)) <= 0)
	{
		fprintf(stderr, " |-! Blad otwarcia pliku do mapowania\n");
	}

	while(1)
	{
		int i=0;

		// Wczytywanie pliku do odczytu
		printf(" | Podaj nazwe pliku: ");
		scanf("%s", nazwa);

		// Otwieranie pliku do odczytu i sprawdzenie czy nie ma problemow
		if((plik = open(nazwa, O_RDONLY)) <= 0 )
		{
			fprintf(stderr, " |-! Blad otwarcia pliku\n");
		}
		else
		{
			// dlugosc pliku
			fstat(plik, &dane_pliku);
			dlugosc1 = dane_pliku.st_size;

			// dlugosc pliku mapujacego
			fstat(mapplik, &dane_pliku);
			dlugosc = dane_pliku.st_size;

			// sprawdzenie czy plik nie ma bledow
			if(dlugosc1 < 0)
			{
				fprintf(stderr, "|-! Blad dlugosci pliku\n");
			}
			// sprawdzanie czy plik nie jest pusty
			else if(dlugosc1 == 0)
			{
				printf(" |-> Ten plik jest pusty\n");
			}
			// sprawdzanie czy plik istnieje
			else if(dlugosc1 > 0)
			{
				printf(" |-> Dlugosc tego pliku wynosi %d \n",dlugosc1);
				
				// mapowanie 
				ftruncate(mapplik, dane_pliku.st_size);
				wskaznik_do_pamieci = mmap(NULL, dane_pliku.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, mapplik, 0);
				
				printf(" |--> Mapowanie ...");
				
				// wpisanie do wspodzielonego pliku
				while(read(plik,bufor,MAX_BUFF_LENGTH)>0)
				{
					wskaznik_do_pamieci[i++]=bufor[0];
				}
				printf(" zakonczone :)\n");
			}
			close(plik);
		}	
		printf(" |\n");
	}
	close(mapplik);
	return 0;
}