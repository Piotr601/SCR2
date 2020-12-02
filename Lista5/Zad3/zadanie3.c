#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h>

#define MAX_BUFF_LENGTH 256 // maksymalna dlugosc bufora

// zdefiniowanie potoku o wlasnej nazwie
#define POTOK "potok1"

// ARGUMENTY
// argc - 2 (ilosc argumentow podczas wywolania)
// argv[0] - ./a.out (wywolanie programu)
// argv[1] - tekst.txt (nazwa pliku txt)

int main(int argc, char* argv[])
{
	// zdefiniowanie bufora, file descriptorow, zmiennej pomocniczej
	char bufor[MAX_BUFF_LENGTH];
	int potokfd;
	int plikfd;
	int n;

	// utworzenie potoku | 0666 - nadanie permisji
	mkfifo(POTOK, 0666);
	// otwieranie potoku
	potokfd = open(POTOK, O_WRONLY);

	for(int i = 1; i < argc; i++)
	{
		// otwieranie pliku z argumentu podanego przez uzytkownika
		printf(" >> Otwarto plik %s\n", argv[i]);
		plikfd = open(argv[i], O_RDONLY);

		// czytanie z pliku
		while((n = read(plikfd, &bufor, MAX_BUFF_LENGTH)) > 0)
		{
			// wpisywanie do potoku
			write(potokfd, bufor, n);
			sleep(3);
		}

		// zamykanie pliku
		printf(" >| Zamknieto plik %s\n", argv[i]);
		close(plikfd);
	}
	// zamykaniu potoku
	close(potokfd);

	return 0;
}