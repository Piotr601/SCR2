#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define LICZBA_WATKOW 100

// ZMIENNE GLOBALNE
int ilosc_powtorzen_na_watek = 100000;
int promien_kola = 1;

// STRUKTURA
struct dane_watkow
{
   int  id_watku;         
   int  obszar_kola;      // ile razy wylosowany punkt znalazl sie w srodku kola
};

struct dane_watkow dane_watkow_tab[LICZBA_WATKOW];  // tablica struktur

// Funkcja liczaca metoda monte carlo (ile razy punkt znalazl sie w okregu)
int Monte_Carlo()
{
    // losowanie wspolrzednych (0,1) z podwojna precyzja zmiennoprzecinkowa
    double x = 2 * drand48();
    double y = 2 * drand48();

    // warunek na pole okregu
    double pole = sqrt(((x-1)*(x-1))+((y-1)*(y-1)));

    // sprawdzanie czy wylosowany punkt miesci sie w promieniu kola
    if (pole <= promien_kola)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}

// Funkcja wykonujaca sie w kazdym watku
void *Funkcja_watkowa(void *watek) 
{
  struct dane_watkow *wskaznik;           // lokalny wskaznik na strukture
  wskaznik = (struct dane_watkow*) watek; // stworzenie wskaznika odwolujacego sie do argumentu funkcji

  int id_zadania = wskaznik -> id_watku;
  
  // algorytm Monte Carlo
  for (int i=0; i < ilosc_powtorzen_na_watek; i++)
  {
    dane_watkow_tab[id_zadania].obszar_kola += Monte_Carlo();
  }
  
  // obliczenie i wyswietlenie sredniej wartosci PI dla danego watku      
  printf(" %d, Wartosc PI wynosi: %f\n", id_zadania, (float)dane_watkow_tab[id_zadania].obszar_kola * 4 / ilosc_powtorzen_na_watek);
  pthread_exit(NULL);
}

// PROGRAM GLOWNY MAIN
// przerobiony program hello32.c
int main() 
{
  int t;
  double wynik = 0.0;
  pthread_t watki[LICZBA_WATKOW];

  srand48(1);

  for(t=0; t < LICZBA_WATKOW; t++) 
  {
    dane_watkow_tab[t].id_watku = t;
    int rc = pthread_create(&watki[t], NULL, Funkcja_watkowa, (void *) &dane_watkow_tab[t]);
        
    if (rc) 
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  
  sleep(1);
    
  for(int j=0; j < LICZBA_WATKOW; j++)
  {
    wynik = wynik + dane_watkow_tab[j].obszar_kola;
  }

  printf(" > Westymowana wartosc liczby PI: %f\n", wynik * 4 / (LICZBA_WATKOW * ilosc_powtorzen_na_watek));
  pthread_exit(NULL);
}
