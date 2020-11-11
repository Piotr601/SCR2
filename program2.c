#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define SIGUSR1 10
#define SIGUSR2 12
#define SIGALRM 14
#define SIGTERM 15

/*__________________________________________________________________________________

# 10 SIGUSR1 - pierwszy sygnal definiowany przez uzytkownika

# 12 SIGUSR2 - drugi sygnal definiowany przez uzytkownika

# 14 SIGALRM - sygnal budzika, uzywajac funkcji systemowej alarm() okresla,
               kiedy dany proces ma zostac obudzony

# 15 SIGTERM - standardowy sygnal generowany przez oprogramowanie (domyslny KILL)
  __________________________________________________________________________________*/

int i=0;

// SYNGAL SIGUSR1
void USR1(int signal)
{
  printf(" > Zlapano sygnal (%i) SIGUSR1. \nWylaczenie programu ...\n", signal);
  exit(1);
}

// SYGNAL SIGUSR2
void USR2(int signal)
{
  printf(" > Zlapano sygnal (%i) SIGUSR2. \nKontynuacja pracy programu ...\n", signal);
}

// SYGNAL SIGALRM
void ALRM(int signal)
{
  printf("Poczatek sygnalu (%i)\n", signal);
  for(int j=0; j<10; j++)
    {
      i++;
      printf("%i \n", i);
      sleep(1);
    }
  printf("Koniec sygnalu\n");
}

/*---------------
      PROGRAM
  ----------------*/

int main()
{
  signal(10, USR1);
  signal(12, USR2);
  signal(14, ALRM);
  signal(15, SIG_IGN);
  
  while(1)
  {
    i++;
    printf("%i \n", i);
    sleep(1);
  }
}

/*
  Program przechwytuje sygnaly prawidlowo, wyswietla komunikaty i zakonczenia pracy programu (a), takze powraca
  do ponownej pracy (b). Wstrzymywuje odebrania sygnalu (c), jednak po ponownym wyslaniu sygnalu w czasie blokady,
  po odblokowaniu zostanie wyslany i przetworzony sygnal (ten sam). Ignorowanie sygnalow (d) - tutaj wystarczy
  nic nie robic po odebraniu tego sygnalu.

  Uzyto:
  - SIGUSR1 -> (a)
  - SIGUSR2 -> (b)
  - SIGALRM -> (c)
  - SIGTERM -> (d)
 */
