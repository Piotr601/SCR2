#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BUFF_LENGTH	256// maksymalna dlugosc bufora

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

	// Obsluga pliku, dlugosci i licznik
	int plik;
	int dlugosc;
	int i=0;

	// Kod rodzica
	if(pid > 0)
	{
		// Jezeli nie znaleziono pliku
        if((plik = open(argv[1], O_RDONLY)) <= 0) {
            
            fprintf(stderr, "Blad odczytu pliku\n");
            exit(2);
        }
        // Jezeli znaleziono plik
      	else
      	{
			// Zamkniecie potoku czytajcego
	        close(potok_fd[0]);

	        // Zdefiniowanie bufora
	        char bufor[MAX_BUFF_LENGTH];

	        // Wczytanie zawartosci buforu, dopoki cos w nim jest
	        while((dlugosc = read(plik, bufor, MAX_BUFF_LENGTH)) > 0) {

	        	// Wczytywanie  do buforwa
	    		if(write(potok_fd[1], bufor, dlugosc) >= 0) 
	    		{
	    			i++;
	    		}
	    		// Blad wczytania do bufora
	            else if(write(potok_fd[1], bufor, dlugosc) < 0) 
	            {
	            	fprintf(stderr, "Blad wpisania do bufora\n");
	                exit(3);
	            }	          
	        }
	        // Zamkniecie pliku
	        printf("Ilosc zczytanych buforow: %d\n",i);
	        close(plik);
    	}
	}

	// Kod dziecka
	else if (pid == 0)
	{

		// ZAMKNIECIE POTOKU WCZYTUJACEGO
        close(potok_fd[1]);

        // ZAMKNIECIE PLIKU
        close(0);

        // Zduplikowanie potoku
        dup(potok_fd[0]);

        // Zamkniecie potoku CZYTAJACEGO
        close(potok_fd[0]);

        // Gdy plik istnieje
        if((plik = open(argv[1], O_RDONLY)) > 0) 
        {	
        	// nastapi wyswietlenie w nowym procesie
	        execlp("display", "display", NULL, NULL);
	    }
	}

	// Kod bledu
	else
	{
		fprintf(stderr, "Blad funkcji fork()\n");
	}
}